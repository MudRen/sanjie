// created by kuku@sjsh 2002/12

inherit ROOM;

void create ()
{
    set ("short", "威远镖局");
  set ("long", @LONG

这里是威远镖局，几只太师椅一字排开，正中央坐着总
镖头，手持烟袋杆正在闭目沉思。墙上挂着几幅字画
和一把宝剑。
LONG);

    set("exits", ([ 
        "north"    : "/d/qujing/qinfa/jiedao7",
      ]));
    set("objects", ([ 
        __DIR__"npc/baobiao"    : 1,
      ]));
  setup();
}
