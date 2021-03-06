// bboard.c

#include <ansi.h>

#define BOARD_CAPACITY query("capacity")

inherit ITEM;
inherit F_SAVE;

void setup()
{
    string loc;
    string my_long, my_id;

    if (stringp(loc = query("location")))
        move(loc);

    my_long = query("long");
    my_id = query("board_id");

    restore();

    set("no_get", 1);
    set("long", my_long);
//    set("id", my_id);
    set("location", loc);
}

void init()
{
    add_action("do_post", "post");
    add_action("do_read", "read");
    add_action("do_discard", "discard");
    add_action("do_appoint", "banzhu");
    add_action("do_demit", "bamian");
    add_action("do_lock", "lockb");
    add_action("do_unlock", "unlockb");
    add_action("do_document", "document");
}

string query_save_file()
{
    string id;

    if (! stringp(id = query("board_id"))) return 0;
        return DATA_DIR + "board/" + id;
}

string query_master()
{
    if (query("master"))
        return query("master");
    else
        return "尚未任命";
}

string short()
{
    mapping *notes;
    int i, unread, last_read_time;

    notes = query("notes");

    if (! pointerp(notes) || ! sizeof(notes))
        return ::short() + " [ 没有任何留言"HIG"  本板版主："HIY + query_master() + NOR" ]";

    if (this_player())
    {
        last_read_time = (int)this_player()->query("board_last_read/" +
                         (string)query("board_id"));
        for (unread = 0, i = sizeof(notes) - 1; i >= 0; i--, unread ++)
            if (notes[i]["time"] <= last_read_time )
                break;
    }
    if (unread)
        return sprintf(HIC"%s"NOR" [ %d 张留言，"HIY"%d"NOR" 张"HIR"未读"HIG"  本板版主："HIY+query_master()+NOR" ]",
                       ::short(), sizeof(notes), unread);
    else
        return sprintf("%s [ %d 张留言"HIG"  本板版主："HIY+query_master()+NOR" ]",
                       ::short(), sizeof(notes));
}

string long()
{
    mapping *notes;
    int i, last_time_read;
    string msg, myid;

    notes = query("notes");
    msg = query("long");
    msg = msg + "留言版的使用方法请见 help board。\n";
    if (! pointerp(notes) || ! sizeof(notes)) return query("long");

    last_time_read = this_player()->query("board_last_read/" + (string)query("board_id"));
/*
    i = sizeof(notes) - 200;
    if (i < 0) i = 0;
    for (; i < sizeof(notes); i++)
    msg += sprintf("%s[%2d]" NOR "  %-40s %s (%s)\n",
        (notes[i]["time"] > last_time_read ? HIY: ""),
        i + 1, notes[i]["title"], notes[i]["author"], ctime(notes[i]["time"])[0..15]);
*/

    for (i = sizeof(notes)-1; i >= 0; i--)
    {
        msg += sprintf("%s[%2d]" NOR "  %-40s %s (%s)\n",
            (notes[i]["time"] > last_time_read ? HIY: ""),
            i + 1, notes[i]["title"], notes[i]["author"], ctime(notes[i]["time"])[0..15]);
    }

    return msg;
}

