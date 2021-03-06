// By Cigar @sjsh_SKxyj 2002-05-20
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit SSERVER;
 
int perform(object me, object target)
{
        int extra;
        object weapon,ob;
        if(me->is_busy())
                return notify_fail("你现在没空！！\n");
        extra = me->query_skill("buddha-stick",1)/5;
        if( !target ) target = offensive_target(me);
if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「九天慈悲菩萨心」只能在战斗中使用。\n");
         
    
         if( (int)me->query("force") < 1000 )
                return notify_fail("你的真气不够！\n");

              if( (int)me->query("bellicosity") > 250 ) 
              return notify_fail("你的杀气太重，无法渡出菩萨心肠。\n"); 

              if(me->query_skill("lotusforce",1) < 180) 
              return notify_fail("你的内功底子不足，无法领悟出佛门「九天慈悲菩萨心」。\n"); 
       
              if((string)me->query_skill_mapped("force")!="lotusforce") 
              return notify_fail("「九天慈悲菩萨心」必须以莲台心法为底子。\n"); 
       
              if(me->query("family/family_name")!="南海普陀山") 
                      return notify_fail("不是佛门弟子用了此招数有损真气！\n"); 

              if(me->query("bonze/class")!="bonze") 
                      return notify_fail("你没有出家，怎么能领悟其中真谛？\n"); 

              if(me->query("class")!="bonze") 
                      return notify_fail("归依我佛门，方可领悟其中真髓。\n"); 


              if((string)me->query_skill_mapped("spells")!="buddhism") 
              return notify_fail("佛门必须以佛法为中心，你要多加修行。\n"); 

              if ((int)me->query_skill("buddhism",1) < 180) 
              return notify_fail("佛门以大成为上乘法术，你修行太差，不足以。\n"); 


        if( (int)me->query_skill("buddha-stick",1) < 180 )
                return notify_fail("你的释厄棍法根基不够，无法使用「九天慈悲菩萨心」！\n");

        if( time()-(int)me->query_temp("cibei_end") < 4 )  
        return notify_fail(CYN"「九天慈悲菩萨心」对真气损耗太大,无法连续使用！\n"NOR);  
        if( (int)me->query_skill("stick",1) < 180 )
                return notify_fail("你的基本棍法火候不够，无法领悟「九天慈悲菩萨心」的精髓！\n");
        if( (int)me->query_skill("force",1) < 180 )
                return notify_fail("你的内功修为不够，无法使用「九天慈悲菩萨心」！\n");
        me->add_temp("apply/attack",extra);
        me->add_temp("apply/damage",extra);
        weapon = me->query_temp("weapon");

        message_vision(HIW "\n$N心如止水，感觉到九天之上冥冥之中赐予有无穷力量，无意之中使出了"+HIY"“九天慈悲菩萨心”！\n" NOR,me,target);
        message_vision(HIC "\n就似傍晚的遥烟，顿时天地间产生一丝苦涩，一丝怜悯，一丝惆怅．．．\n" NOR,me,target);
         message_vision(HIM  "\n  ～ 九 ～\n" NOR,me,target);
         me->set_temp("QJB_perform", 1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

         message_vision(HIY  "\n         ～ 天 ～\n" NOR,me,target);
         me->set_temp("QJB_perform", 2);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        message_vision(HIW  "\n                  ～ 慈 ～\n" NOR,me,target);
              me->set_temp("QJB_perform", 3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        message_vision(HIR  "\n                           ～ 悲 ～\n" NOR,me,target);
               me->set_temp("QJB_perform", 4);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        message_vision(HIB "\n                                    ～ 菩萨心 ～\n" NOR,me,target);
           me->set_temp("QJB_perform", 5);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
              me->delete_temp("QJB_perform");
        me->add_temp("apply/attack",-extra);
         me->add_temp("apply/damage",-extra);
        me->add("force", -200);
      me->set_temp("cibei_end",time());  

        return 1;
}
