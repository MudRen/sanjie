//By waiwai@mszj 2000/12/02

inherit ITEM;

#include <ansi.h>
#include <task.h>

void create()
{
        set_name("花裙子", ({"hua qunzi", "qunzi"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一件很漂亮的裙子。\n");
                set("unit", "件");
                set("owner_name","梅鸳鸯");
                set("owner_id","mei yuanyan");
        }
}

