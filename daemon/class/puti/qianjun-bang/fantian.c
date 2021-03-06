#include <ansi.h>

inherit SSERVER;

string get_name(string str)
{
        str="翻天覆地";
        return str;
}

string get_help(string str)                
{
        str="指令：ｐｅｒｆｏｒｍ　ｆａｎｔｉａｎ\n"
        +"条件：千钧棒法150级，最大内力1000"
        +"威力自揣，但是与拜佛五式合用威力惊人！";
        return str;
}

int perform(object me, object target)
{
        
        object *inv, obj, obj1;
        int i, mypot, tapot, damage;
        string str;

        object weapon;
       
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「翻天覆地」？\n");

        if(!me->is_fighting())
                return notify_fail("「翻天覆地」只能在战斗中使用！\n");

        if (!PFM_D->valid_family(me, "方寸山三星洞"))
                return notify_fail("你那里偷来的绝技？\n"); 
                
        if((int)me->query("max_force") < 1000 )
                return notify_fail("你的内力不够！\n");

        if((int)me->query("force") < 600 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("你的精神不足，没法子施用外功！\n");

        i=(int)me->query_skill("qianjun-bang",1);

        if( i < 150)
                return notify_fail("你的棒法还不够，使用这一招会有困难！\n");

        if( time()-(int)me->query_temp("fantian_end") < 4 )
                return notify_fail("“翻天覆地”哪里有老用的道理？\n");
                
        message_vision(HIY"\n$N手指$n愤恨道：“对我不仁尔等小命休以”，一语道罢，$N气运丹田，力灌掌心，使出「翻天覆地」。\n\n"NOR,me,target);
                
        mypot=(int)me->query_skill("qianjun-bang");
        mypot=mypot*mypot*mypot + (int)me->query("combat_exp");

        tapot=(int)target->query_skill("parry");
        tapot=tapot+(int)target->query_skill("dodge")/10;
        tapot=tapot*tapot*tapot/10 + (int)target->query("combat_exp");

       
        if( random( mypot+tapot ) > tapot/5 || !living(target) ) 
        {               
                message_vision(HIR"\n只见$n硬生生的接住$N这技绝招，顿感喉头一甜，[噗]的一声吐出一口鲜血。\n\n"NOR,me, target);  
                COMBAT_D->do_attack_damage(me, target);
                damage = random(me->query_skill("stick")) + me->query_skill("stick");
                target->receive_wound("kee", damage, me, "pfm");
                COMBAT_D->report_status(target);
                
/* 去掉rumor
                if (target->query("eff_kee")< -100 || !living(target))  
                {
                        str=target->name()+"被"+me->name()+"的「翻天覆地」震死，魂魄都无处寻觅。";
                        CHANNEL_D->do_channel(me, "rumor",str);
                        me->delete_temp("last_channel_msg");}
                else 
                {
  */
                        if ( random(10)>1 )
                        {
                                message_vision(HIR"\n\n$N见到$n受伤不轻，乘胜追击，又出一技“翻云覆雨”，$n的七魂六魄早已少去一半。\n"NOR,me,target);
                                COMBAT_D->do_attack_damage(me, target);
                                damage = random(me->query_skill("parry")) + me->query_skill("parry");
                                target->receive_wound("kee", damage, me, "pfm");
                                COMBAT_D->report_status(target);
                                target->start_busy(1+random(2));
                                message_vision(HIR"\n$N甩出千钧棒最后一技，想致$n于死地。\n"NOR,me,target);
                                me->set_temp("QJB_perform", 6);
                                COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
                                me->delete_temp("QJB_perform");
                        }
          
// }
        }        
     
        else  
        {
                message_vision(HIC"$N识破此招，气运丹田，以力抗力硬接此绝招！\n"NOR, target);
                //me->start_busy(2);
        }
               
        me->add("force", -150);
        me->receive_damage("sen", 50);
        me->set_temp("fantian_end",time());
        return 1;
}


