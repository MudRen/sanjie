// 古冥神剑 by Calvin

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIW"古冥神剑"NOR, ({ "guming sword", "guming", "sword","shenjian" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
             set("value", 0);
                set("material", "steel");
                set("long", "这是一把来自九重天界的神兵,其身乌黑,锋利无比。\n");
                set("wield_msg", "一道白光闪过，$N手中已多了把$n。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
        }
   init_sword(120);
        setup();
}
