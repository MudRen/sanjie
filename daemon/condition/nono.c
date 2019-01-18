// pk_counter.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{

        object env=environment(me);
        int damage_kee=100,damage_sen=100;
        string str = "";
        if (duration<1) return 0;
        if(env) {
// if (random(7) > 5)
str = "在"+ env->query("short") + "一带出现";
MONITOR_D->report_rumor_object_msg(me, str + "。");
            if(env->query("no_fight")&& env->query("no_magic"))
              {
                me->receive_wound("sen", damage_sen);
                me->receive_wound("kee", damage_kee);
                message_vision("天上出现一道闪电，伴随着雷声，正好劈在$N的头上。\n", me);
                me->set_temp("death_msg","被天雷劈死了。\n");
                me->apply_condition("no_pk_time", duration);
              }
                    
            else 
            me->apply_condition("no_pk_time", duration-1);
            
        }



        if( duration < 1 ) return 0;

        return CND_CONTINUE;
}
