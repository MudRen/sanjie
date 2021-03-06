#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        
        object *inv, obj, obj1;
        int i, mypot,tapot;
        string str;

        object weapon;
       
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「灵犀指」？\n");

        if(!me->is_fighting())
                return notify_fail("「灵犀指」只能在战斗中使用！\n");

        if (!PFM_D->valid_family(me, "南海普陀山")) 
                return notify_fail("「灵犀指」是佛门弟子的绝学！\n");
                
        if((int)me->query("max_force") < 1000 )
                return notify_fail("你的内力不够！\n");

        if((int)me->query("force") < 600 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("你的精神不足，没法子施用外功！\n");

        i=(int)me->query_skill("jienan-zhi",1);

        if( i < 150)
                return notify_fail("你的劫难指级别还不够，使用这一招会有困难！\n");

        if( time()-(int)me->query_temp("lingxi_end") < 4 )
                return notify_fail("绝招用多就不灵了！\n");
                
        message_vision(HIY"\n$N心悟佛法，灵犀所至，缓缓伸出右手食指向$n凌空一点，一股阳和的气流向$n直逼过去。\n\n"NOR,me,target);
                
        mypot=(int)me->query_skill("unarmed");
        mypot=mypot*mypot*mypot + (int)me->query("combat_exp");

        tapot=(int)target->query_skill("parry");
        tapot=tapot+(int)target->query_skill("dodge")/10;
        tapot=tapot*tapot*tapot/10 + (int)target->query("combat_exp");

       
        if( random( mypot+tapot ) > tapot * 4/5 || !living(target) ) 
        {       
        
                message_vision(HIR"只听见「嗤」的一声轻响，$N右手食指已经在$n身上戳出一个血窟窿。\n\n"NOR,me, target);  
                COMBAT_D->do_attack_damage(me, target);
                target->receive_wound("kee",100 + me->query_str()+random(me->query_skill("unarmed")*3/5),me,"pfm");
                COMBAT_D->report_status(target);
                
                if (target->query("eff_kee")<0 || !living(target))  
                {
                        str=target->name()+"被"+me->name()+"的灵犀指力打中死穴，登时七孔流血而死。";
//                        CHANNEL_D->do_channel(me, "rumor",str);
                        me->delete_temp("last_channel_msg");
                }
                else 
                {
                        if ( random(10)>1 )
                        message_vision(HIY"\n$N的指力正正打在$n的穴道上，$n登时浑身酸麻动弹不得。\n"NOR,me,target);
                        target->start_busy(4+random(3));
                }
          
        }        
     
        else  
        {
                message_vision(HIC"$N识得厉害，连忙使一个鹞子翻身躲开了！\n"NOR, target);
                me->start_busy(2);
        }
               
        me->add("force", -50);
        me->receive_damage("sen", 50);
        me->set_temp("lingxi_end",time());
        return 1;
}


