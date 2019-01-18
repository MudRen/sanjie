#include <ansi.h>
inherit ROOM;
inherit "/d/9ct/qy/climbtree.c";

void create ()
{
  set ("short", HIW"天外神天"NOR);
  set ("long", @LONG

一间古老的而神秘的寝宫，没人知道它是在哪里，座落在极
为偏僻的山谷中，崎岖的地形会使初次到访者摸不着东西南
北。但它却极负盛名，因为传说中，这里的主人是最接近神
的人，直接执行着神的意志。不管这个传言是真是假，不过，
在这个禁地中的的确确住着一只已沉睡了17000的天神-彗星。



LONG);

  set("exits", ([
           "west" : __DIR__"flash",
           "east" : __DIR__"yanyang",
      ]));

  set("objects", ([
           "/d/wizz/junhyun/usr/ffff.c" : 1,
      ]));

  setup();
}

int do_climb(string arg)
{
        object tianshen; 
  object me=this_player();

  if( (!arg) || !((arg == "sky") || (arg == "天外天")))
    return notify_fail("登什么？\n");
  if (me->is_busy()) return notify_fail("你现在正忙着呢。");
  if( me->query("kee") < (int)(me->query("max_kee")/3)){
    me->receive_damage("kee",(int)me->query("max_kee")*20/100);
    return notify_fail("你身子发虚，一头栽了下来，哎呀！\n");
}
  else
    {
      if ((int)me->query_skill("dodge", 1)<60 && (int)me->query_skill("moondance", 1) < 200)
        {
          message_vision("$N小心翼翼的往上攀登了一点，觉得头晕眼花，就赶紧爬了下来．\n", me);
          me->improve_skill("dodge", 60-me->query("str"));
          tell_object(me, "你领悟出一些基本轻功方面的窍门。\n");
        }
      else
        {
          message_vision("$N轻轻地一跃好似踩着无形的阶梯,一会便消失在云海之中。。\n", me);
                   me->move(__DIR__"tian2.c");
        }
    }
  me->receive_damage("kee", (int)me->query("max_kee")*10/100);
  return 1;
}

int valid_leave(object me, string dir)
{
        object a;
   if (dir == "up" ) {
                if(objectp(a=present("tianshen", environment(me))) &&
living(a) )
        return notify_fail("天神拦住你说道:天外神天的一些禁地请不要前去。\n");
        }   
        return ::valid_leave(me, dir);
}


