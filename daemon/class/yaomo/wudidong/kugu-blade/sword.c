
#include <ansi.h>

inherit SSERVER;

string get_name(string str)
{
        str="刀光剑影";
        return str;
}

string get_help(string str)                
{
        str="指令：ｐｅｒｆｏｒｍ　ｓｗｏｒｄ\n"
        +"条件：枯骨刀法180级，七修剑法180级，最大内力1000";
        return str;
}

int perform(object me, object target)
{
        
        object *inv, obj, obj1;
        int i, j, mypot, tapot;
        string str;

        object weapon1, weapon2;
       
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「刀光剑影」？\n");

        if(!me->is_fighting())
                return notify_fail("「刀光剑影」只能在战斗中使用！\n");

        if (!PFM_D->valid_family(me, "陷空山无底洞"))
                return notify_fail("你那里偷来的绝技？\n"); 
                
        if((int)me->query("max_force") < 1000 )
                return notify_fail("你的内力不够！\n");

        if((int)me->query("force") < 600 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("你的精神不足，没法子施用外功！\n");

        i=(int)me->query_skill("kugu-blade",1);
        j=(int)me->query_skill("qixiu-jian",1);
        
        if( i < 180)
                return notify_fail("你的枯骨刀法还不够纯熟，使用这一招会有困难！\n");
                
        if( j < 180)
                return notify_fail("你的七修剑法还不够纯熟，使用这一招会有困难！\n");

        if( time()-(int)me->query_temp("wddsword_end") < 4 )
                return notify_fail("“刀光剑影”用多了就不灵了。\n");

        if (me->query_temp("xieji_busy")) 
                return notify_fail("[刀光剑影]与[血祭]不能连续使用!\n");
                
        weapon1=me->query_temp("weapon");
        weapon2=present("sword", me);
        if(!objectp(weapon2)) 
                return notify_fail("你就一把刀怎么用「刀光剑影」？\n");

                
        message_vision(MAG"\n$N对$n冷哼一声，双目精光一现，左手"+weapon2->query("name")+MAG"，右手"+weapon1->query("name")+MAG"，
近乎疯狂的使出了"HIW"「枯骨刀－－刀光剑影」"NOR""MAG"这最阴险、毒辣的一招。
顿时天风阴阴，地谷森森，整个大地笼罩在$N无比锋利的刀光剑影之中。\n\n"NOR,me,target);
                
        mypot=(int)me->query_skill("kugu-blade");
        mypot=mypot*mypot*mypot + (int)me->query("combat_exp");

        tapot=(int)target->query_skill("parry");
        tapot=tapot+(int)target->query_skill("dodge")/10;
        tapot=tapot*tapot*tapot/10 + (int)target->query("combat_exp");

       
        if( random( mypot+tapot ) > tapot/4 || !living(target) ) 
        {               
                message_vision(MAG"\n只见$n顿时馅入风雨飘摇之间，$N强大的刀气将$n逼退了三步，样子十分狼狈！\n\n"NOR,me, target);  
                COMBAT_D->do_attack_damage(me, target);
                target->receive_wound("kee", random(me->query_skill("blade")*3/2), me, "pfm");
                COMBAT_D->report_status(target);
                
                if (target->query("eff_kee")< -100 || !living(target))  
                {
                        str=target->name()+"被"+me->name()+"的「刀光剑影」杀死，尸体都无处寻觅。";
                        CHANNEL_D->do_channel(me, "rumor",str);
                        me->delete_temp("last_channel_msg");}
                else 
                {
                        if ( random(10)>1 )
                        {
                                message_vision(MAG"\n\n$N见到$n摇摇欲坠，挥舞刀剑乘胜追击，誓把$n置于死地。\n"NOR,me,target);
                                COMBAT_D->do_attack_damage(me, target);
                                target->receive_wound("kee", random(me->query_skill("qixiu-jian")*3/2), me, "pfm");
                                COMBAT_D->report_status(target);
                                if(!target->is_busy())
                                        target->start_busy(2+random(2));
 
                        }
          
                }
        }        
     
        else  
        {
                message_vision(HIY"$N见$n来势汹汹，不敢以卵击石，连忙后撤，躲开了$n的攻击！\n"NOR, target, me);
         
        }
               
        me->add("force", -150);
        me->receive_damage("sen", 50);
        me->set_temp("wddsword_end",time());
        return 1;
}

