/***************************************
MUDLIB：Biographies         〓悟空传〓  
Created Admin By Waiwai@2001/02/18
Admin Email：wkzstory@21cn.com         
****************************************/
// Update by waiwai@2001/04/17
//Last modified by waiwai@2001/04/24

#include <ansi.h>
inherit NPC;

string do_zhuibu();
int get_reward(object me, object obj);
int potential_lv(int exp);

void create()
{
        set_name("程药发", ({ "cheng yaofa", "cheng" }));
        set("title", "长安知府");
        set("gender", "男性");
        set("age", 43);
        set("str", 4000);
        set("dex", 20);
        set("long", "他就是程药发，长安现任知府。\n");
        set("combat_exp", 30000);
        set("shen_type", 0);
        set("attitude", "heroism");

        set_skill("unarmed", 50);
        set_skill("force", 50);
        set_skill("sword", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 15);

        set("force", 500);
        set("max_force", 500);
        

        set("inquiry", ([
                "追捕" : (: do_zhuibu :),
        ]));

        setup();
        //carry_object("clone/weapon/gangjian")->wield();
        //carry_object("/clone/misc/cloth")->wear();
}

string do_zhuibu()
{

string *quest = ({
"/d/xueshan/dixiashi",
"/d/xueshan/bingchuan",
"/d/xueshan/binggu",
"/d/xueshan/binggukou",
"/d/xueshan/bingya-up1",
"/d/xueshan/bingya-up2",
"/d/xueshan/bingya-up3",
"/d/xueshan/bingya-up4",
"/d/xueshan/bingya-up5",
"/d/xueshan/bingya-up6",
"/d/xueshan/bingya-up7",
"/d/xueshan/chufang",
"/d/xueshan/eroad1",
"/d/xueshan/eroad2",
"/d/xueshan/eroad3",
"/d/xueshan/no4-e",
"/d/xueshan/no4-enter",
"/d/xueshan/no4-w1",
"/d/xueshan/no4-w2",
"/d/xueshan/no4-wn1",
"/d/xueshan/no4-wn2",
"/d/xueshan/restroom",
"/d/xueshan/shanpo",
"/d/xueshan/shanpohou",
"/d/xueshan/snowmaze1",
"/d/xueshan/snowmaze2",
"/d/xueshan/snowmaze3",
"/d/xueshan/snowmaze4",
"/d/xueshan/snowmaze5",
"/d/xueshan/snowmaze6",
"/d/xueshan/snowmaze7",
"/d/xueshan/snowmaze8",
"/d/xueshan/snowmaze9",
"/d/xueshan/wroad1",
"/d/xueshan/wuchang-c",
"/d/xueshan/wuchang-e",
"/d/xueshan/wuchang-n",
"/d/xueshan/wuchang-ne",
"/d/xueshan/wuchang-nw",
"/d/xueshan/wuchang-s",
"/d/xueshan/wuchang-se",
"/d/xueshan/wuchang-sw",
"/d/xueshan/wuchang-w",
"/d/xueshan/xiaomuwu",
"/d/xueshan/xihai",
"/d/xueshan/xuejie",
"/d/xueshan/xuejie-2",
"/d/xueshan/xuejie-3",
"/d/xueshan/xuelu1",
"/d/xueshan/xuelu2",
"/d/xueshan/xueshan1",
"/d/xueshan/xueshan2",
"/d/xueshan/xueshan3",
"/d/xueshan/xueshan4",
"/d/xueshan/xueshan5",
"/d/xueshan/xueshan6",
"/d/ourhome/honglou/bula", 
"/d/lingtai/lantao2",
"/d/moon/courtyard",
"/d/changan/nanyue",
"/d/gao/yashi",
"/d/meishan/feifeng",
"/d/sea/wunei",
"/d/nanhai/zhulin22",
"/d/eastway/guandao2", 
"/d/dntg/hgs/up1", 
"/d/qujing/wuzhuang/taijituroom",
"/d/qujing/baotou/shanlu5",//13 line
"/d/qujing/baoxiang/zuofang",
"/d/qujing/bibotan/furong",
"/d/qujing/biqiu/xiaozi",
"/d/qujing/chechi/da", 
"/d/qujing/dudi/sandong",
"/d/qujing/fengxian/ludian",
"/d/qujing/firemount/cuiyun1",
"/d/qujing/kusong/qingcao0",
"/d/qujing/jilei/shan1",
"/d/qujing/jindou/jindou2",
"/d/qujing/jingjiling/songlin",
"/d/qujing/jinping/huayuan1",
"/d/qujing/jisaiguo/eastmarket",
"/d/qujing/maoying/tuxue3",
"/d/qujing/nuerguo/annei",
"/d/qujing/pingding/dating",
"/d/qujing/pansi/ling4",
"/d/qujing/tongtian/minju3",
"/d/qujing/qilin/shan13",
"/d/qujing/qinfa/longgong",
"/d/qujing/qinglong/dongting",
"/d/qujing/tianzhu/hou5",
"/d/qujing/wudidong/shanlu2",
"/d/qujing/wuji/qiyutan",
"/d/qujing/xiaoxitian/daxiong",
"/d/qujing/yuhua/xiaojie2",
"/d/qujing/zhujie/da",
"/d/qujing/zhuzi/mianguan",
"/d/jjf/dining_room",
"/d/westway/fenghuo",
"/d/kaifeng/xihu4", 
"/d/songshan/tayuan",
"/d/mingjiao/lsd/lsgu",
"/d/mingjiao/bhd/pingyan1",//49
});
//100
        object obj, ob = this_player();
        int exp = ob->query("combat_exp");

        if ( environment(this_object())->query("short")!="衙门正厅" )
                return "这里不是衙门，你有事回衙门再说吧？";

        if ( ob->is_busy() || ob->query_temp("pending/exercising"))
                return "你现在正忙着呢。\n";

        if ( ob->query_condition("in_zhuibu") )
                return "你不是己经在追捕了吗？ 如果你不想干，就放弃吧。\n";


         if (exp < 5000000)
        {
                if (exp < 100000) {
                        command("pat " + ob->query("id"));
                        return ("程药发说道：你年纪还小，大人的事怎么能做呢？\n");
                }
                else if (exp < 500000) {
                        obj = new("/quest/thief");
                        obj->move(quest[random(103)]);
                        ob->set_temp("抓/" + obj->query("id"), 1);
                }
                else if (exp < 1000000) {
                        obj = new("/quest/zei");
                        obj->move(quest[random(103)]);
                        ob->set_temp("抓/" + obj->query("id"), 1);
                }
                else if (exp < 2000000) {
                        obj = new("/quest/dadao");
                        obj->move(quest[random(103)]);
                        ob->set_temp("抓/" + obj->query("id"), 1);
                }
                else if (exp < 3000000) {
                        obj = new("/quest/qinfan");
                        obj->move(quest[random(103)]);
                        ob->set_temp("抓/" + obj->query("id"), 1);
                }
                  else if (exp < 4000000) {
                        obj = new("/quest/dawang");
                        obj->move(quest[random(103)]);
                        ob->set_temp("抓/" + obj->query("id"), 1);
                }
                ob->start_busy(1);

                ob->set("oldtitle",ob->query("title"));
                ob->set("title",HIY"长安衙门捕快"NOR);
                ob->apply_condition("in_zhuibu", 40);
                message_vision(HIW"$N已被委任为衙门捕快。\n"NOR,ob);
                remove_call_out("destrory");
                call_out("destrory",1000,obj);
//          return "快去把" + obj->query("name") + obj->short()+ CYN"给我抓来，可别让他逃了！\n"NOR;//153 line
          return "快去把" + obj->query("name") +obj->short()+ "给我抓来，可别让他逃了！\n";

        }
        else {
                return(HIC"程药发说道：这种小事怎敢劳您大驾？\n"NOR);
        }
}

