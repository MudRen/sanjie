// 密林宝库 by Calvin

inherit ROOM;
#include <ansi.h>


void create ()
{
  set ("short","密林");
  set ("long", @LONG

这里是密林的一处要道,以往常有些许土匪出没,可如今却全然不见其踪影了。

LONG);

  set("exits", ([
        "south" : __DIR__"men",
        "north" : __DIR__"1",
      ]));
  set("outdoors", __DIR__);

  setup();
}


void init()
{       
        object me=this_player();
        if( query("done") ) return;
        if( interactive(me)) {
                remove_call_out("greeting");
                call_out("greeting",2, me);
        }
}
	
int greeting(object me)
{
	object *list, ob;
	int i;
	if( !me || environment(me) != this_object() ) return 1;
        tell_room(this_object(), "忽然一阵黑风狂啸而来………\n");

	list=all_inventory(this_object());
	i=sizeof(list);
	while (i--)
	{
		ob=list[i];
                ob->move("/d/milin/qy/sc");
                message_vision("顷刻间黑风停住了，$N也迷迷糊糊到了另一个地方………\n", ob);
	}
	this_object()->set("done");
	call_out("reg", 300);
	return 1;
}
int reg()
{
	this_object()->delete("done");
	return 1;
}

