// player装备
//

#include <armor.h>
#include <ansi.h>

inherit WAIST;

void create()
{
        set_name(HIW"飞羽"NOR, ({ "wan", "yaodai" }) );
        set("long", "梅很注重身材啦，喜欢束腰，这是她平时常用的腰带
。\n");
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "条");
                set("material", "cloth");
                set("armor_prop/armor", 20);
                set("armor_prop/spells", 50);
                set("armor_prop/dodge", 20);
                set("value", 50000);
        }
        setup();
}

