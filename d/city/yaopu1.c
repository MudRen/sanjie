//changan city

inherit ROOM;
#include <ansi.h>
void create ()
{
        set ("short","药房" );
        set ("long", @LONG

这是长安城一家老字号的药铺的药房，药房中摆满了各种各样的
药材，急需药铺伙计把这些药材磨成需要的药粉，药丸之类。
LONG);

        set("exits", 
        ([ //sizeof() == 1
                "west" : __DIR__"yaopu",
        ]));

        set("objects", 
        ([ //sizeof() == 1
                "/adm/npc/city_yao" : 1,
        ]));
        
        set("no_fight", 1);;
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);


}



