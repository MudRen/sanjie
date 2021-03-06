//乾坤一棒
//modify by wuyou@sk_sjsh 
//2003-7-27

#include <ansi.h>
#include <combat.h>
#include "/daemon/skill/eff_msg.h";

inherit SSERVER;

string get_name(string str)
{
        str="乾坤一棒";
        return str;
}

string get_help(string str)                
{
        str="指令：ｐｅｒｆｏｒｍ　ｑｉａｎｋｕｎ\n"
        +"条件：千钧棒法150级，基本棍法150级，小无相功150级，最大内力1200，先天臂力20"
        +"威力甚居，不仅可以破坏对方的盔甲，而且能够使对方身受内伤！";
        return str;
}

int perform(object me, object target)
{
        string msg, dodge_skill;                                
        int damage, jiali, attack, defense, p;
        object armor;
      
        if( !target ) target = offensive_target(me);
     
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「乾坤一棒」？\n");
                
        if(!me->is_fighting())
                return notify_fail("「乾坤一棒」只能在战斗中使用！\n");
                
        if (!PFM_D->valid_family(me, "方寸山三星洞"))
                return notify_fail("你是哪儿偷学来的武功！\n");
                
        if( (int)me->query_skill("qianjun-bang",1) < 150 )
                return notify_fail("你的千钧棒法不够娴熟，还不会使用「乾坤一棒」！\n");
      
        if( (int)me->query_skill("stick",1) < 150 )
                return notify_fail("你的基本棍法不够娴熟，还不会使用「乾坤一棒」！\n");

        if( (int)me->query_skill("wuxiangforce",1) < 150 )
                return notify_fail("你的小无相功等级不够，不能使用「乾坤一棒」！\n");  
      
        if( (int)me->query_str() < 20 )
                return notify_fail("你的先天臂力不够强，不能使用「乾坤一棒」！\n");
      
        if( (int)me->query("max_force") < 1200 )
                return notify_fail("你的内力太弱，不能使用「乾坤一棒」！\n");
      
        if( (int)me->query("force") < 800 )
                return notify_fail("你的内力太少了，无法使用出「乾坤一棒」！\n"); 
                
        if( time()-(int)me->query_temp("qiankun_end") < 3 )
                return notify_fail("你的内息还没有平复。\n");                     
       
        if( (int)target->query_condition("qiankunyibang"))
                return notify_fail("对方早已身中「乾坤一棒」的内伤了！\n");                                                                                
      
        jiali = me->query("force_factor")+1;
        attack = me->query("combat_exp")/1000;
        attack += me->query_skill("unarmed");
        attack += me->query("force")/5;
        defense = target->query("combat_exp")/1000;
        defense += target->query_skill("dodge");
        defense += target->query("force")/7;
//      attack = (attack+random(attack+1))/2;
        attack += random(defense+1);
      
        damage = me->query_skill("qianjun-bang", 1)/20 * jiali;
        if(damage > 1000) damage = 1000;
      
        message_vision(HIR"\n$N突然面色怪异，口中爆发一声轻吼，双臂骨节一阵爆响，猛然腾空而起，双手抡起棍子向$n当空砸去，好一式"HIY"「乾坤一棒」"BLU"！\n"NOR,me,target);
 
//      if( attack > defense ) { 
        if( random( attack ) > defense/2 || !living(target) ) 
        { 
                if( objectp(armor = target->query_temp("armor/cloth"))
                && armor->query("armor_prop/armor") < 600
                && damage > 100)
                {
                        message_vision(HIY"只见这一棍正好砸在$N的$n"HIY"上，立即将它震得粉碎，裂成一块块掉在地上！\n"NOR, target, armor);
                        armor->unequip();
                        armor->move(environment(target));
                        armor->set("name", "破碎的" + armor->query("name"));    
                        armor->set("value", 0);
                        armor->set("armor_prop/armor", 0);
                        target->reset_action();
                }
                tell_object(target, RED"你只觉得霍的胸口一阵剧痛，浑身上下向散了架一样！\n"NOR);
                target->apply_condition("qiankunyibang", 1+(me->query_str()));
                target->receive_damage("kee", damage,  me, "pfm"); 
                target->receive_wound("kee", damage/2, me, "pfm");
                target->add("force",-damage);
                target->start_busy(2);
                if ((int)target->query("force")<0)
                {
                        target->set("force",0);
                        message_vision(HIR"$n一口鲜血狂喷而出！\n"NOR);
                }
                p = (int)target->query("kee")*100/(int)target->query("max_kee");
                msg = damage_msg(damage, "内伤");
                msg += "( $n"+eff_status_msg(p)+" )\n";
                message_vision(msg, me, target);
                me->add("force", -jiali);
        }
        else 
        {
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                message_vision(SKILL_D(dodge_skill)->query_dodge_msg(target, 1), me, target);
        }
//      me->add("force", -200);
//      me->start_busy(1+random(2));  
        me->set_temp("qiankun_end",time());          
        return 1;
}

 


