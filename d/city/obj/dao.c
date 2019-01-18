//手术刀

#include <ansi.h>
#include <weapon.h>

inherit BLADE;

void create()
{
        set_name(HIW"手术刀"NOR, ({"blade", "shoushu dao", "dao"}) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 500);
                set("material", "iron");
                set("long", "这是神农氏专用手术用刀，寒光四射，看来锋利无比。\n");
                set("wield_msg", "$N抽出一只寒光四射的$n握在手中。\n");
                set("unequip_msg", "$N将手中的$n插入怀中的刀囊。\n");
        }
        init_blade(125);
        setup();
}

