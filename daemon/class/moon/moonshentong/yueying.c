// Modified By Longer@SJSH

#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
        string msg,start;
        int ap, dp, success;
        target = offensive_target(me);
        //always use the one who is fighting me as target.

        if (!PFM_D->valid_family(me, "月宫"))
                return notify_fail("你不是月宫弟子，如何会月影？\n");
                
        if( me->is_busy())
                return notify_fail("你正忙着呢，先应付眼前的事吧。\n");

        if( (int)me->query("mana") < 100 )
                return notify_fail("你的法力不够了！\n");

        if( (int)me->query("sen") < (int)me->query("max_sen")/5 )
                return notify_fail("你精神太差，难以集中精力念咒。\n");

        if( (int)me->query_skill("moonshentong", 1) < 20)
                return notify_fail("你未曾学会月影。\n");

        if(environment(me)->query("under_water"))
                return notify_fail("你在水中，没法施用月影！\n");

        ap=me->query_skill("spells")+me->query("max_mana")/10;
        if(target) dp=target->query_skill("spells")+target->query("max_mana")/10;

        if(!me->is_fighting() )
        {
                me->add("sen", -me->query("max_sen")/8);
                me->add("mana", -80);
                message_vision(HIB"月光淡淡的抚过一片树林，\n柔和的托起了$N，\n在天际之间慢慢飞舞。\n纵情山水间，\n挥洒天地情，\n$N的身影缥缈不定的消逝在月光中。\n"NOR,me);
                success=1;
        }
        else
        {
                if(random(ap+dp)>dp/2)
                {
                        msg=HIB"月光淡淡的抚过一片树林，\n柔和的托起了$N，\n在天际之间慢慢飞舞。\n纵情山水间，\n挥洒天地情，\n$N的身影缥缈不定的消逝在月光中。\n"NOR;
                        me->add("sen", -me->query("max_sen")/6);
                        me->add("mana", -50);
                        success=1;
                }
                else 
                msg = HIG"但$n大吼一声『月亮姐姐，慢点跑，我还有话说呢』，将$N拦了下来。\n"NOR;
                me->add("mana", -50);
                message_vision(msg, me, target);
        }
        if(success)
        {
                start=me->query("env/destination");
                start=me->query("记号/"+start);
                if(!start || !find_object(start))
                        start=me->query("startroom");
                if(!start) start="/d/city/kezhan";
                me->move(start);
                message("vision", HIG+me->name()+"飘浮不定的身影出现在你面前，\n那种仰慕的感觉，\n仿佛让你忘却尘世间的红尘浪影。\n你沉寂在着缥缈的虚幻之中，\n不知何时，\n天长地久似乎已变的苍白无力，\n海枯石烂美丽却是虚无。\n"NOR,
                                  environment(me), me);
                return 3+random(3);
                tell_object(me, HIM"一道绚丽的五彩虹光洒落在你面前，\n你那婀娜多姿的身影慢慢的浮现出来，\n霎时间刀光剑影的世界沉寂在这柔和的月光中，\n是那么的清馨……\n"NOR);
        }
        return 5+random(5);
}

