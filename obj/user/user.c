// user.c
// modify by mudring@Sanjie

#include <ansi.h>
#include <origin.h>
#include <user.h>
#include <command.h>

inherit CHARACTER;
inherit F_AUTOLOAD;
inherit F_SAVE;

nosave int net_dead;
int    is_net_dead()    { return net_dead || ! interactive(this_object()); }
int    is_player()      { return clonep(); }
int    is_pker()        { return query_condition("no_pk_time"); }

nosave int last_age_set;

void create()
{
    ::create();
    set_name("使用者物件", ({ "user object", "user", "object" }) );
}

void terminal_type(string term_type)
{
    set_temp("terminal_type", term_type);
    message("system", "终端机型态设定为 " + term_type + "。\n", this_object());
}

void reset()
{
    if ((int)query("potential") - (int)query("learned_points") < 100)
        add("potential", 1);
    if ((int)query("thief") > 0)
        add("thief", -1 );
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
    string id;

    id = geteuid();
    if (!id) id = getuid();
    if (!stringp(id)) return 0;

    return sprintf(DATA_DIR "user/%c/%s", id[0], id);
}

// override set function
mixed set(string idx, mixed para)
{
    if (idx == "name" && clonep(this_object()) &&
        geteuid(this_object()))
    {
        NAME_D->change_name(this_object(), para, 1);
        return para;
    }
    else
    return ::set(idx, para);
}

int save(int raw)
{
    int res;

    if (!raw) save_autoload();
    res = ::save();
    if(!raw) clean_up_autoload();           // To save memory

#if INSTALL_EXAMINE
    EXAMINE_D->examine_player(me);
#endif
    return res;
}

// This function updates player's age, called by heart_beat()
void update_age()
{
    int age;
    int delta;
    int rmud_age;
    object cake;

    if (! last_age_set)
    {
        last_age_set = time();
        add("mud_age", 0);
    }

    if ((delta = (time() - last_age_set)) > 100)
        // time too long
        delta = 100;

    if (environment() &&
//        !environment()->is_chat_room() ||
        !environment()->query("no_time"))		
    {
        // Update age
        add("mud_age", delta);
    }

    rmud_age = query("mud_age") + query("age_modify");
    if (rmud_age < query("combat_exp") / 4) add("age_modify", 1800);
    else if (rmud_age / 3 < query("combat_exp") / 8) add("age_modify", 300);
    else if (rmud_age < query("combat_exp") / 2) add("age_modify", 60);
    else if (rmud_age / 3 > query("combat_exp") / 2) add("age_modify", -3600);

    last_age_set = time();
    age = rmud_age / 86400;
    if (age > 118) age = 46 + (age - 118) / 4; else
    if (age > 28)  age = 16 + (age - 28) / 3; else
    if (age > 4)   age = 4  + (age - 4) / 2;
    age += 14;
    set("age", age);

    if (!query("shengri/" + age))
    {
        if (query("combat_exp")<20000) return;
        this_object()->set("shengri/"+age,1);
        this_object()->set("birth",1);
        cake = new("/d/city/npc/obj/cake");
        cake->set("owner",this_object()->query("id"));
        cake->move(this_object());
        tell_object(this_object(), "祝你生日快乐！恭喜你获得了特别的生日蛋糕。\n");
        this_object()->delete("birth");  
    }
}

void setup()
{
    mapping fabao_map;
    string  *fabao_list, *id_list, *t_list;
    int     i;
    object  newob;
    string  fabao_id;

    // We want set age first before new player got initialized with
    // random age.
    update_age();

    ::setup();
    restore_autoload();

    // here We restore the self-made fabao
    fabao_map = query("fabao");
    if (!mapp(fabao_map))
        return;

    fabao_list = keys(fabao_map);
    for(i=0; i<sizeof(fabao_list); i++)
    {
        newob = new("/obj/fabao");
        if (newob )
        {
            newob->set("owner_id", query("id"));
            newob->set("series_no", fabao_map[fabao_list[i]]);
            if (!newob->restore())
            {
                tell_object(this_object(), "不能 restore fabao. \n");
                destruct(newob);
                continue;
            }
            fabao_id = (string)newob->query("id");
            if (!fabao_id)
            { // mon 9/5/98
                destruct(newob);
                continue;
            }
            fabao_id = replace_string(fabao_id, " ", "_");
            newob->set("id", fabao_id);
            seteuid(fabao_id);
            export_uid(newob);
            seteuid(getuid());

            id_list = ({ fabao_id });
            t_list = explode(fabao_id, "_");
            if (sizeof(t_list) > 1)
            {
                id_list += t_list;
            }
            newob->set_name(newob->query("name"), id_list);
            if (stringp(newob->query("default_file")))
                newob->set_default_object( newob->query("default_file") );
             newob->save();
            newob->move(this_object());
        }
    }

    if (query("doing"))
        CLOSE_D->continue_doing(this_object());
}

