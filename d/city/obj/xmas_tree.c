// xmas-tree

#include <ansi.h>

inherit ITEM;
int do_zhai(string);
void init();

void create()
{
        set_name(HIC "礼"HIR"物"HIG"树" NOR, ({ "liwu tree", "tree"}) );
        set_weight(6000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIC"星灯闪烁美丽灿烂的礼物树，上面有很多小礼物，你忍不住去摘（zhai liwu)。\n
@* .☆  ＊/ * . ☆/ ＊。   \n
   ◢◣。       ◢◣。     \n
  ◢★◣。     ◢★◣。    \n
 ◢■■◣。   ◢■■◣。   \n
◢■■■◣。 ◢■■■◣。  \n
︸︸||︸︸ !!︸︸||︸︸    \n
                           \n
                "NOR);
                set("value", 100000);
                set("unit", "个");
        set("no_clean_up", 0);
        }
         set("is_monitored",1);
         setup();
}

void init()
{
        if (!wizardp(this_player())) {
    set("no_get",1);
    set("no_give",1);
    set("no_drop",1);
    set("no_sell",1);
    }
        add_action("do_zhai", "zhai");
}

int do_zhai(string arg)
{
        object ob;
        int tt;

        object me = this_player();

        if (arg!="liwu" )   return 0;

        me = this_player();
    if (!userp(me)) return notify_fail("什么东西!");
 if (me->query("combat_exp") < 200000 && (int)me->query("mud_age")<18000)
          return notify_fail("你是大米吗?不是？我看挺象!");
         if(me->query("zhailiwu_time") && (me->query("zhailiwu_time")+1800)>time())
          return notify_fail("你刚拿了礼物，不可太贪哟，等等再来吧！\n");
        me->add("sen",-50);
        me->set("zhailiwu_time",time());     
          
        switch(random(15)){
              case 0:
                     ob=new("/d/wizz/ffff/obj/51zhang");
                     ob->move(me);
                     break;
              case 1:
                     ob=new("/obj/gift");
                     ob->move(me);
                     break;
              case 2:
                     ob=new("/d/wizz/helpler/obj/zhou");
                     ob->move(me);
                     break;
              case 3:
                     ob=new("/d/wizz/helpler/obj/ice");
                     ob->move(me);
                     break;
              case 4:
                     ob=new("/d/wizz/ffff/obj/51zhang");
                     ob->move(me);
                     break;
              case 5:
                     ob=new("/d/wizz/cigar/obj/kaixinguo");
                     ob->move(me);
                     break;
              case 6:
                     ob=new("/d/wizz/cigar/obj/quduwan");
                     ob->move(me);
                     break;
              case 7:
                     ob=new("/d/wizz/helpler/obj/zhu");
                     ob->move(me);
                     break;
              case 8:
                     ob=new("/d/wizz/helpler/obj/yao");
                     ob->move(me);
                     break;
              case 9:
                     ob=new("/d/wizz/helpler/obj/dan2");
                     ob->move(me);
                     break;
              case 10:
                     ob=new("/d/wizz/helpler/obj/yuebing");
                     ob->move(me);
                     break;
              case 11:
                     ob=new("/d/city/obj/xjdan");
                     ob->move(me);
                     break;
              case 12:
                     ob=new("/d/wiz/obj/card");
                     ob->move(me);
                             ob->set("owner",me->query("id"));
                     break;
                     break;
              case 13:
                     ob=new("/obj/gift");
                     ob->move(me);
                     break;
              case 14:
                     ob=new("/d/wizz/ffff/obj/51zhang");
                     ob->move(me);
                     break;
                     }
        message_vision(HIY"五"+HIC"一"+HIR+"节"+HIB+"快"+HIW+"乐！\n"+me->query("name")+"从礼物树拿到了一"+ob->query("unit")+ob->query("name")+"。 \n"NOR, me);
                             ob->set("owner",me->query("id"));
                             ob->set("no_put",1);

        return 1;

}


