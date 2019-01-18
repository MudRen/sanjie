#include <ansi.h>
inherit F_VENDOR_SALE;
int ask_niang (); 

void create()
{
        set_name("酒鬼", ({ "jiu gui" }) );
        set("gender", "男性" );
        set("age", 25+random(20));
        set("long", "你看到一位整日醉醺醺的迷迷糊糊的酒鬼。\n");
        set("combat_exp", 150+random(800));
        set("attitude", "friendly");
        set("env/wimpy", 60);
        set("chat_chance_combat", 50 );
        set("chat_msg_combat", ({
                "酒鬼叫道：杀人哪！杀人哪！\n",
                "酒鬼叫道：有土匪哪！光天化日下打劫哪！\n",
                (: command, "surrender" :),
        }) );
        set("inquiry", ([ 
            "百花酿" : (: ask_niang :), 
           ]) ); 

        setup();
        carry_object("/d/obj/cloth/choupao")->wear();
}

int ask_niang () 
{ 
         object obj,jiuyin,jiupai,hulu;
         object me=this_object();
         object who=this_player();
         jiuyin=present("jiu yin",who);
         jiupai=present("jiu pai",who);
         if (who->query("level")<20){
               command("say "+RANK_D->query_respect(who)+"还的继续努力呀，等你等级高了再来吧。 \n"); 
           return 1;}
        if(!userp(who)){
                command("say 你是谁呀，我好象不认识你。 \n");  
                return 1;
        }
         if ( !present("jiu yin",who)||!present("jiu pai",who) ) { 
               command("say 那是什么呀？我不知道喔。 \n"); 
               command("zzz");
               return 1;} 
         if(! who->query("quest/pending/ask/done")){
               command("say 大阐都纲陈光蕊是我的好朋友，这样吧，你去帮他完成一个任务再来找我要东西，完成后直接找我喔，不要进皇宫领赏，不然不给你。 \n"); 
               command("hoho");
               return 1;} 
         if ( !who->query_temp("rent_paid")){
               command("hmm");     
               command("say 最近手头有点紧，这个这个....，知道了吧？ \n"); 
               return 1;} 
          obj=new("/d/quest/wine/obj/baihuaniang");
          obj->move(who);
          who->delete("wine/start");
          who->delete("quest/pending/ask/done");
          who->delete_temp("rent_paid");
          who->delete("wine/mijiu");
          who->delete("wine/gaoliang");
          who->delete("wine/huangjiu");
          destruct(jiuyin);
          destruct(jiupai);
          message_vision("$N给了$n一瓶"+obj->query("name")+"。\n", me,who);
          command("gongxi "+who->query("id"));
        message( "chat", HIC"【"+HIB"西王母"+HIC"】： 恭喜恭喜！"+who->query("name")+"做出了"+obj->query("name")+"，给予重奖。\n" NOR, users() );
        who->add("balance",500002+random(4500000));
            who->add("morality",1);
            who->add("daoxing",20000+random(80000));
        who->set("wine/done",1);
        log_file("winetask","["+ctime(time())+"] "+sprintf("%s(%s)帮王母娘娘做出了百花酿，得到了奖励。\n", who->query("name"),who->query("id")));  
            who->save();
            return 1; 
} 

int accept_object(object who, object ob)
{
        int value;
        if (ob->query("money_id") && (value=ob->value()) >= 300000 && present("jiu yin",who)) 
        {
            tell_object(who, name()+"一哈腰，说道：多谢了，请等一会儿，我这就给你做。\n");
            who->set_temp("rent_paid",1);
            take_money(value, 300000);
                return 1;
        }
        return 0;
}
