// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//living.c

inherit ROOM;

void create ()
{
  set ("short", "枫雪大殿");
  set ("long", @LONG

                雪是无由醉，梦从有因扬
                莫问心中事，从来浅梳妆

LONG);


  set("exits", ([ /* sizeof() == 4 */
   "west" : __DIR__"zoulang",
   "east" : __DIR__"restroom",
   "north" : __DIR__"meeting",
   "out" : __DIR__"fdoor",
]));

  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/dream":1,
  "/d/obj/flower/rose":2,
]));

  set("valid_startroom", 1);

  setup();
  "/obj/board/fxtd_b"->foo();
}


