
#include <ansi.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage,extra;
        string msg,str; 
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「暴雪天威」？\n");
        if (!PFM_D->valid_family(me, "大雪山"))
                return notify_fail("你的冰魄寒刀是从哪里偷学来的？\n");
        if(!me->is_fighting())
                return notify_fail("「暴雪天威」只能在战斗中使用！\n");
        if((int)me->query("max_force") < 500 )
                return notify_fail("你的内力不够！\n");
        if((int)me->query("force") < 500 )
                return notify_fail("你的内力不足！\n");
        if((int)me->query("sen") < 500 )
                return notify_fail("你的精神不足，没法子施用外功！\n");
        if((int)me->query_skill("bingpo-blade", 1) < 100)
                return notify_fail("你的冰魄寒刀级别还不够，使用这一招会有困难！\n");

        message_combatd(HIW"\n$N运起寒气，身形一转，四周顿时冰冻数尺，空气中寒气逼人，$n只冻的忘记的抵抗！\n"NOR,me,target,"");
        me->set_temp("noauto",1);
        target->start_busy(1);
        damage=random(((int)me->query_skill("blade")))+(int)me->query_skill("blade");

        message_combatd(HIW"\n$N嘿嘿一声冷笑，竟然隐入雪花之中。$n大急，四下找寻$N，忽然背后一阵寒气随着\n"NOR,me,target,"");
        message_combatd(HIW"\n刀光狂袭过来！！！\n"NOR,me,target,"");
        
        extra=(int)me->query_skill("bingpo-blade", 1)/2;
        me->add_temp("apply/attack", extra);
        me->add_temp("apply/damage", extra); 
                
        message_combatd(HIY"飘雪式---$N手中$n"HIY"顺着雪势使出一招！\n"NOR,me,weapon,"");
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"));
        message_combatd(HIC"排雪式---$N手中$n"HIC"犹如扑风追影反撩！\n"NOR,me,weapon,"");
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"));
        message_combatd(HIB"劈雪式---$N手中$n"HIB"夹着翩翩刀光猛劈！\n"NOR,me,weapon,"");
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"));
        
        me->add_temp("apply/attack", -extra);
        me->add_temp("apply/damage", -extra);
                
        if(random(me->query("combat_exp"))>random(target->query("combat_exp"))/4)
        {
                message_combatd(HIY"\n打斗中,一只金色大鹏鸟远远飞来！$N和$n都看呆了！\n"NOR,me,target,"");
                message_combatd(HIY"\n突然大鹏鸟用翅膀一扇,顿时狂风大作！\n"NOR,me,target,"");
                if(random(me->query("force_factor"))>target->query("force_factor")/4)
                {
                        message_combatd(HIR"\n$N见机不可失,连忙攻出一招！\n"NOR,me,target,"");
                        target->receive_damage("kee",damage*2,me,"pfm"); 
                        target->receive_damage("sen",damage*2,me,"pfm"); 
                        message_combatd(HIR"\n狂风夹杂着碎石漫天飞舞,把$n砸得遍体鳞伤！\n"NOR,me,target,"");
                        target->receive_wound("kee",damage,me,"pfm");
                        target->receive_wound("sen",damage,me,"pfm");
                        COMBAT_D->report_status(target);
                        COMBAT_D->report_sen_status(target);
                }  
                else 
                if(random(me->query("force_factor"))>target->query("force_factor")/2)
                {
                        message_combatd(HIR"\n狂风夹杂着碎石漫天飞舞,把$n砸得遍体鳞伤！\n"NOR,me,target,"");
                        target->receive_wound("kee",damage,me,"pfm");
                        COMBAT_D->report_status(target);
                }
                else  
                {
                        message_combatd(HIR"\n狂风夹杂着碎石漫天飞舞,把$N和$n砸得遍体鳞伤！\n"NOR,me,target,""); 
                        target->receive_wound("kee",damage,me,"pfm");
                        target->receive_wound("sen",damage,me,"pfm");
                        COMBAT_D->report_status(target);
                        me->receive_damage("kee",damage/10);
                        COMBAT_D->report_status(me);
                }        
        }
        me->delete_temp("noauto");
        me->receive_damage("sen", 100);
        me->add("force", -100);

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else me->kill_ob(target);
                }
        }

/*
        if (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0))  
        {
                str=target->name()+HIM"被"+me->name()+"用雪山秘传"NOR+HIW"「暴雪天威」"+HIM"杀死了，据说"+target->name()+"的尸体被封印在一个巨大的"NOR+HIW"冰棺"+HIM"里面！";
                message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
        }
*/        
        me->start_busy(2);
        
        return 1;
}


