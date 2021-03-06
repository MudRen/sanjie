#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
        string msg,start;
        int ap, dp, success;
        target = offensive_target(me);
        //always use the one who is fighting me as target.

        if( me->is_busy())
                return notify_fail("你正忙着呢，先应付眼前的事吧。\n");

        if( (int)me->query("mana") < 100 )
                return notify_fail("你的法力不够了！\n");

        if( (int)me->query("sen") < (int)me->query("max_sen")/5 )
                return notify_fail("你精神太差，难以集中精力念咒。\n");

        if( (int)me->query_skill("seashentong", 1) < 70)
                return notify_fail("你未曾学会水遁。\n");

        ap=me->query_skill("spells")+me->query("max_mana")/10;
        if(target) dp=target->query_skill("spells")+target->query("max_mana")/10;

        if(!me->is_fighting() )
        {
                message_vision(HIC"\n\n$N的脚下突然涌起一股水波，水流过后，$N随之不见了！\n\n"NOR,me);
                me->add("sen", -me->query("max_sen")/8);
                me->add("mana", -80);
                success=1;
        }
        else
        {
                msg=HIC"\n\n$N的脚下突然涌起一股水波，水流过后，$N随之不见了！\n\n"NOR;
                if(random(ap+dp)>dp/2)
                {
                        msg+=HIC"\n\n只听$N喝了一声「 龙王速速释水！」，$N人影已经不见了。\n\n"NOR;
                        me->add("sen", -me->query("max_sen")/6);
                        me->add("mana", -50);
                        success=1;
                }
                else msg+=HIR"\n\n$N的脚下突然涌起一股水波，却被$n识破，$N没能跑掉！。\n\n"NOR;
                me->add("mana", -50);
                message_vision(msg, me, target);
        }
        if(success)
        {
                start=me->query("env/destination");
                start=me->query("记号/"+start);
                if(!start || !find_object(start))
                        start=me->query("startroom");
                if(!start) start="/d/sea/yujie2";
                me->move(start);
                message("vision", HIC+me->name()+"从一阵雾水之中走了出来，浑身还湿淋淋的。\n\n"NOR,
                                  environment(me), me);
                tell_object(me, HIG"\n\n你的龙形之影出现在一雾气中慢慢的显现出来。\n\n"NOR);
                return 3+random(3);
        }
        return 5+random(5);
 }
