#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
        int ap,dp,damage,chance;
        string msg;
        object weapon;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展「阎罗歌舞」？\n");
        if(!me->is_fighting())
                return notify_fail("「阎罗歌舞」只能在战斗中使用！\n");
        if (!PFM_D->valid_family(me, "阎罗地府"))
                return notify_fail("不是阎罗地府的不能用「阎罗歌舞」！\n");
        if((int)me->query("max_force") < 1000 )
                return notify_fail("你的内力不够！\n");
        if((int)me->query("force") < 1000 )
                return notify_fail("你的内力不足！\n");
        if((int)me->query("sen") < 300 )
                return notify_fail("你的精神不足，没法子施用外功！\n");
        if((int)me->query_skill("hellfire-whip", 1) < 60)
                return notify_fail("你的烈火鞭修为还不够，使用这一招会有困难！\n");
        msg = HIR"\n$N手腕晃动如疾风，以疾风的速度瞬间绕着$n转了九千九百九十九圈,突然打出一鞭！\n"NOR;
        ap = me->query("combat_exp"); 

        dp = target->query("combat_exp"); 

        if( random(ap)> (dp/4)) 
        {
                damage = me->query_skill("whip",1) * 2 + me->query("force_factor");
                if (damage > 1000) damage = 900+random(100);
                target->receive_damage("kee",damage,me,"pfm");
                target->receive_wound("kee",damage/2,me,"pfm");
                msg += CYN"结果$n被$N的「阎罗歌舞」迷惑，未能躲闪！\n"NOR;
        }
        else 
                msg += "但是被$n躲开了。\n"NOR;
        message_vision(msg, me, target);
        if( damage > 0 ) COMBAT_D->report_status(target);
        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }
        me->add("force",-200);
        me->start_busy(2);
        return 1;
}

