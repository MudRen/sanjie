// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//meeting.c

inherit ROOM;

void create ()
{
  set ("short", "后殿");
  set ("long", @LONG

    后殿比起大殿来要小多了，不过这么却是非常整洁，不知道
这里以前的主人是谁。窗外映着漫天风雪，靠窗有一张桌子，桌
子上好象压着一张字纸（paper），也不知道写了些什么！

LONG);
  set ("item_desc",([
     "paper": @LONG

　　　 　　　┌—┬—┬—┬—┬—┬—┬—┬—┐
　　　　　　 │　│　│  │　│　│　│　│  │
  　　　　　 │君│明│似│今│何│既│何│既│
     　　　　│已│夕│水│日│需│然│必│不│
   　　　　　│陌│何│无│种│誓│无│不│回│
　   　　　  │路│夕│痕│种│言│缘│忘│头│
　　 　　　　│　│　│　│　│　│　│　│  │
   　  　　　└—┴—┴—┴—┴—┴—┴—┴—┘

LONG]));

  set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"living",
]));

  set("objects", ([ /* sizeof() == 1 */
]));
  setup();
}


void init()
{
this_player()->set("env/brief",0);
}