// This is the callback function to process the string returned from the
// editor defined in F_EDIT of player object.
void done_post(object me, mapping note, int n, string text)
{
    int i;
    int t;
    int pl;
    string sign;
    string pure;
    mapping *notes;
    string *lines;

    if (! stringp(text))
        return;

    if (strlen(text) > 64 * 1024)
    {
        tell_object(me, "你的留言太长了，请略去一些不必要的。\n");
        return;
    }

    lines = explode(text, "\n");
    i = sizeof(lines);
    if (i > 2000)
    {
        tell_object(me, "你的留言太长了，请略去一些不必要的。\n");
        return;
    }

    if (i > 20 && strlen(text) / i < 10)
    {
        tell_object(me, "你的留言中短句太多了，请调整一下以便他人阅读。\n");
        return;
    }

    while (i--)
    {
        // scan all lines
        if (strlen(lines[i]) > 300)
        {
            tell_object(me, "你留言中有些行太长了，请分行以便他人阅读。\n");
            return;
        }
    }

    if (! n) n = me->query("env/default_sign");
    if (! stringp(sign = me->query(sprintf("env/sign%d", n))))
    {
        // auto select the first none null sign
        for (i = 1; i <= 4; i++)
        {
            sign = me->query(sprintf("env/sign%d", i));
            if (stringp(sign)) break;
        }
    }

    if (stringp(sign))
    {
        sign = replace_string(sign, "\\n", "\n");
        sign = trans_color(sign, 1);
        pure = filter_color(sign);

        if (strlen(pure) >= 1 && pure[strlen(pure) - 1] != '\n')
            sign += "\n";

        pure = filter_color(text);
        pl = strlen(pure);
        if (pl >= 1 && pure[pl - 1] != '\n')
            text += "\n\n" + sign;
        else
        if (pl >= 2 && pure[pl - 2] != '\n')
            text += "\n" + sign;
        else
            text += sign;
    }

    note["msg"] = text;
    notes = query("notes");
    if (! pointerp(notes) || ! sizeof(notes))
    notes = ({ note });
    else
    {
        i = sizeof(notes) - 1;
        if (note["time"] <= notes[i]["time"])
            note["time"] = notes[i]["time"] + 1;
        notes += ({ note });
    }

    // Truncate the notes if maximum capacity exceeded.
    if (sizeof(notes) > BOARD_CAPACITY)
    notes = notes[BOARD_CAPACITY / 2 .. BOARD_CAPACITY];

    set("notes", notes);
    save();

    note = copy(note);
    note["msg"] = "来自 " + ::short() + "\n" + text;
    "/obj/board/post_b"->done_post(me, note);

    tell_object(me, "留言完毕。\n");

    me->add_busy(1);
    return;
}

int do_post(string arg, int n)
{
    object me;
    mapping note;
    if (! arg) return notify_fail("留言请指定一个标题。\n");

    me = this_player();
    if (!wizardp(me))
    {

        if (query("wiz_board"))
            return notify_fail("只有巫师才可以在这里留言。\n");

        if (me->query("mud_age") < 1800)
            return notify_fail("你必须在完成注册三十分钟以后才能使用留言版，这段"
                       "时间内请先阅读他人的留言。\n");

        if (me->query("sen") < 50)
            return notify_fail("你现在精神不济，休息一会儿再说吧。\n");

        me->receive_damage("sen", 50);
    }

    if (sscanf(arg, "%s with %d", arg, n) != 2)
        n = 0;

    if (replace_string(arg, " ", "") == "")
        arg = "无标题";
    
    note = allocate_mapping(4);
    note["title"] = arg;
    note["author"] = this_player()->query("name") + "-" + this_player()->query("id");
    note["time"] = time();
    me->edit((: done_post, this_player(), note, n :));
    return 1;
}

int do_read(string arg)
{
    int num;
    mapping *notes, last_read_time;
    string myid;

    last_read_time = this_player()->query("board_last_read");
    myid = query("board_id");
    notes = query("notes");

    if (! pointerp(notes) || ! sizeof(notes))
        return notify_fail("留言板上目前没有任何留言。\n");

    if (! arg) return notify_fail("指令格式：read <留言编号>|new|next\n");

    if (arg == "new" || arg == "next")
    {
        if (! mapp(last_read_time) || undefinedp(last_read_time[myid]))
            num = 1;
        else
            for (num = 1; num<=sizeof(notes); num++)
            {
                if (notes[num-1]["time"] > last_read_time[myid])
                    break;
            }
        
    } else if (! sscanf(arg, "%d", num))
        return notify_fail("你要读第几张留言？\n");

    if (num < 1 || num > sizeof(notes))
        return notify_fail("没有这张留言。\n");

    num--;
    this_player()->start_more(sprintf("[%d] %-40s %s(%s)\n----------------------------------------------------------------------\n",
    num + 1, notes[num]["title"], notes[num]["author"], ctime(notes[num]["time"])[0..9])
    + notes[num]["msg"]);

    // Keep track which post we were reading last time.
    if (! mapp(last_read_time))
        this_player()->set("board_last_read", ([ myid: notes[num]["time"] ]));
    else 
    if (undefinedp(last_read_time[myid]) || notes[num]["time"] > last_read_time[myid])
        last_read_time[myid] = notes[num]["time"];

    return 1;
}

