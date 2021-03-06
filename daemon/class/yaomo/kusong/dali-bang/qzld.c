//by cigar 2001.12 

#include <ansi.h>
#include <combat.h>
inherit SSERVER;

string get_name(string str)
{
        str="穷追烂打";
        return str;
}

string get_help(string str)                
{
        str="指令：ｐｅｒｆｏｒｍ　ｑｚｌｄ\n"
        +"条件：大力棒100级"
        +"不仅能打掉对方的兵器，而且能够busy对方！";
        return str;
}

int perform(object me, object target)
{
        string msg;
        int extra, myexp, hisexp;
        object weapon;
        if(me->is_busy())
                return notify_fail("你现在没空！！\n");
        extra = me->query_skill("dali-bang",1) ;
        if ( extra < 100) 
                return notify_fail("你的[大力棒法]还不够纯熟！\n");

        if( !target ) target = offensive_target(me);
        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("［穷追烂打］只能对战斗中的对手使用。\n");
                
        if((int)me->query("force") < 150 ) 
                return notify_fail("你的内力不足！\n");
                
        if((int)me->query("sen") < 150 ) 
                return notify_fail("你无法集中精力！\n");
                
        me->add("force", -100);
        me->receive_damage("sen", 100);
        weapon = target->query_temp("weapon");
        myexp = (int)me->query("combat_exp");
        hisexp= (int)target->query("combat_exp");
        if(random(hisexp) < myexp*2/3 && weapon)   
        {
                message_vision(HIR "\n\n$N使出一式大力棒中的"+HIG"［穷追烂打]"+HIR"，手中的"+(me->query_temp("weapon"))->name()+HIR"变成一跟绿色露丝将$n的兵刃越缠越紧，
$n"+HIR"再怎么抓紧也无济于事了，顿时手中"+ weapon->name()+  "脱手而飞！\n\n" NOR, me,target);
                weapon->unequip();
                if( weapon->unequip()) weapon->move(environment(target));
        }
        else
        {
                message_vision(HIR "\n\n$N使出一式大力棒中的"+HIG"［穷追烂打］"+HIR"，并且对天划出一个绿色光圈"+(me->query_temp("weapon"))->name()+  HIR"将"+"$n"+HIR"越逼越紧，逼的$n到了上天绝命的地步！\n\n" NOR, me,target);
                if(random(hisexp) < myexp*2/3 )
                {
                        target->start_busy(5+random(7));
                }
                else 
                {
                        message_vision(HIY "\n$n被追得无可奈何，立定步伐，对天大叫一声"+HIW"天不绝我"+HIY"，所有不利自己的招数统统化解！\n" NOR, me, target);
                }
        }
        me->start_busy(2);
        me->improve_skill("dali-bang", 1, 1);

        return 1;
}

