//临时pfm
//Created by wuyou@sk

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg,*limbs;
        int i,size,damage,num;

        if( !target ) target = offensive_target(me);
        if( !target||!target->is_character()||!me->is_fighting(target) )
                return notify_fail("你只能对战斗中的对手使用「虎虎虎」。\n");

//    加上门派判断by seng@2005-1-20
// 18      if( me->query("family/family_name")!="三界山") 
// 19         return notify_fail("你不是三界山的, 不能使用「虎!虎!虎!」！\n");
        if( (int)me->query_skill("huxiaojian",1) < 50)
                return notify_fail("你目前功力还使不出「虎虎虎」。\n");
        if( (int)me->query("force") < 100 )
                return notify_fail("你的内力不够。\n");
        me->add("force", -60);
        msg = WHT"虎！虎！虎！虎！虎！虎！虎！虎！虎！虎！虎！虎！\n"NOR;
        message_combatd(msg,me,target,"");
        me->start_busy(1+random(1));

        if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/8 ) 
        {
                        
                limbs=target->query("limbs");                   
                size=(int)(me->query_skill("huxiaojian")/5);
                damage=random(size)+size;
                damage=damage+me->query_str()+random(me->query_temp("apply/damage"));
                num=random(size/2)+size/2;
                for(i=0;i<=num;i++)
                {
                        msg =HIR"$N突然变成一只白虎咬向$p"+limbs[random(sizeof(limbs))]+"！\n"NOR;
                        message_combatd(msg,me,target,"");
                   target->receive_damage("kee",damage,me,"pfm");
                   target->receive_wound("kee",damage,me,"pfm");
                }
                COMBAT_D->report_status(target);
                
        }
        
        return 1;
        
}


