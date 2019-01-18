//青羽魔剑
//by junhyun@SK

#include <weapon.h>
//  inherit F_UNIQUE;

inherit F_UNIQUE;
inherit SWORD;
#include <ansi.h>
void create()
{
        set_name(HIG"青羽魔剑"NOR, ({"qingyu mojian", "sword","jian"}));
        set_weight(5000);
if( clonep() )
                set_default_object(__FILE__);
        else {
set("long","一柄散发着青色妖气的宝剑。\n");
                set("unit", "柄");
                set("value", 12000);
               set("unique", 1);
                set("wield_msg", "$N中手聚起一股青色妖气，慢慢盘旋成一柄利剑！\n");
                set("unwield_msg", "$N手中的利剑化作一团青色妖气消失了。\n");
                set("weapon_prop/courage", 20);
                }
        init_sword(120); // so high...mudring
        setup();
}
mixed hit_ob(object me, object victim)
{
    int damage_bonus = 0;
    
    if( (string)me->query("family/family_name") == "轩辕古墓"
                && me->query_skill("qinghu-jian",1) > 1)
    damage_bonus = me->query_skill("qinghu-jian",1);
    damage_bonus = (damage_bonus+random(damage_bonus))/4; //...

    victim->receive_wound("kee",damage_bonus);
    return HIG"青羽"+HIW"魔剑"+HIR"上妖气四射！\n" NOR;

}

