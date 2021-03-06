//乱刃分尸
//by junhyun@SK
#include <ansi.h>
inherit SSERVER;

int perform(object me, object target)
{
        int extra;
        object weapon1;

        if(!target) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「乱刃分尸」？\n");

        if(!me->is_fighting())
                return notify_fail("「乱刃分尸」只能在战斗中使用！\n");

        if (!PFM_D->valid_family(me, "轩辕古墓"))
                return notify_fail("非古墓弟子不能用「乱刃分尸」！\n");

        if((int)me->query("max_force") < 500)
                return notify_fail("你的内力不够！\n");

        if((int)me->query("force") < 500 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 250)
                return notify_fail("你的精神不足，没法子施用外功！\n");

        if((int)me->query_skill("mohuang-blade",1) < 200)
                return notify_fail("你的魔皇刀法还不够娴熟，使用这一招会有困难!\n");


        weapon1=me->query_temp("weapon"); 

        extra = me->query_skill("mohuang-blade",1);

        message_vision(HIR"\n
$N默运九阴，体内先天罡气力贯右手，手中"+weapon1->query("name")+HIR"被内力逼的通红，
突然无数红光，如划破天际的闪电般直逼$n全身要害!\n"NOR, me, target);

        if(!target->is_busy()) target->start_busy(2);

        me->add_temp("apply/attack",extra);
        me->add_temp("apply/damage",extra);
        COMBAT_D->do_attack(me, target, weapon1);
        COMBAT_D->do_attack(me, target, weapon1);
        COMBAT_D->do_attack(me, target, weapon1);
        COMBAT_D->do_attack(me, target, weapon1);

        message_vision(HIR"\n
$n全身顿时被$N劈出无数的伤口，就在$n无力招架的时候，$N左手
一翻从腰间抽出一把无形的宝剑向$n刺去，$N双手飞舞，刀剑其施，
霎时间红光如雨般倾斜而至。"NOR, me, target);


        COMBAT_D->do_attack(me, target, weapon1);
        COMBAT_D->do_attack(me, target, weapon1);
        COMBAT_D->do_attack(me, target, weapon1);
        COMBAT_D->do_attack(me, target, weapon1);

        me->add_temp("apply/damage",-extra);
        me->add_temp("apply/attack",-extra);

        me->receive_damage("sen", 100);
        me->add("force", -100);
        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }


        me->start_busy(2);

        return 1;
}

