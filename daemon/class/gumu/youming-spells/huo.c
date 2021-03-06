//轩辕古墓 幽明神通 幽明玄雷
#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
        int success_adj, damage_adj;

success_adj = 130;
damage_adj = 130;

        if( me->query("gender") =="男性" )
                return notify_fail("可爱的妖狐不会变臭男人的\n");

        if( !target ) target = offensive_target(me);

        if( random(me->query("max_mana")) < 850 ) {
                write("你的没有那么多法力来召唤妖狐\n");

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要召唤妖狐咬谁？\n");

        if((int)me->query("mana") < 25+2*(int)me->query("mana_factor") )
                return notify_fail("你的法力不够！\n");

        if((int)me->query("sen") < 50 )
                return notify_fail("你无法集中精力召唤！\n");

        me->add("mana", -25-2*(int)me->query("mana_factor"));
                me->receive_damage("sen", 10);

                return 1;
        }

        SPELL_D->attacking_cast(
                me, 
                        //attacker 
                target, 
                        //target
                success_adj,    
                        //success adjustment
                damage_adj,     
                        //damage adjustment
                "both",                 
                        //damage type: could be "qi"/"kee", "shen"/"sen", ...default "both"
                MAG "
$N娇媚的一笑，口中念念有词，突然从$N的身后出现无数的美女\n
$n正在差异中，只见美女渐渐靠近，霎时间变成无数黑色妖狐扑了过来\n\n" NOR,
                        //initial message
                WHT "$n大惊失措，不只如何应对，被妖狐咬的遍体鳞伤！\n" NOR, 
                        //success message
                HIC "$n不慌不忙，左手一挥，妖狐惨嚎一声，顿时灰飞烟灭！\n" NOR, 
                        //fail message
        HIC "之见$n双眼放光，大喝一声“回去”妖狐竟然折向$N！\n" NOR,
                        //backfire initial message
                HIC "结果$n反而被自己的妖狐咬的遍体鳞伤！\n" NOR
                        //backfire hit message. note here $N and $n!!!
        );

        me->start_busy(1+random(2));
        return 3+random(5);
}


