//无底洞-七修剑绝学·狂杀斩 
//by junhyun@SK 

#include <ansi.h> 
#include <combat.h> 
inherit SSERVER; 

void kuang_ok(object); 

int perform(object me, object target) 
{ 
        int damage,damagea,extra; 
        
        if( !target ) target = offensive_target(me); 
        
        if( !target 
        ||      !target->is_character() 
        ||      target->is_corpse() 
        ||      target==me) 
                return notify_fail("你要对谁施展这一招「狂杀斩」？\n"); 
                
        if (!PFM_D->valid_family(me, "陷空山无底洞"))
                return notify_fail("“狂杀斩”只有无底洞门人才可以用！\n");
        
        if(!me->is_fighting()) 
                return notify_fail("「狂杀斩」只能在战斗中使用！\n"); 
        
        if((int)me->query("max_force") < 300 )  
                return notify_fail("你的内力不够！\n"); 
                
        if((int)me->query("force") < 300 ) 
                return notify_fail("你的内力不足！\n"); 

        if((int)me->query("sen") < 100 ) 
                return notify_fail("你的精神不足，没法子施用外功！\n"); 
        
        if((int)me->query_skill("dodge", 1) < 120) 
                return notify_fail("你的基本轻功不够娴熟，使用这一招会有困难！\n");    
        
        if((int)me->query_skill("yinfeng-zhua", 1) < 120) 
                return notify_fail("你的阴风爪不够娴熟，使用这一招会有困难！\n");             

        if((int)me->query_skill("qixiu-jian", 1) < 120) 
                return notify_fail("你的七修剑法不够熟练，使用这一招会有困难！\n"); 

        if(me->query_temp("no_kuang")) 
                return notify_fail("你累不累啊？休息一下吧！\n"); 
                
        if( time()-(int)me->query_temp("qijian_end") < 4 )    
                return notify_fail(CYN"[狂杀斩]和[夺命七剑]不能连续使用！\n"NOR);  
       
        me->delete("env/brief_message"); 
        target->delete("env/brief_message"); 

        extra=(int)me->query_skill("qixiu-jian");  
        //damagea=random((int)me->query_skill("dodge")); 
        damagea=(int)me->query_skill("dodge"); 
        if(random((int)target->query("combat_exp")) < (int)me->query("combat_exp")) 
        { 
                message_vision(HIR"$N眼中杀气爆现，一声长啸，手中利剑脱手而出。纵身跃出。 
三尺青锋游身而走，$N双爪翻飞，将全身没于剑气爪风之中。\n"NOR,me,target); 
                target->receive_damage("kee", damagea, me, "pfm"); 
                target->receive_wound("kee", damagea/2, me, "pfm"); 
                target->receive_damage("sen", damagea/3, me, "pfm"); 
                target->start_busy(2); 
                COMBAT_D->report_status(target); 
        } 
        else 
        { 
                message_vision(HIR""NOR,me,target); 
        } 
        message_vision(HIW"爪风猎猎，剑气漫天，正是陷空山无底洞七修绝学—狂杀斩\n"NOR,me,target); 
        message_vision(HIR"剑气带着爪风扑面而来，$N的攻击犹如一张无形的大网一般。\n"NOR,me,target); 
        me->add_temp("apply/attack",extra); 
        me->add_temp("apply/damage",extra); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        me->add_temp("apply/attack",-extra); 
        me->add_temp("apply/damage",-extra); 
        damage=(int)me->query_skill("sword")+random((int)me->query_skill("parry")); 
        if(random((int)target->query("combat_exp"))<(int)me->query("combat_exp")) 
        { 
                message_vision(HIR"霎时间$n被$N的狂杀斩击的遍体鳞伤，根本没有反抗的能力....\n"NOR,me,target); 
                target->receive_damage("kee",damage/2,me,"pfm"); 
                target->receive_wound("kee",damage/2,me,"pfm"); 
                COMBAT_D->report_status(target); 
        } 
        else 
        { 
                message_vision(HIW"$n见势不妙，急忙向后倒去，贴着地面平平的飞了出去，勉强避过着一招……\n"NOR,me,target); 
        } 
        me->receive_damage("sen", 30); 
        me->add("force", -100); 
        me->set_temp("no_kuang",1); 
        call_out("kuang_ok",2+random(2),me); 
        if( !target->is_fighting(me) ) { 
                if( living(target) ) { 
                        if( userp(target) ) target->fight_ob(me); 
                        else target->kill_ob(me); 
                } 
        } 
        return 1; 
} 
 
void kuang_ok(object me) 
{ 
        if (!me) return; 
        me->delete_temp("no_kuang"); 
} 


