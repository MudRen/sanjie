//npc--shengmu

inherit NPC;

#include <ansi.h>

void create()
{
        set_name(HIM"三圣母"NOR, ({"san shengmu", "shengmu"}));
        set("age", 32);
        set("attitude", "peaceful");
        set("gender", "女性");
        set("title", HIC"圣母娘娘"NOR);
        set("str", 30);
        set("int", 20);
        set("per", 40);
        set("con", 20);
        set("max_gin", 10000);
        set("max_kee",10000);
        set("max_sen", 10000);
        set("combat_exp", 15000000);
        set("daoxing", 15000000);


        set("force", 20000);
        set("max_force", 20000);
        set("force_factor", 500);
        set("mana",20000);
        set("max_mana", 20000);
        set("mana_factor", 500);
        set_skill("unarmed", 300);
        set_skill("force", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("spells", 300);
        set_skill("whip", 300);
        set_skill("jueqingbian",300);
        set_skill("moonforce",300);
        set_skill("moonshentong",300);
        set_skill("moondance",300);
        set_skill("baihua-zhang",300);
        map_skill("dodge","moondance");
        map_skill("unarmed","baihua-zhang");
        map_skill("force","moonforce");
        map_skill("spells","moonshentong");
        map_skill("axe","jueqingbian");


        create_family("月宫", 2, "弟子");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: cast_spell, "mihun" :),
                (: cast_spell, "arrow" :)  
  }) );

        setup();

        add_money("gold", 50);

        carry_object("/d/obj/cloth/luoyi")->wear();
        carry_object("/d/obj/weapon/whip/jueqingwhip")->wield();

}


void init()
{
  object me;
    ::init();
  if( userp(me = this_player()) && !is_fighting() 
          && living(me) ) 
    call_out("greeting", 1, me);

}

void greeting(object me)
{
    me=this_player();
          
            if(!me || environment(me)!=environment()) return;
if (me->query("bld/done")) 
{
             command("say 凑热闹呀？ \n");
destruct(this_object());
return;
}


     if ( me->query("bld/jie") !=1 && me->query("age") <= (me->query("lucky/bld")+1))
           {
             command("kick "+me->query("id"));
             command("你是哪儿来的，快滚出去！ \n");
          me->move("/d/quest/bld/shanjiao");
             message_vision("你只觉的一下被踢中，飞了出去！ \n",me);                return;
           }
      command("chat "+me->query("name")+"救我出洞，一家团聚，功德无量！");
             me->add("combat_exp",100000);
             me->add("daoxing",20000);
             me->add("potential",50000);
             me->add("balance", 15000000);
             if ( me->query("lucky/bld"))
             {
             me->add("str",1);
             me->add("int",1);
             me->add("spi",1);
             me->add("con",1); 
             message_vision("你得到膂力、悟性、灵性、根骨各多一点！ \n",me);
             }
             me->delete("bld/monkey");
             me->delete("bld/chenxiang"); 
         me->delete("bld/monther");
             me->delete("bld/laozhe");
             me->delete("bld/taxue");
             me->delete("bld/erlang");
             me->delete("bld/dog");
             me->add("bld/done",1);
        me->set("lucky/bld",me->query("age"));
             message_vision("你得到十万武学，二十年道行，五万潜能，一千五百两黄金存款！ \n",me);
         
      destruct(this_object());
      return;
}

