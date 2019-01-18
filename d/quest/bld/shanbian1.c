//room

inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short","山边");
        set ("long", @LONG

这里是华山的西边，从这里走可以到华山的悬崖，很多人都喜欢
去那个悬崖，听说一个是景色美，还有就是可能会发现什么秘密！
LONG);

        set("exits", 
        ([ //sizeof() == 2
                "east" : __DIR__"shanjiao",
                "westup" : __DIR__"xuanya",
        ]));


        set("outdoors", "huashan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

