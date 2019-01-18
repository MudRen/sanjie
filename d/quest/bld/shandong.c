//room

inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short","山洞");
        set ("long", @LONG

华山的内部，三圣母就被押在这里，大概已有了十几年了。这
里有一个法台，上面就押着圣母。法台上还有一道神符，只要
揭（jie）了它，圣母就自由了！
LONG);

        set("exits", 
        ([ //sizeof() == 0
        
        ]));

        set("objects", 
        ([ //sizeof() == 1
//                __DIR__"npc/libai" : 1,
        ]));


        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_jie", "jie");
}

int do_jie(string arg)
{
         object where = this_object();
         object me=this_player();
         object *ob = all_inventory(environment(me));
         int i;
         object shengmu=present("san shengmu",where); 

         if (arg!= "fu")
         return notify_fail("你要揭什么？ \n");
         if (shengmu)
         return notify_fail(HIM"三圣母"NOR+"不是在吗？ \n");

         if (me->query("bld/done") > 0)
         return notify_fail("你不是揭过了吗？ \n");

         if (me->query("bld/dog")!= 1 || me->query("bld/erlang")!=1 
             || me->query("bld/pi")!=1 ) {
         
         return notify_fail("没人叫你揭，你乱揭什么？还不快出去？ \n");
           return 1;                     }

            if (sizeof(ob)>1)
         return notify_fail("这里东西太多拉，"+HIM"三圣母"NOR+"会不高兴的！\n");
           
if (me->query("lucky/bld")>0){
me->add("bld/done",1);
return notify_fail("你干吗呀？怎么老来啥？ \n");}
         shengmu = new ("/d/quest/bld/npc/shengmu");
         shengmu->move(where);
         message_vision("只见一道金光闪过，"+HIM"三圣母"NOR+"从法台上飘了下来，你只觉香风拂面，让人联想翩翩！ \n",me);
         me->set("bld/jie",1);
         return 1;
}
