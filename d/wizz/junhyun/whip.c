//��������
//by junhyun@SK

#include <weapon.h>
//  inherit F_UNIQUE;

inherit WHIP;
#include <ansi.h>
void create()
{
        set_name(HIW"����"+HIY"����"NOR, ({"yinsuo jinling", "bian","whip"}));
        set_weight(5000);
if( clonep() )
                set_default_object(__FILE__);
        else {
set("long","һ�������˿�Ƴɵ������Ϲ���������ɫ��������\n");
                set("unit", "��");
                set("value", 12000);
                set("wield_msg",HIW "������һ������$N�����Ѿ�����һ���׻λε�����\n"NOR);
                set("unwield_msg", "$N�����������������ϡ�\n");
                set("weapon_prop/courage", 20);
                }
        init_whip(100);
        setup();
}
mixed hit_ob(object me, object victim)
{
    int damage_bonus = 0;
    
    if( (string)me->query("family/family_name") == "��˿��"
                && me->query_skill("yinsuo-jinling",1) > 1)
    damage_bonus = me->query_skill("yinsuo-jinling",1);
    damage_bonus = (damage_bonus+random(damage_bonus))/2;

    victim->receive_wound("kee",damage_bonus);
    return HIW"����"+HIY"����"+HIC"��ϼ�����䣡\n" NOR;

}
