//兰陵 kz_up

inherit ROOM;

void create ()
{
        set ("short", "二楼雅座");
        set ("long", @LONG

这里是兰陵客栈的二楼雅座,这里风景优美,兰陵城的景色尽受眼底。

这里也是无数墨人文者常驻之地,在这里谁都可以雅兴一掷大甩一气。

LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                "down": "/d/calvin/kezhan",
// 21                  "east": "/d/calvin/system",
// 22                  "up": "/d/calvin/kezhan3",
        ]));

        set("objects", 
        ([ //sizeof() == 1
        ]));

//      set("outdoors", "changan");
        set("no_clean_up", 0);
  set("no_time",1);
  set("no_fight", 1);
  set("no_kill", 1);
  set("no_magic", 1);
  set("freeze",1);
        setup();
 call_other("/obj/board/lanling_b1","???");
        replace_program(ROOM);
}
