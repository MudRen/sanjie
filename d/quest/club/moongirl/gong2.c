//九霄冷月宫
//by junhyun@SK

inherit ROOM;

void create ()
{
        set ("short", "雨花石路");
        set ("long", @LONG

这里是冷月宫内,这里地理环境优雅,一条用雨花石铺成的路
笔直的通向坤月宫

LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
       "north" : __DIR__"moon2", 
       "south" : __DIR__"moon1", 
       "west" : __DIR__"piaomiao",  
       "east" : __DIR__"jinghong",
        ]));

        set("objects", 
        ([ //sizeof() == 1
        ]));

        set("outdoors", "雨花石路");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

