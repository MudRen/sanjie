//九霄冷月宫
//by junhyun@SK

inherit ROOM;

void create ()
{
        set ("short", "太乙宫");
        set ("long", @LONG

四周贴满了道教经文，中间挂着一幅巨大的太极八卦图，
三缕青烟扶遥而上，让人感到一丝清静。

LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
        "east" : __DIR__"gong4",    
        ]));

        set("objects", 
        ([ //sizeof() == 1
        "/d/wizz/junhyun/usr/gsy" : 1,
        ]));

        set("indoors", "太乙宫");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

