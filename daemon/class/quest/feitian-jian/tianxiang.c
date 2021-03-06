// feitian-jian.c  飞天剑
// Modified by Cody May.2001
// Write by Cody

#include <ansi.h>

inherit SSERVER;


int perform(object me, object target)
{
        object weapon, ob;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「天翔龙闪」?\n");

        if( !me->is_fighting() )
                return notify_fail("「天翔龙闪」只能在战斗中使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if( environment(me)->query("no_fight") )
                return notify_fail("在这里不能攻击他人。\n");

        if( (int)me->query_skill("feitian-jian",1) < 180 )
                return notify_fail("你的飞天剑等级不够，你怎么能使出「天翔龙闪」。\n");


        if( target->is_busy() )
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if (me->query("force") < 300)
                return notify_fail("你内力不继，难以使出「天翔龙闪」。\n");



        msg = HIR "$N使出飞天御剑流的剑决「天翔龙闪」，剑风随着你的移动形成了一个风流！\n\n罩住了$n的全身, 使$n动弹不得。\n" NOR;

        if( random(me->query("combat_exp")) > (int)target->query("combat_exp") / 4 )
        {
                msg +=  HIG "结果$p被$P攻了个措手不及! \n" NOR;
                target->start_busy(6);
                me->add("force", -100);
        }
        else
        {
                msg += HIY "可是$p看破了$P的企图，并没有上当。\n" NOR;
                me->start_busy(2);
        }

        message_vision(msg, me, target);

        
        return 1;  

}

