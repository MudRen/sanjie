//edit by xuanzi 2000/9/12

inherit ROOM;

void create ()
{
  set ("short", "小路");
  set ("long", @LONG

这是一条隐蔽的小路，石阶上长满了杂草，到处都是各种藤蔓。大概是这里的
主人疏于管理的缘故，很多小鸟小兽都在这里安了家。在小路的尽头隐隐约约看见
一座楼阁，隐隐有丝丝的花香从附近传来。

LONG);

  set("outdoors", __DIR__"");
  set("exits", ([ /* sizeof() == 2 */
  "out" : __DIR__"lake-side",
  "northup" : __DIR__"wytdamen",
]));

  setup();
  replace_program(ROOM);
}

