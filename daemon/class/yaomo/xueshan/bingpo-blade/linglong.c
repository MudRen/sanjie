 
#include <ansi.h>
inherit SSERVER;

string get_name(string str)
{
        str="雪玲珑";
        return str;
}

string get_help(string str)                
{
        str="指令：ｐｅｒｆｏｒｍ　ｌｉｎｇｌｏｎｇ\n"
        +"条件：冰魄寒刀250级，冰谷凝血功200级，最大内力1000"
        +"惊天一击，威力无穷";
        return str;
}

int perform(object me, object target)
{
        string msg;
        int damage, ap, dp;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展「雪玲珑」？\n");
        if (!PFM_D->valid_family(me, "大雪山"))
                return notify_fail("你不是大雪山弟子，怎么能使用大雪山绝技？\n");
        if(environment(me)!=environment(target))
                return notify_fail("你现在没有了攻击目标!\n");
        if((string)me->query_skill_mapped("force")!="ningxie-force")
                return notify_fail("雪玲珑要以冰谷凝血功为底子。\n");
        if((int)me->query("force") < 65+(int)me->query("force_factor") )
                return notify_fail("你的内力不足！\n");
        if(me->query("max_force") < 1000 || me->query("force")<500)
                return notify_fail("内力不足，根本无法发挥雪玲珑的威力。\n");
        if((int)me->query("kee") < 100 )
                return notify_fail("你身体太虚弱了，无法施展「雪玲珑」！\n");
        if((int)me->query_skill("bingpo-blade", 1) <250)
                return notify_fail("你的冰魄寒刀练得不够纯熟，无法使出这招「雪玲珑」！\n");
        if((int)me->query_skill("ningxie-force", 1) <200)
                return notify_fail("你对冰谷凝血功领悟尚浅，不能使出「雪玲珑」！\n");
        me->add("force", -65-(int)me->query("force_factor"));
        msg = HIW
 "\n$N身影慢慢的浮现在你面前，只见$N洒出无数晶莹剔透的"RED"雪玲珑"NOR"\n"HIW"围绕在你周围，刀光剑影的世界霎时间沉寂在这柔和的雪光之中，好一记温柔\n缠绵的"HIG"玲珑雪"NOR"\n"HIM"纵情山水间，挥洒天地情!\n"NOR;

        ap = me->query_skill("bingpo-blade", 1);
        ap = ( ap * ap * ap / (3 * 350) );
        ap = ap*250 + (int)me->query("combat_exp");
        dp = target->query_skill("parry");
        dp = ( dp * dp * dp / (7 * 400) );
        dp = dp*250 + target->query("combat_exp");
        //if( random((ap + dp)/800+1) <  dp/2200 ) 
        if( random((ap + dp)/600+1) <  dp/2500 ) 
        {
                msg += HIY "可$n并没有被这绚丽的雪景所吸引,依然屹立在雪花飞舞的幻景中！\n\n"NOR;
                message_combatd(msg, me, target, "");
        } 
        else 
        {
                damage = (int)me->query_skill("bingpo-blade",1) / 8 +
        (int)me->query("sen") / 200 + random((int)me->query("sen") / 150 ) +
        (int)me->query("kee") / 200 + random((int)me->query("kee") / 150 );
                msg += HIR "\n$n顿时沉寂在这梦一般的景象之中，如痴如醉中被雪玲珑击中了！\n\n" NOR;
                damage +=random(10);
                target->receive_damage("sen", me->query("eff_sen")*damage/100, me, "pfm");
                target->receive_damage("kee", me->query("eff_kee")*damage/80, me, "pfm");
                target->receive_wound("kee", me->query("eff_kee")*damage/200, me, "pfm");
                me->improve_skill("bingpo-blade", 1, 1);
                message_combatd(msg, me, target, "");
                COMBAT_D->report_status(target);
        }
        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else me->kill_ob(target);
                }
        }
        me->start_busy(2);
        return 1;
}

