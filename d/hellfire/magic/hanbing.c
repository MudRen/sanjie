// created 2002 by stey
#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit H_MAGIC_ITEM;

void create()
{
  set_name(HIW "魔法咒" NOR, ({ "scroll"}));
  set_weight(100);
          if( clonep() ) 
                 set_default_object(__FILE__); 
         else { 
                  set("long",HIY"这是一个具有特别魔法的魔法咒。\n"NOR); 
                 set("unit", "卷"); 
                 set("base_unit", "张"); 
                 set("base_weight", 5); 
                 set("value", 3); 
         } 
  set("sp_name",HIC"寒冰");//注意三项参数sp_name sp_id sp_long不变
  set("sp_id","ice scroll");  
  set("sp_long","水系普通魔法,召唤寒冰攻击的魔法咒。\n");
  set("magic_type","water"); //魔法系
  set_amount(1);
  setup();
  
}


int cast(object me, object target) //魔法咒主体lpc内容
{
        int success_adj, damage_adj; 
 

        success_adj = 110; 
        damage_adj = 100;//stey意见，80-100比较合适，130左右很厉害
 
        if( !target ) target = offensive_target(me); 
 
        if( !target 
        ||      !target->is_character() 
        ||      target->is_corpse() 
        ||      target==me) 
                return notify_fail("你要用寒冰打谁？\n"); 
 
        if(me->query("hell_type")!="精灵族"&& me->query("hell_type")!="魔法师" && me->query("hell_type")!="终结者") 
                return notify_fail( me->query("hell_type")+"不能使用水系魔法！\n"); 
 
        if((int)me->query("mana") < 25+2*(int)me->query("mana_factor") ) 
                return notify_fail("你的法力不够！\n"); 
 
        if((int)me->query("sen") < 20 ) 
                return notify_fail("你无法集中精力，别砸中自己了！\n"); 
          if(me->query("hell_type")=="魔法师")
                        damage_adj = damage_adj +35;
          if(me->query("hell_type")=="终结者")
                        damage_adj = damage_adj +10;
        me->add("mana", -25-2*(int)me->query("mana_factor")); 
        me->receive_damage("sen", 10); 
 
        if( random(me->query("max_mana")) < 50 ) { 
                write("好象没反应，再来一次吧！\n"); 
                return 1; 
        } 
 
        //HELLMAGIC_D->attacking_cast( 
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
                HIC "$N口中念了几句咒文，半空中无数集结寒冰。\n唰！地一声向$n当头罩下！\n" NOR, 
                        //initial message 
                HIC "结果打个正着，差点没把$n冻死！\n" NOR,  
                        //success message 
                HIC "但是$n在千钧一发之际化解寒冰开来。\n" NOR,  
                        //fail message 
                HIC "但是寒冰被$n以法力一引，反而罩到了$N的全身！\n" NOR,  
                        //backfire initial message 
                HIC "结果无数寒冰打个正着，差点没把$n砸死！\n" NOR 
                        //backfire hit message. note here $N and $n!!! 
        ); 
 
        me->start_busy(1+random(2));      
  

}



