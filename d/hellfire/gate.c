inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIY"地狱火城"NOR);
        set("long", @LONG

※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※
※※※  这就是入口了，没有一定的修为，最好还是不要乱闯哦。※※※
※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※

LONG);
        set("exits", ([
                "up" : "/d/city/dowmtown1",
                "down" : "/d/hellfire/hellfire1/in.c",
        ]));
        set("objects", ([
                __DIR__"npc/mofashi" : 1,
        ]));
    set("hellfireroom",1);
    set("position_max",4);
        setup();
}
int valid_leave(object me, string dir)
{
        object a;
   if (dir == "down" ) {
                if(objectp(a=present("guard", environment(me))) &&
living(a) )
        return notify_fail("守卫拦住你说道：禁止通行。\n");
        }   
        return ::valid_leave(me, dir);
}
