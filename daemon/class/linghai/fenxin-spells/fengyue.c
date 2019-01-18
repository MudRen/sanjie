//by dewbaby@sk_sjsh

#include <ansi.h>
inherit SSERVER;

int cast(object me, object target)
{
        string msg;
        int damage;
        int sp, texp;
        int exd;
        if( !target ) target = offensive_target(me);

        if((int)me->query_skill("spells") < 20 )
                return notify_fail("你的法术还不够高！\n");

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展“风月”？\n");

        if((int)me->query("mana") < 100 )
                return notify_fail("你的法力不够！\n");

        if((int)me->query("force") < 200 )
                return notify_fail("你的内力不够，这个咒语需要内力支持。\n");

        if((int)me->query("kee") < 50 )
                return notify_fail("你的气血太低，恐怕用这个不太好吧？\n");


        if((int)me->query("sen") < 150 )
                return notify_fail("你的精神没有办法有效集中！\n");

         if((int)me->query("max_mana") < 200 ) 
                return notify_fail("你法术不够。\n");

        me->add("mana", -100);
        me->receive_damage("sen", 20);

            msg = HIM
"$N凝神定气，双目水光潋滟。左手掌心朝天，右手指剑$n\n
$n"HIW"只觉眼前一片白光闪耀，动作不由地慢了下来。\n
$N突然笑问$n"HIM"：“闲步瑶阶月色昏，娉婷舞，谁可似轻云?”\n"
NOR;

        sp = me->query_skill("spells");
        exd = sp/2;
        texp = target->query("combat_exp");

        if( random(sp + texp) > texp ) {
         damage = sp/3 + (int)me->query_skill("force")/5  + random(exd);
                if( damage > 0 ) {
        msg +=  HIR "$n"HIR"呆站在原地，忽然听到$N"HIR"的问话，神情恍惚地答道：“风暖香浓似酒醇。栏杆侧，薄醉染檀唇...”\n"NOR;

         target->receive_wound("sen", damage/3,me,"cast");
         target->receive_damage("kee",damage/3,me,"cast");
          } else
          msg += HIW"结果$n"HIW"对$N"HIW"的问题毫无反应，从险中逃出！n"NOR;
          message_vision(msg, me, target);
          COMBAT_D->report_status(target);
    }

         me->start_busy(1);
        return 1;
}


