//modified by sgzl for dntg/donghai quest
#include <skill.h>
#include <ansi.h>

int goto_home(); 

inherit NPC;
inherit F_MASTER;

string expell_me(object me);

void create()
{
        set_name(HIC"龙飞"NOR, ({"long fei", "long","fei","longfei","tianshen"}));

        set("long","龙飞是水帝禹的化身,拥有很强大的水能量。\n");
       set("gender", "男性");
       set("age",100);
       set("title", HIC"天杰水帝"NOR);
       set("class","dragon");
       set("attitude", "peaceful");
       set("shen_type", 1);
       set("combat_exp", 5000000);
       set("daoxing", 5000000);
       set("rank_info/respect", "水帝");
       set("per", 20);
       set("str", 30);
       set("max_kee", 6000);
       set("max_gin", 400);
       set("max_sen", 6000);
       set("force", 3000);
       set("max_force", 1500);
       set("force_factor", 120);
       set("max_mana", 800);
       set("mana", 1600);
       set("mana_factor", 40);

       set_skill("huntian-hammer", 350);
        set_skill("hammer", 350);
        set_skill("literate", 350);
       set_skill("unarmed", 350);
       set_skill("dodge", 350);
       set_skill("force", 350);
       set_skill("parry", 350);
       set_skill("fork", 350);
       set_skill("spells", 350);
        set_skill("seashentong", 350);
        set_skill("dragonfight", 350);
        set_skill("dragonforce", 350);
        set_skill("fengbo-cha", 350);
        set_skill("dragonstep", 350);
        map_skill("hammer", "huntian-hammer");
        map_skill("spells", "seashentong");
        map_skill("unarmed", "dragonfight");
        map_skill("force", "dragonforce");
        map_skill("fork", "fengbo-cha");
        map_skill("parry", "fengbo-cha");
        map_skill("dodge", "dragonstep");
       set("chat_chance_combat", 50);
       set("chat_msg_combat", ({
                (: cast_spell, "hufa" :),
                (: perform_action, "unarmed", "sheshen" :),
                }) );

        create_family("东海龙宫", 1, "水族");
        set_temp("apply/armor",50);
        set_temp("apply/damage",25);
set("inquiry", ([ 
"练功": (:goto_home:), 
])); 
        setup();

        carry_object("/d/9ct/zb/pifeng")->wear();
        carry_object("/d/9ct/zb/fork")->wield();
}
void init()
{
        ::init();
        add_action("do_learn", "xuexi");
}


void destroy(object ob)
{
        destruct(ob);
        return;
}

void unsetlearn(object ob)
{
        if (find_player(ob->query("id"))) {
                ob->set_temp("temp/learn", 0);
                ob->save();
                }
}

string *reject_msg = ({
"说道：您太客气了，这怎么敢当？\n",
        "像是受宠若惊一样，说道：请教？这怎么敢当？\n",
        "笑著说道：您见笑了，我这点雕虫小技怎够资格「指点」您什么？\n",
});

int do_learn(string arg)
{
        string skill, teacher, master;
        object me= this_player(), ob;
        int master_skill, my_skill, sen_cost;

        if(!arg || sscanf(arg, "%s from %s", skill, teacher)!=2 )
                return notify_fail("指令格式：xuexi <技能> from <某人>\n");

        if( me->is_fighting() )
                return notify_fail("临阵磨枪？来不及啦。\n");

        if( !(ob = present(teacher, environment(me))) || !ob->is_character())
                return notify_fail("你要向谁求教？\n");

        if( !living(ob) )
                return notify_fail("嗯．．．你得先把" + ob->name() + "弄醒再说。\n");

     if( !master_skill = ob->query_skill(skill, 1) )
                return notify_fail("这项技能你恐怕必须找别人学了。\n");

        if (skill != "unarmed" || !me->query_temp("temp/learn") ) 
                return notify_fail( ob ->name() + reject_msg[random(sizeof(reject_msg))] );

        notify_fail(ob->name() + "不愿意教你这项技能。\n");
        if( ob->prevent_learn(me, skill) )
                return 0;

        my_skill = me->query_skill(skill, 1);
        if( my_skill >= master_skill )
                return notify_fail("这项技能你的程度已经不输你师父了。\n");

        notify_fail("依你目前的能力，没有办法学习这种技能。\n");
        if( !SKILL_D(skill)->valid_learn(me) ) return 0;

        sen_cost = 250 / (int)me->query_int();

        if( !my_skill ) {
                sen_cost *= 2;
                me->set_skill(skill,0);
        }

        if( (int)me->query("learned_points") >= (int)me->query("potential") )
                return notify_fail("你的潜能已经发挥到极限了，没有办法再成长了。\n");
        printf("你向%s虢逃泄亍?s沟囊晌省n", ob->name(),
                to_chinese(skill));

        if( ob->query("env/no_teach") )
                return notify_fail("但是" + ob->name() + "现在并不准备回答你的问题。\n");

        tell_object(ob, sprintf("%s蚰闱虢逃泄亍?s沟奈侍狻n",
                me->name(), to_chinese(skill)));

        if( (int)ob->query("sen") > sen_cost/5 + 1 ) {
                if( userp(ob) ) ob->receive_damage("sen", sen_cost/5 + 1);
        } else {
                write("但是" + ob->name() + "显然太累了，没有办法教你什么。\n");
                tell_object(ob, "但是你太累了，没有办法教" + me->name() + "。\n");
                return 1;
        }
                

        if( (int)me->query("sen") > sen_cost ) {
                if( (string)SKILL_D(skill)->type()=="martial"
&&      my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) {
                        printf("也许是道行不够，你对%s幕卮鹱苁俏薹旎帷n", ob->name() );
                } else {
                        printf("你听了%s闹傅迹坪跤行┬牡谩n", ob->name());
                        me->add("learned_points", 1);
                        me->improve_skill(skill, random(me->query_int()));
                }
        } else {
                sen_cost = me->query("sen");
                write("你今天太累了，结果什么也没有学到。\n");
        }

        me->receive_damage("sen", sen_cost );

        return 1;
}

void attempt_apprentice(object ob)
{       
        if( (int)ob->query_skill("dragonforce",1) < 50
        || (int)ob->query_skill("seashentong", 1) < 50) {
        command("say " + RANK_D->query_respect(ob) +
                "还是先去龙宫把基础打好了再来我这儿吧。\n");
        return;
        }       
        command("smile");
        command("say 难得" + RANK_D->query_respect(ob) +
                "有此心志，还望日后多加努力，为我东海龙宫争光。\n");
        command("recruit " + ob->query("id") );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "dragon");
                   ob->set("title", HIB"东海龙宫小海神"NOR);
}


int goto_home() 
{
object me=this_player(); 
if(me->query("family/family_name")!="东海龙宫")
{ message_vision("$N不是本门中人。\n", me); 
 return 1;
}
else {
me->move("/d/9ct/qy/liangong.c");  }
return 1;
}
