// 兰陵续 by Calvin

inherit ROOM;

void create ()
{
        set ("short", "清渊小径");
        set ("long", @LONG

这里是一条石头铺成路的小径,是去清渊净水潭唯一的路途。
LONG);

        set("exits", 
        ([ //sizeof() == 4
          "southwest": "/d/calvin/lanling/tan1",
          "northeast": "/d/calvin/lanling/tan3",
        ]));

        set("objects", 
        ([ //sizeof() == 1
        ]));

        set("no_clean_up", 0);
        set("outdoors", "lanling");
        setup();
        replace_program(ROOM);
}
