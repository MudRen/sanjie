//tougu.c 神爪透骨
// by junhyun@SK
 
#include <ansi.h>
 
inherit SSERVER;
 
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;
        int force_wound, kee_wound ;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("jiuyin-zhua",1);

        if( !(me->is_fighting() ))
                return notify_fail("「神爪透骨」只能对战斗中的对手使用。\n");

        if (!PFM_D->valid_family(me, "轩辕古墓"))
return notify_fail("不是古墓弟子怎么会白骨爪？\n");

        if( skill < 80)
                return notify_fail("你的「九阴白骨爪」等级不够, 不能使出「神爪透骨」！\n");

        if( me->query("force") < 200 )
                return notify_fail("你的内力不够，无法运功！\n");
 
        msg = HIW "
$N突然脸色苍白，眼神中显出一丝戾气，一声清啸你越起数丈，居高临下
五指箕张，向着$n直扑而来，正是九阴白骨爪绝学——"+HIB"「神爪透骨」
\n"NOR;

        message_vision(msg, me, target);

        ap = me->query("combat_exp") + skill * 800;
        dp = target->query("combat_exp") ;

        if( dp < 1 )
                dp = 1;
        if( random(ap+dp) > (dp*5/7) )
        {
                if(userp(me))
                        me->add("force",-100);

                msg = HIW "
$n突然觉得左腿一凉，一股寒气直窜丹田，低头一看，左腿上已被$N抓出五个血洞！
！\n"NOR;

                force_wound = 200 + random(skill)*3;
                if(force_wound > target->query("force"))
                        force_wound = target->query("force");


                    kee_wound = force_wound /2;
                              
                if(kee_wound > target->query("eff_kee"))
                        kee_wound = target->query("eff_kee");

         if(kee_wound<0) kee_wound=100;
                target->receive_damage("kee", kee_wound,me,"pfm");
                target->receive_wound("kee", kee_wound/3,me,"pfm");
//                target->start_busy(2+random(2));
                me->start_busy(random(2));
                target->start_busy(random(3));
             

       }
        else
        {
                msg = HIW "$n慌忙中翻倒在地，就势一滚，狼狈的躲开了$N的猎猎爪风！\n"NOR;
                if(userp(me))
                        me->add("force",-70);
                me->start_busy(2);
        }
        message_vision(msg, me, target);

        return 1;
}