int do_discard(string arg)
{
    mapping *notes;
    int num;
    object me = this_player();
    int n_start, n_end=0;

    if (!arg || (sscanf(arg, "%d to %d", n_start,n_end)!=2 
        && sscanf(arg,"%d",n_start)!=1))
            return notify_fail(HIC"指令格式：discard <留言编号>\n"NOR);
    notes = query("notes");

    if (n_end==0) n_end=n_start;

    if (!arrayp(notes) || n_start < 1 || n_end > sizeof(notes) )
        return notify_fail(HIC"没有这张留言。\n"NOR);
    num=n_end;
    while(num>=n_start)
    {
        num--;
        if (notes[num]["author"] != (string) this_player(1)->query("name") + "-"+this_player(1)->query("id")
            && query("master")!=this_player(1)->query("id")
            && wiz_level(this_player()) < wiz_level("(wizard)"))
        {
            write(sprintf(HIC"第"HIR"%d"HIC"号留言不是你写的,你又不是版主。\n"NOR,num+1));
            return 1;
        }
        if (notes[num]["lock"])
        {
            write(sprintf(HIC"第"HIR"%d"HIC"号留言加锁了,请联系巫师解锁。\n"NOR,num+1));
            return 1;
        }
    }

    if (n_start >1)
        notes = notes[0..num-1] + notes[n_end..sizeof(notes)-1];
    else
        notes =notes[n_end..sizeof(notes)-1];
    set("notes", notes);
    save();
    write(HIC"删除第 " HIR+ (n_start) +HIC " 号到第 "HIR+(n_end)+HIC" 号留言....Ok。\n"NOR);
    log_file("static/POSTING", log_time() + ": " + me->name(1) + "-" + me->query("id")
           + " 删除了" + ::short() + "的第"+(n_start) + "到"+(n_end)+"号留言。\n");

    return 1;
}

int do_appoint(string arg)
{
    object me = this_player();

    if (wiz_level(this_player()) < wiz_level("(arch)")
        && query("master")!=this_player(1)->query("id"))
        return notify_fail("你没有委任版主的权利!\n");
   
    if (!arg)
    {
        if (wizardp(me))
            return notify_fail("你要委任谁为本版版主？\n");
        else
            return notify_fail("你要将本版版主职位转任给谁？\n");
    }

    if (!present(arg,environment(me)))
        return notify_fail("你要任命的玩家不在这个地方！\n");

    this_object()->set("master",arg);

    if (wizardp(me)) 
        message_system("版主公告：" + me->name(1) + "任命 " + arg + " 为 "
                + this_object()->name() + " 版主！");
    else
        message_system("版主公告：现任" + this_object()->name() + "版主"
                + me->name(1) + "将版主职位转任给"+arg+"！");

    log_file("static/zhuanren",sprintf("%s(%s)将%s版主职位转任给%s 时间在: (%s) \n",
             me->name(1), geteuid(me), this_object()->name(), arg, log_time() )); 

    save();      
    return 1;
}

int do_demit()
{
    object me = this_player();

    if (wiz_level(this_player()) < wiz_level("(arch)")
        && query("master")!=this_player(1)->query("id"))
        return notify_fail("你没有罢免版主的权利!\n");

    if (!this_object()->query("master") )
        return notify_fail("这个版本来就没有版主！\n"); 

    if (wizardp(me)) 
        message_system("版主公告：" + me->name(1) + "罢免了 " 
                   + this_object()->name() + " 版主 " + this_object()->query("master") +" ！");
    else
        message_system("版主公告：" + me->name(1) + "放弃了 "
                   + this_object()->name() + " 版主的职位 ！");

    this_object()->delete("master");
    save();
    return 1;
}

int do_lock(string arg)
{
    mapping *notes;
    int num;
       
    if (!arg || sscanf(arg, "%d", num)!=1)
                return notify_fail(HIC"指令格式：lockb <留言编号>\n"NOR);
    notes = query("notes");
    if (!arrayp(notes) || num < 1 || num > sizeof(notes))
        return notify_fail(HIC"没有这张留言。\n"NOR);
    num--;
    if (notes[num]["lock"])
        return notify_fail(HIW"这张留言已经加锁了。\n"NOR);

    if (!wizardp( this_player(1)))
        return notify_fail(HIC"你没权加锁。\n"NOR);
    notes[num]["lock"]=1;
    set("notes", notes);
    save();
    write(HIY"加锁...第 " HIR+ (num+1) +HIY " 号留言....成功。\n"NOR);
    return 1;

}

