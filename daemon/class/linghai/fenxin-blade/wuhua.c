
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill;
        if( !target ) target = offensive_target(me);

       if (!objectp(weapon = me->query_temp("weapon"))
          || (string)weapon->query("skill_type") != "blade")
                    return notify_fail("你使用的武器不对。\n");

                    if( !target  
                    ||      !target->is_character()  
                    ||      target->is_corpse()  
                    ||      target==me)  
                    return notify_fail("「无花」只能在战斗中对对手使用。\n");

      if((int)me->query_skill("fenxin-blade", 1) < 50 )
                    return notify_fail("你的焚心刀法等级不够。\n");       
            
      if ((int)me->query_skill("lingbo-steps", 1) < 80 )
                    return notify_fail("你的凌波微步等级不够！\n");    
   
      if ((int)me->query_skill("blade", 1) < 50 )
                    return notify_fail("你的基本刀法极不够!\n");    
     
      if ((int)me->query("force") < 200 )
                    return notify_fail("你的内力太低了!\n");

      if ((int)me->query("max_force") < 500 )
                    return notify_fail("你现在内力太弱!\n");    
    message_vision(HIM"$N前后游走，身形闪动，手中"+BLINK""+ weapon->name()+ NOR" "+HIM"越使越快，刀光身影绚烂如百花齐放。\n\n"HIC"$n"HIC"随着$N的"BLINK""+weapon->name()+ NOR""+HIC"来回游走，终于却被刀光惑得眼花缭乱。\n"NOR,me,target);
        
           target->add("force",-300);
           target->add("kee", -200);
           target->start_busy(2);
           me->start_busy(random(1));    
           
           return 1;

}




