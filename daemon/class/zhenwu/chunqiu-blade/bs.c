#include <ansi.h>
inherit SSERVER;

int perform(object me, object target)
{
        int skill, skill1, skill2;
        object weapon1, weapon2;

        if(!target) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「刀剑乱」？\n");

        if(!me->is_fighting())
                return notify_fail("「刀剑乱」只能在战斗中使用！\n");

        if(me->query("family/family_name")!="武当山真武门")
                return notify_fail("非真武弟子不能用「刀剑乱」！\n");

        if((int)me->query("max_force") < 500)
                return notify_fail("你的内力不够！\n");

        if((int)me->query("force") < 500 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 250)
                return notify_fail("你的精神不足，没法子施用外功！\n");

        if((int)me->query_skill("xuantian-sword",1) < 100)
                return notify_fail("你的玄天剑法还不够娴熟，使用这一招会有困难!\n");

        if((int)me->query_skill("chunqiu-blade",1) < 100)
                return notify_fail("你的春秋刀法还不够娴熟，使用这一招会有困难!\n");

        weapon1=me->query_temp("weapon");
        weapon2=present("sword", me);
        if(!objectp(weapon2)) 
                return notify_fail("没剑怎么施展「刀剑乱」?\n");

        message_vision(HIM"\n$N手中"+weapon1->query("name")+HIM"刷刷砍出几刀，直逼$n全身要害!\n"NOR, me, target);

        me->set_temp("CQD_perform", 1);
        COMBAT_D->do_attack(me, target, weapon1);
        COMBAT_D->do_attack(me, target, weapon1);
        COMBAT_D->do_attack(me, target, weapon1);
        COMBAT_D->do_attack(me, target, weapon1);

        message_vision(HIC"\n$n正忙于从$N的刀光中脱身时，$N抽出"+weapon2->query("name")+HIC"向$n刺去。"NOR, me, target);

        weapon1->unequip();
        weapon2->wield();

        me->set_temp("CQD_perform", 2);
        COMBAT_D->do_attack(me, target, weapon2);
        COMBAT_D->do_attack(me, target, weapon2);

        me->set_temp("CQD_perform", 3);
        COMBAT_D->do_attack(me, target, weapon2);
        COMBAT_D->do_attack(me, target, weapon2);

        me->delete_temp("CQD_perform");

        me->receive_damage("sen", 100);
        me->add("force", -100);

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }

        weapon2->unequip();
        weapon1->wield();

        me->start_busy(2);

        return 1;
}