int accept_object(object me, object obj)
{
        if ( !me || environment(me) != environment() ) return 0;

        if ( !objectp(obj) ) return 0;

        if ( !present(obj, me) ) {say("你没有这件东西。\n"); return 0;}

        if ( me->query_condition("in_zhuibu") ) {
                if ( me->query_temp("抓/" + obj->query("id")) )
                {
                        command("nod");
                        command(HIW"say 很好很好，这是你的奖赏。\n"NOR);
                        call_out("get_reward", 0, me, obj);
                        me->apply_condition("after_zhuibu", 7);
                        me->apply_condition("in_zhuibu", 0);
                        me->delete_temp("抓/" + obj->query("id"));
                        me->set("title",me->query("oldtitle"));
                        me->delete("oldtitle");
                        return 1;
                }
                else {
                        command("heng");
                        command(HIR"say 想滥竽充数，来人啦，给我打！打完了关起来！！！\n"NOR);
                        message_vision(HIR"四周衙役凶神恶刹般拥过来，围住你一顿痛打......\n"NOR, me);
message("channel:rumor", HIR"【官府通报】：自有 "HIW+me->query("name")+HIR" 追捕朝廷钦犯时有欺瞒嫌疑，略戒惩罚并打入大牢！！！\n"NOR, users());
                        me->apply_condition("after_zhuibu", 7);
                        me->apply_condition("in_zhuibu", 0);
                        me->set("title",me->query("oldtitle"));
                        me->delete("oldtitle");
                        me->unconcious();
                        me->move("/d/changan/jianyu");
                        me->add("combat_exp", -500);
                        me->add("potential", -200);
                        me->add("office_number", -2);
                        return 0;
                }
        }
        else {
                command("say 你好象还没什么任务吧，\n");
                return 0;
        }
}

int get_reward(object me, object obj)
{
        int exp, pot, bonus;
        int rand = random(3);
        if ( rand == 0 )
                rand = 1;

         exp =((int)me->query("literate")*2)+random(200) + me->query("combat_exp")/20000;
         pot = exp / 5;//20

                        remove_call_out("destrory");
                        call_out("destrory",1,obj);

        me->add("combat_exp", exp);
/*
        bonus = (int)me->query("potential");
        bonus = bonus - (int)me->query("learned_points");
        bonus = bonus + pot;
        if ( bonus > potential_lv((int)me->query("combat_exp")) )
        bonus = potential_lv((int)me->query("combat_exp"));
        bonus += (int)me->query("learned_points");
        me->set("potential", bonus );
*/
        me->add("potential", pot);
        tell_object(me, sprintf(HIY"你得到了 "HIR"%s"HIY" 点潜能 "HIR"%s "HIY"点武学经验。\n"NOR,chinese_number(pot),chinese_number(exp)));
message("channel:rumor", HIM"【官府通报】："HIW+me->query("name")+HIM" 追捕朝廷钦犯有功被奖励了 "HIR+chinese_number(exp)+HIM" 点武学 "HIR+chinese_number(pot)+HIM" 点潜能！！！\n"NOR, users());
}

int potential_lv(int exp)
{
        int grade;
        grade = 500 + exp / 500;;
        return grade;
}

void destrory(object ob)
{
        destruct(ob);
        return;
}

