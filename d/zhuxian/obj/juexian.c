#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_UNIQUE;
void create()
{
        set_name( HIW "绝仙剑" NOR, ({ "juexian jian", "jian", "sword" }) );
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long",
"绝仙剑\n"
);
                set("value", 0);
                set("sheenness", 25);
                set("material", "silver");
                set("wield_msg", "$N「唰」地一声抽出一把$n握在手中。\n");
                set("is_monitored", 1);
                set("no_put", 1);
                set("unequip_msg", "$N将手中的$n插入腰间的剑鞘。\n");
        }

        init_sword(125);
        setup();
}
