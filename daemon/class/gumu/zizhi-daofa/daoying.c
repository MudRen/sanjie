//刀影连身
//by junhyun@sk

#include <ansi.h>
#include <combat.h>

inherit SSERVER;

int perform(object me, object target)
{
      object weapon=me->query_temp("weapon");
      int enhance,damage;
      string str;

      if (!weapon) return 0;
      if( !target ) target = offensive_target(me);
      if( !target || !target->is_character()||target->is_corpse()||target==me)
          return notify_fail("你要攻击谁？\n");
      if (!me->is_fighting())
             return notify_fail("刀影连身只能在战斗中使用！\n");
           
     if( time()-(int)me->query_temp("daoying_end") < 5 )
                   return notify_fail("你现在真气不纯。\n");      
     if(me->query("family/family_name") != "轩辕古墓")
                return notify_fail("[刀影连身]是轩辕古墓不传之密！\n");
      if (me->query_skill("jiuyin-zhua",1)<60) 
          return notify_fail("你的九阴白骨爪等级不够。\n");                
     if (me->query_skill("zizhi-blade",1)<60)
          return notify_fail("你的紫雉刀法太差，还不会出刀影连身。\n");
    if (me->query_skill("jiuyin-force",1)<60)
        return notify_fail("你的九阴真精修为不够，还不会出刀影连身。\n");
     if (me->query_skill_mapped("force")!="jiuyin-force")
            return notify_fail("没有九阴真力如何使用刀影连身。\n");
     if (me->query_skill_mapped("unarmed")!="jiuyin-zhua")
            return notify_fail("刀影连身是全面的功夫，没有九阴爪是不行的。\n");
      if (me->query("force")<150)
           return notify_fail("你内力不继，难以出招。\n");
    message_vision(HIW"\n
$N默运九阴真力，刀爪齐施，晃晃刀影中，夹杂着无数爪风。

霎时间，风走沙滚，刀光爪影，当真是刀刀连身，爪爪要命"NOR,me);
    //weapon->unequip();
    weapon->set_temp("original/use_apply_skill",weapon->query("use_apply_skill"));
    weapon->set_temp("original/skill_type",weapon->query("apply/skill_type"));
    weapon->set("use_apply_skill",1);
    weapon->set("apply/skill_type","unarmed");
    enhance=me->query_skill("jiuyin-zhua",1);
    me->add_temp("apply/attack", enhance);  
    damage=me->query_skill("jiuyin-force",1);
    damage=damage/2;
    me->add_temp("apply/damage",damage);        
    COMBAT_D->do_attack(me, target);
    weapon->set("use_apply_skill",weapon->query_temp("original/use_apply_skill"));
    weapon->set("apply/skill_type",weapon->query_temp("original/skill_type"));
    me->add_temp("apply/attack",-enhance);
    me->add_temp("apply/damage",-damage);
    //weapon->wield();
    if (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0))  
                       {str=target->name()+"被"+me->name()+"用轩辕古墓绝招「刀影连身」砍死了，尸体上留下无数的刀口爪痕！";
                         message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
                       }
    me->reset_action();
    me->set_temp("daoying_end",time());
    return 1;
}


