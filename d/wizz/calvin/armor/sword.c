// 轩辕剑.c

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(MAG"轩辕剑"NOR, ({ "xuanyuan sword", "jian", "sword" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 100000);
               set("no_sell", "卖?别逗了,这种罕见的东西可以买卖吗!\n");
                set("material", "steel");
                set("long", "这是一把天下唯一的紫金宝剑，剑身透亮,锋利无比。\n");
                set("wield_msg", "一道紫光闪过，$N手中已多了把$n。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
        }
        init_sword(200);
        setup();
}
