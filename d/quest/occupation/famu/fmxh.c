//Created by kuku@sjsh 2003.2

inherit ROOM;

void create ()
{
        set ("short", "伐木工协会");
        set ("long", @LONG

伐木工协会坐落在一片绿荫掩映的树林中，这里环境幽雅，
在这里工作真是件惬意的事情。
LONG);

        set("exits", ([ /* sizeof() == 2 */             
                "east" : __DIR__"shulin2",
                "south": __DIR__"songlin",
        ]));
        set("objects", ([  
                __DIR__"npc/guanshi" : 1,
        ])); 
        setup();
}
