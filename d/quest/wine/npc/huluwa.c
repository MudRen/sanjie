inherit NPC;
int ask_hulu (); 

void create()
{
        set_name("葫芦娃", ({ "hulu wa" }) );
        set("gender", "男性" );
        set("age", 10+random(5));
        set("long", "这是一个机灵活泼的葫芦娃。\n");
        set("combat_exp", 150+random(800));
        set("attitude", "friendly");
        set("env/wimpy", 60);
        set("chat_chance_combat", 50 );
        set("chat_msg_combat", ({
                "葫芦娃叫道：杀人哪！救命啊！\n",
                "葫芦娃叫道：爹、娘，快救救我啊！\n",
                (: command, "surrender" :),
        }) );
        set("inquiry", ([ 
            "金刚葫芦" : (: ask_hulu :), 
           ]) ); 

        setup();
}

int ask_hulu () 
{ 
         object obj;
         object me=this_object();
         object who=this_player();
         if (who->query("level")<35){
               command("say "+RANK_D->query_respect(who)+"还的继续努力呀，等你等级高了再来吧。 \n"); 
           return 1;}
        if ( !who->query("wine/start") || !present("jiu pai",who)) { 
               command("say 我这没有你要的东西。 \n"); 
               return 1;} 
         if ( who->query_temp("poem/wrong") || !who->query("poem_answered")){
           command("pure "+who->query("id"));
           command("say 我这倒是有个宝贝葫芦，不过如果你想要，得先去长安的乐府诗社去对诗，答对了就给你。 \n"); 
           command("xixi");
             return 1;}
          obj=new("/d/quest/wine/obj/hulu");
          obj->move(who);
          message_vision("$N给了$n一只"+obj->query("name")+"。\n", me,who);
          who->delete("poem_answered");
            return 1; 
} 
