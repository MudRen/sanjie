inherit NPC;
#include <ansi.h>
int liwu();

int answer_me();

void create()
{
         set_name("东方大财神", ({"caishen"}));
         set("long",
                "这个是天天送大礼的财神大老爷，呵呵...\n"
                "他正在这里发节日红包，看来你可以向他要。(ask caishen about 红包拿来)\n" );

        set("gender", "男性");
        set("title",HIY"笑口常开,"+HIW"天天送礼的"NOR);
        set("age", 28);
        set("per", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("inquiry", ([           
                       "红包拿来"    :(:liwu:),           
                         ]));
        setup();
        carry_object("/d/lingtai/obj/faguan")->wear();
}
int answer_me()
{
        command("say 小心我扁你！嘿嘿 。\n");
        return 1;
}

void init()
{
    object ob;
    ::init();
    if( interactive(ob=this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting",1,ob);
        }
    
}
void greeting(object ob)
{
        if(!ob || environment(ob)!=environment()) return;

      command("say 你是来拿红包的吧？\n");
}
int liwu()
{
        object me,ob;
        me=this_player();
        if (!userp(me)){
                command("heng");
                command("say "+"什么小猫小狗也来要礼物？！");
                command("qi");
                return 1;
        }
      if ((int)me->query("combat_exp") <200000 || (int)me->query("mud_age")<18000)
        { command("say "+"嘿嘿，想用新玩家来骗我，没门！。");
        return 1;}
        if (me->query("combat_exp") < 200000 && (int)me->query("mud_age")<18000)
         { command("say "+"你是大米吗?不是？我看挺象!");
          return 1;}
         if(me->query("lucky/spring_time") && (me->query("lucky/spring_time")+286400)>time())
          {command("say "+"你刚拿了红包，不可太贪哟，过两天再来吧！\n");
          return 1;}
        me->add("sen",-50);
        me->set("lucky/spring_time",time());    
        ob = new("/d/wizz/liwu/obj/hongbao");
        ob->move(me);
        ob->set("owner",me->query("id"));
    
      message_vision(HIW"节日"+HIY"快乐！\n"+HIW"财神大老爷给"+me->query("name")+"一个"+HIR"红包"NOR+"。\n",this_object(),this_player());

      command("job 恭喜恭喜，"+me->query("name")+"得到了节日红包!");
      return 1;
}
