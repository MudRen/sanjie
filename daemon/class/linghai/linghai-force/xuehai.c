//linghai-force
//血杀

#include <ansi.h>

inherit SSERVER;

int exert(object me, object target)
{
        int lh;
        int lhh;
        int tg;

        if( !me->is_fighting() )
                return notify_fail("只能在战斗中对敌人使用！\n");

        if(!target)target = offensive_target(me);
        if(target==me) target = offensive_target(me);

        if( (int)me->query("force") < 600 )
                return notify_fail("你的内力不够。\n");
  
        lh = me->query_skill("linghai-force",1);

        if( lh < 120 )
                return notify_fail("你的【凌海心法】火候不够，使不出【血海无边】!\n");

        lhh = me->query_skill("force")+me->query_skill("spells");
        message_vision(HIR+"$N嘿嘿一笑，回身对着$n就是一掌。\n\n"HIR"$N与$n四掌相接，两人头顶真气袅袅，不知会有什么结果..\n"+NOR,me,target);

        if(random((me->query("combat_exp")))>(int)target->query("combat_exp")/3 )
{
     message_vision(
                HIB +
"$N"HIB"只觉得胸口一阵疼痛，忙收回双掌，疼痛却越来越厉害！\n"+NOR,target,me);
        target->receive_damage("kee",target->query_skill("force")/2+110,me,"pfm");
        target->receive_wound("kee",lhh,me,"pfm");
        target->start_busy(3+random(4));
      me->add("force",-200);
      me->add("sen",-80);
}
else
{
         message_vision(
                HIY +
"$n仗着内力混厚，毫不费力地逃过此劫。\n"+NOR,me,target);
}
        me->add("force", -400);
        me->start_busy(1+random(2));

        return 1;
}


