//By waiwai@mszj 2000/12/02

#include <ansi.h>

inherit ITEM;
#include <task.h>
void create()
{
        set_name("鱼网", ({"yu wang", "wang"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "别看网烂，却可以捉到鱼。\n");
                set("unit", "条");
               set("owner_name","张顺");
                set("owner_id","zhang shun");
        }
}

