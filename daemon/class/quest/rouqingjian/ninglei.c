//饶指柔情剑 【凝泪决】
//by junhyun@SK

#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int i,j;
                
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招【凝泪决】？\n");

        if(!me->is_fighting())
                return notify_fail("【凝泪决】只能在战斗中使用！\n");

        if((int)me->query("force") < 100 )
                return notify_fail("你的内力不够！\n");

        if((int)me->query("kee") < 100 )
                return notify_fail("你的气血不足，没法子施用外功！\n");

        if((int)me->query_skill("rouqingjian", 1) < 150)
                return notify_fail("你的饶指柔情剑级别还不够，无法使用【凝泪决】！\n");

               weapon=me->query_temp("weapon");

        if( me->query("env/brief_message") ){
                i=1;
        } else {
                i=0;
        }
        if( target->query("env/brief_message") ){
                j=1;
        } else {
                j=0;
        }

        me->delete("env/brief_message");
        target->delete("env/brief_message");

        message_vision(HIW"
你剑势越舞越快，剑气四射，寒光逼人，突然一声长啸，剑光如
滑落的泪滴般洒下来，在天际中划出一道优美的弧线，思念了眼
泪化作无边的剑气
\n\n\n"NOR, me);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
 message_vision(HIW"☆凝☆\n"NOR, me);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
 message_vision(HIW"☆泪☆\n"NOR, me);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
 message_vision(HIW"☆决☆\n"NOR, me);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
 message_vision(HIW""NOR, me); 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

                if( i ) me->set("env/brief_message", 1);
        if( j ) target->set("env/brief_message", 1);

        me->receive_damage("kee", 100);
        me->add("force", -10);

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }

        me->start_busy(1);
        return 1;
}