protected void user_dump(int type)
{
    object me = this_object();

    switch(type)
    {
    case DUMP_NET_DEAD:
        if (environment())
        {
            tell_room(environment(), query("name") + "断线超过 " +
                NET_DEAD_TIMEOUT / 60 + " 分钟，自动退出这个世界。\n");
        }
        catch(command("quit"));
        if (objectp(me) && ! query("doing"))
        {
            // command quit failed.
            QUIT_CMD->force_quit(me);
        }
        break;

    case DUMP_IDLE:
        // use input keep idle bug have fixed ...mudring
        if (!environment(me)->query("chat_room"))
        {
            // wizard idle auto visible ...mudring.
            if (wizardp(me))
            {
                if (!query("env/invisibility"))
                {
                    me->set("env/invisibility",1);
                    tell_object(me, "您的发呆时间过长，系统将您转入自动隐身中。\n");
                }
            }
            else
            {
                 tell_object(me, "对不起，您已经发呆超过 " 
                     + IDLE_TIMEOUT/60 + " 分钟了，请下次再来。\n");
                 if (environment())
                 {
                     tell_room( environment(), "一阵风吹来，将发呆中的" + query("name")
                         + "化为一堆飞灰，消失了。\n", ({me}));
                 }
                 command("quit");
                 if (objectp(me) && ! query("doing"))
                 {
                     // command quit failed.
                     QUIT_CMD->force_quit(me);
                 }
                                   
                 return;
            }
        }
        if (in_input() && (!wizardp(me)))
        {
            tell_object(me, "对不起，您已经输入文字发呆超过 " 
                + IDLE_TIMEOUT/60 + " 分钟了，请下次再来。\n");
            tell_room( environment(), "一阵风吹来，将输入文字发呆中的" + query("name")
                + "化为一堆飞灰，消失了。\n", ({me}));
            command("quit");
            if (objectp(me) && ! query("doing"))
            {
                // command quit failed.
                QUIT_CMD->force_quit(me);
            }
            return;
        }
        break;
    default:
        return;
    }
}

// net_dead: called by the gamedriver when an interactive player loses
// hir network connection to the mud.
protected void net_dead()
{
    object link_ob;
    object me = this_object();

    me->remove_interactive();

//271      if (!query("doing") && !query_condition("no_pk_time"))
    if (!query("doing"))
        set_heart_beat(0);

    if (objectp(link_ob = query_temp("link_ob")))
    {
        link_ob->set("last_on", time());
        link_ob->set("last_from",
                      link_ob->query_temp("last_from"));
        link_ob->save();

        destruct(link_ob);
    }

    // no_net_dead room force quit... mudring 
    if (! environment()
        || (environment(me)->query("no_net_dead")))
    {
                QUIT_CMD->force_quit(me);
                return;
    }

    net_dead = 1;
        
    if (userp(me) && ! query("doing"))
    {
        call_out("user_dump", wiz_level(me)?1:NET_DEAD_TIMEOUT, DUMP_NET_DEAD);
        tell_room(environment(), query("name") + "断线了。\n", me);
        CHANNEL_D->do_channel(load_object(LOGIN_D), wiz_level(me)?
                 "wiz":"sys", filter_color(short(1)) + " 断线了。");

        remove_all_enemy();
    }
    else
    {
        if (environment())
            message("vision", name() + "离线了。\n",
                environment(), ({ me }));
        CHANNEL_D->do_channel(load_object(LOGIN_D), wiz_level(me)?
                 "wiz":"sys",filter_color(short(1)) + " 离线了。");
    }
}

// reconnect: called by the LOGIN_D when a netdead player reconnects.
void reconnect()
{
    set_heart_beat(1);
    net_dead = 0;
    remove_call_out("user_dump");
    tell_object(this_object(), "重新连线完毕。\n");
}

string get_id()
{
    return query("id");
}

string get_name()
{
    return query("name");
}

int get_exp()
{
    return query("combat_exp");
}

int get_dx()
{
    return query("daoxing");
}


