//兰陵

inherit ROOM;
#include <ansi.h>
void create ()
{
        set ("short","客来药铺" );
        set ("long", @LONG

这是一家很不错的老药铺,这里的老板是个高手
据说还有过医治好死人的先例,不过那也只是传说
这里的布置干净考究,墙上还有块大匾，大匾上写
有"妙手回春"四个大字 ... ...
LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
    "east" : "/d/calvin/lanling/jie7",
        ]));

        set("objects", 
        ([ //sizeof() == 1
"/obj/boss/lanling_yaodian" : 1,
        ]));

//      set("outdoors", "changan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
