//Created by kuku@sjsh 2003.2

inherit ROOM;

void create ()
{
        set ("short", "矿工协会");
        set ("long", @LONG

矿工协会坐落在风景迤俪的泾水之滨，想要找个好工作吗？
可以来这里试试。
LONG);

        set("exits", ([ /* sizeof() == 2 */             
                "south" : "/d/changan/wside5",
        ]));
        set("objects", ([   
                __DIR__"npc/kuangzhang" : 1,
        ])); 
        setup();
}
