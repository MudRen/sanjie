// shendao.c stey 血刀「祭血神刀」

#include <ansi.h>

inherit SSERVER;
int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;

        if (!target ) target = offensive_target(me);
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail(RED"装备刀才能使用「枯骨祭血神刀」？\n"NOR);
        if (!target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「枯骨祭血神刀」只能对战斗中的对手使用。\n");
        if ((int)me->query_skill("kugu-blade", 1) < 200 )
                return notify_fail(WHT"你枯骨刀刀法不够娴熟，使不出「枯骨祭血神刀」。\n"NOR);
        if ((int)me->query_skill("huntian-qigong", 1) < 200 )
                return notify_fail(RED"你混天气功火候不够，使不出「枯骨祭血神刀」。\n"NOR);
        if (!PFM_D->valid_family(me, "陷空山无底洞"))
                return notify_fail("只有无底洞门人才可以用！\n");
        if ((int)me->query("max_force") < 600)
                return notify_fail(RED"你内力修为不足，无法运足内力。\n"NOR);
        if ((int)me->query("force") < 600)
        {
                return notify_fail(HIC"你现在内力不够，没能将「枯骨祭血神刀」使完！\n"NOR);
        }
        msg = HIC "$N右手持刀向左肩一勒，一阵血珠溅满刀面，紧接着右臂抡出，一片血光
裹住刀影向$n当头劈落，\n"NOR;

        if( ((random(me->query("combat_exp")) + (me->query("combat_exp")/2) > (int)target->query("combat_exp")*1/2 ))) 
        {
                //damage = random((int)(me->query("sen")/2))+(int)(me->query("sen")/30);
                damage = random((int)(me->query("sen")/10))+(int)(me->query("sen")/2);
                me->add("force", -200);
                me->recevive_damage("kee", (me->query("kee")/10), me, "pfm");
                me->start_busy(1);
                target->start_busy(2+random(2));
                target->receive_damage("kee", damage, me, "pfm");
                target->receive_wound("kee", damage/2, me, "pfm");
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
                msg += HIC"$n疾忙侧身避让，但血刀疾闪，只觉眼前一阵血红，刀刃劈面而下，鲜血飞
溅，惨声大嚎！\n"NOR;
                if(me->query_temp("wddtoppfm"))
                {
                        msg+=HIG"$N使出神刀绝技——刀光血影！\n$n一时难以逃避这招，被无数血色刀光击中，受到极其恐怖的伤害！\n";
                        target->receive_damage("kee", damage*(random(4)+1), me, "pfm");
                }
        } 
        else
        {
                me->start_busy(2);
                me->add("kee", -(me->query("kee")/7));
                msg += HIY"可是$n侧身避让，不荒不忙，躲过了$N的血刀。\n"NOR;
                me->add("force", -120);
        }
        message_vision(msg, me, target);
        if(!target->is_fighting(me)) target->fight_ob(me);
        return 1;
}

