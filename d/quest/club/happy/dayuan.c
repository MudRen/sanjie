inherit ROOM;

#include <ansi.h>

void create ()
{
  set ("short","前 院");
  set ("long", @LONG
          ……    梦  回  大  唐  阁    ……

这里是〖梦回大唐阁〗的总坛大院，院中种满了花草，逢春季节，花
茂盛，鲜花顿开，煞是灿烂。院中有一堵风水墙，是人们的风俗习惯
，据说可以挡煞辟邪。墙上写着两个大字〖情〗 〖爱〗。


LONG);

set("exits",([ 
"northup" : __DIR__"juyitang",
"east" : "/u/lost/work",
]));
//set("objects", ([ __DIR__"" : 1, ]));
  set("outdoors", 1);
  set("no_clean_up", 1);
  setup();
}
     int valid_leave(object me, string dir) 
{

if( dir=="east" && me->query("id")!="passion")
return notify_fail("那里你不能去!\n");
return ::valid_leave(me, dir); 

}
