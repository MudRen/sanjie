//by dewbaby@sk_sjsh
//九剑·旧梦

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int i,j;
        int kwj;

        if( !target ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
           return notify_fail("「旧梦」只能对战斗中的对手使用。\n");

        kwj = me->query_skill("kongwujian");

        if( (int)me->query_skill("kongwujian", 1) < 120 )
                return notify_fail("你的空无剑等级不够，再好好练练吧。\n");

        if( (int)me->query_skill("sword", 1) < kwj )
                return notify_fail("你的基本剑法等级不够!\n");

        if( (int)me->query_skill("lingbo-steps", 1) < 100 )
                return notify_fail("你的凌波微步等级不够，再好好练练吧。\n");
            if( time()-(int)me->query_temp("meng_end") < 3 )    
                return notify_fail(WHT"[旧梦]消耗真气,无法连续使用!\n"NOR);    


        if( (int)me->query_skill("linghai-force",1) < 100 )
                return notify_fail("你的凌海心法等级不够!\n");
                
        if( (int)me->query("max_force") < 1500 )
                return notify_fail("你的内力太低了!\n");
        if( (int)me->query("force") < 500 )
                return notify_fail("你的真气不够!\n");

        if (!objectp(weapon = me->query_temp("weapon"))
           || weapon->query("skill_type") != "sword"
           || me->query_skill_mapped("sword") != "kongwujian")
            return notify_fail("你这样可以使出「旧梦」吗？\n");
        
        i = (int)me->query_skill("kongwujian",1)/2;
        j = (int)me->query("max_force",1)/110*4+20;   
 
   message_vision(WHT"$N手中宝剑如风般朝$n"WHT"连连刺去，一剑刚落二剑顿起！\n\n"HIC"$n"HIC"被逼得叫苦连连，却躲不开快若无形的剑招!\n"NOR,me,target);

        me->add_temp("apply/attack", i);
        me->add_temp("apply/sword", i);
       me->add("force", -90);
        me->add_temp("apply/damage", j);
        target->start_busy(random(2));
        target->receive_damage("kee",j,me,"pfm");
        target->receive_wound("kee", i,me,"pfm");
        target->add("force",-j);
     message_vision(WHT"$N轻声吟道：“旧梦与谁同?朔风舞穹空。雪映衬花红，清夜倚熏笼。”\n\n"HIC"$n"HIC"听得一头雾水，以至于忘记身处万分危机之中！\n"NOR,me,target);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        if(me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        if(me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  

       me->start_busy(1);
       return 1;
}