int do_unlock(string arg)
{
    mapping *notes;
    int num;
       
    if (!arg || sscanf(arg, "%d", num)!=1)
        return notify_fail(HIC"指令格式：unlockb <留言编号>\n"NOR);
    notes = query("notes");

    if (!arrayp(notes) || num < 1 || num > sizeof(notes))
        return notify_fail(HIC"没有这张留言。\n"NOR);
    num--;
    if (!notes[num]["lock"])
    {
        return notify_fail(HIW"这张留言没有加锁。\n"NOR);
    }
    if (!wizardp( this_player(1)))
        return notify_fail(HIR"你没权解锁。\n"NOR);
    notes[num]["lock"]=0;
    set("notes", notes);
    save();
    write(HIY"解锁...第 " HIR+ (num+1) +HIY " 号留言....Ok。\n"NOR);
    return 1;
}

int do_document(string arg)
{
        object document, content, cont_num;
        string mon, dirname="/data/";
        int month, num, nummonth, defmon, defyear, argn;
        mapping *notes;
        string *strmon=({"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"});

        if ((string)SECURITY_D->get_status(this_player(1)) != "(admin)"
            && (string)SECURITY_D->get_status(this_player(1)) !="(arch)" )
                return notify_fail("你没有存档的权力！\n");

        if(query("wiz_board"))
                dirname+="wiz_doc/";
        else
                dirname+="doc/";

        if( ! arg ) return notify_fail("指令格式：document <留言编号>\n"); 

        argn=sscanf(arg, "%d %d %d", num, defmon, defyear);

        if( argn >3)
                return notify_fail("指令格式：document <留言编号>\n");

        if (argn==3) {
                dirname = dirname + sprintf("%d",defyear)+"/";
                month=defmon;
                mon="Null";
        }
        if (argn==2) {
                if (defmon>1995) {
                dirname = dirname + sprintf("%d",defmon)+"/";    
                mon=ctime(time())[4..6];
        }
        else {
                dirname = dirname + ctime(time())[20..23] + "/";
                month=defmon;
                mon="Null";
                }
        }
        if (argn==1) {
                dirname = dirname + ctime(time())[20..23] + "/";
                mon=ctime(time())[4..6];
        }
        if ( mon=="Null" ) {
                if (month>12 || month<1) return notify_fail("要存的月份不存在！\n");
                mon=strmon[month-1];
        }
        else switch (mon) {
                case "Jan": month=1; break;
                case "Feb": month=2; break;
                case "Mar": month=3; break;
                case "Apr": month=4; break;
                case "May": month=5; break;
                case "Jun": month=6; break;
                case "Jul": month=7; break;
                case "Aug": month=8; break;
                case "Sep": month=9; break;
                case "Oct": month=10; break;
                case "Nov": month=11; break;
                case "Dec": month=12; break;
        }

        if (month>12 || month<1) return notify_fail("要存的月份不存在！\n");

        notes = query("notes");
        if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
                return notify_fail("没有这张留言。\n");
        num--;

        cont_num=new("/obj/not.c");
        cont_num->set("file_name", dirname+"month.number");
        cont_num->restore();

        if (!objectp(cont_num) )
                return notify_fail("文档读取失败！\n");
        nummonth=cont_num->query(mon);
        nummonth++;
        cont_num->set(mon, nummonth);
        if (!cont_num->save())
                return notify_fail("存档失败！\n");

        content=new("/obj/not.c");
        content->set("file_name", dirname+"content."+mon);
        content->restore();
        if ( !objectp(content) )
                return notify_fail("文档读取失败！\n");
        if (content->query("msg")) content->set("msg", content->query("msg")+ 
                sprintf("[%3d] %-40s %12s (%s)\n",
                nummonth, notes[num]["title"], notes[num]["author"], 
                ctime(notes[num]["time"])[0..9]) );
        else content->set("msg", sprintf("[%3d] %-40s %12s (%s)\n",nummonth, 
                notes[num]["title"], notes[num]["author"], 
                ctime(notes[num]["time"])[0..9]));

        if (!content->save())
                return notify_fail("存档失败！\n");

        document=new("/obj/not.c");
        document->set("file_name", dirname+ sprintf("%s/doc%d.%d",mon,month, 
                nummonth) );
        document->restore();
        if ( !objectp(document) )
                return notify_fail("文档读取失败！");
        document->set("msg",
                sprintf("[%3d] %-40s %12s 
(%s)\n--------------------------------------------------------------------------------\n", nummonth, notes[num]["title"],
notes[num]["author"], ctime(notes[num]["time"])[0..9])
+ notes[num]["msg"]
);
        if (!document->save())
                return notify_fail("存档失败！\n");
        write("OK.\n");
   
        return 1;
}   
