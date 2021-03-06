//wuyou@sk_sjsh
//2003-3-13
//考虑到法术的伤害判断比较麻烦
//伤害数值变动太大
//我用了法术里命中判断的一般规则
//而伤害却使用了pfm中的判断方法
//考虑到如果反弹，这个cast的实用价值也就不是太大了


#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
        string msg;

        string tar_spells,tar_dodge;

        int ap,dp,dg,damage,chance,skills1,skills2;

        if( !target ) target = offensive_target(me);

        if( !target
        ||   !target->is_character()
        ||   target->is_corpse()
        ||   target==me)
                return notify_fail("你要对谁用五行天雷？\n");
  
//        if( target->is_player() )
//                return notify_fail("五行天雷目前不允许对玩家使用。\n");

        if (!target->is_fighting(me))
               return notify_fail("只有在战斗中才能使用五行天雷！\n");

        if((int)me->query("kee") < 200 )
                return notify_fail("你体力不足，用不了五行天雷！\n");

        if((int)me->query("force") < 200 )
                return notify_fail("你须运足内力才能使用五行天雷！\n");

        if((int)me->query_skill("buddhism", 1) < 430 )
                return notify_fail("你的大乘佛法还不够纯熟。\n");

        if((int)me->query_skill("spells", 1) < 430 )
                return notify_fail("你的基本法术还不够纯熟。\n");

        if((int)me->query("mana") < 500 )
                return notify_fail("你的法力不足以召唤五行天雷御敌！\n");

        msg = HIC"\n$N双目怒视$n，口中念道“般若波罗密，五雷天将助我伏魔！”
$N突然伸手一挥，刹那间，风起云涌，浓云密布，隐隐云端站着五雷天将。\n\n" NOR;

/*****************************************************************************/
/*第一击*/
        msg +=HIY "   ┏━┓\n";
        msg +=HIY "   ┃金┃\n";
        msg +=HIY "   ┗━┛\n\n"; 
        msg +=HIY "伴随着电闪雷鸣，一道金光化作一把利剑射向$n。\n"NOR;
 
        ap=(int)me->query_skill("buddhism", 1)
              +(int)me->query_skill("spells", 1)/2;

        tar_spells=target->query_skill_mapped("spells");
        if (! tar_spells) dp=(int)target->query_skill("spells", 1)/2;
        else dp=(int)target->query_skill("spells", 1)/2
              +(int)target->query_skill(tar_spells, 1);

        tar_dodge=target->query_skill_mapped("dodge");
        if (! tar_dodge) dg=(int)target->query_skill("dodge", 1)/2;
        else dg=(int)target->query_skill("dodge", 1)/2
              +(int)target->query_skill(tar_dodge, 1);
        if (dp!=0) dp=100*ap/dp/3+random(100*ap/dp)/2; else dp=100;
        if (dg!=0) dg=100*ap/dg/3+random(100*ap/dg)/2; else dg=100;

        damage=me->query("max_mana")/20+1;
        damage=(me->query("mana_factor")+me->query("str")+random(damage))*2;
        if (dp<30)
          {           
          msg += HIC "$n连忙后退将$N的金光逼开。\n"NOR;
          message_vision(msg, me, target);
          }
        else if (dg<50)
          {           
          msg += HIC "$n纵身向后一跃，闪过了这一击。\n"NOR;
          message_vision(msg, me, target);
          }
        else 
          {           
          msg += HIC "$n眼看着金光罩来，竟没法逼开，被金雷神将的金光牢牢罩住，$N连忙再出一道金光，"
              +"$n被劈了个正着！\n"NOR;
          message_vision(msg, me, target);
          target->receive_damage("kee",damage,me,"cast");
          target->receive_wound("kee",damage,me,"cast");
          if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",damage));
          COMBAT_D->report_status(target); 
          }
/***************************************************************************************/
/*第二击*/      
        msg = HIG "   ┏━┓\n";
        msg +=HIG "   ┃木┃\n";
        msg +=HIG "   ┗━┛\n\n"; 
        msg +=HIG "天空雷声阵阵，木雷神将化身点点绿光冲向$n。\n"NOR;
        
         damage = (int)(random(me->query_skill("spells")/20)) + (int)(me->query_skill("spells")/20)+ 1;
        ap = me->query_skill("spells");
        ap =  ap * ap * ap / 100;
        dp = target->query("combat_exp")* 4 /5;
        if( dp<1 ) dp = 1;
        chance = (int)(random(ap + dp) * 100 / dp);
        if( chance > 66 ) 
        {
            damage = damage * 20 ;
            msg += HIC "结果$n被点点绿光透身而过！\n" NOR;
            target->receive_wound("kee", damage, me);
            target->receive_damage("kee",damage,me);
            if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",damage));
           
         }
         else if ( chance > 33 ) 
        {
            damage = damage * 10 ;
            msg += HIC "$n左躲右闪，但还别绿光擦身而过！\n" NOR;
            target->receive_wound("kee", damage,me,"cast");
            target->receive_damage("kee",damage,me,"cast");
            if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",damage));   
         } 
         else{
         msg += "但是被$n全躲开了。\n";
         }
         message_vision(msg, me, target);
         if( damage > 0 ) COMBAT_D->report_status(target);
         else if( damage < 0 ) COMBAT_D->report_status(me);
/*******************************************************************************/
/*第三击*/
        msg = HIW "   ┏━┓\n";
        msg +=HIW "   ┃水┃\n";
        msg +=HIW "   ┗━┛\n\n"; 
        msg +=HIW "水雷神将翻手为云，覆手为雨，倾盆大雨夹杂着冰刀迅猛而至。\n"NOR;

        ap=(int)me->query("daoxing",1);
        dp=(int)target->query("daoxing",1);
        skills1=(int)me->query_skill("spells",1);
        skills1=skills1*skills1*skills1/10;
        skills2=(target)->query_skill("spells",1);
        skills2=skills2*skills2*skills2/10;
        damage = (int)(me->query_skill("buddhism"))+ 1;
        if( random(ap+skills1) > (dp+skills2)/4 ) 
        {       
                msg += HIC"$n被冰刀戳的体无完肤！\n"NOR;
                target->receive_damage("kee", damage,me,"cast");
                target->receive_wound("kee", damage,me,"cast");
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",damage));
                message_vision(msg, me, target);
                COMBAT_D->report_status(target,0);
         }
         else{
         msg += HIC"$n周围形成一个法力盾，没有受到丝毫伤害。"NOR;
         message_vision(msg, me, target);
        }

/**************************************************************************************/
/*第四击*/  

        msg = HIR "   ┏━┓\n";
        msg +=HIR "   ┃火┃\n";
        msg +=HIR "   ┗━┛\n\n"; 
        msg +=HIR "火雷神将双掌并力将一巨大的火球推向$n！\n"NOR;
        ap = me->query_skill("buddhism");
        ap = ( ap * ap /100 * ap / 4 ) * (int)me->query("sen") ;
        dp = target->query("combat_exp");
        if( random(ap + dp) > dp ) {
                damage = (me->query_skill("spells")+ me->query_skill("buddhism"))/2 ;
                msg +=  HIC "火球在$n的身上炸开了！\n" NOR;
           
                target->receive_damage("kee", damage,me,"cast");
                target->receive_wound("kee", damage,me,"cast");
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",damage));
                message_vision(msg, me, target);
                if( damage > 0 ) COMBAT_D->report_status(target);

        } else
                {
                msg += HIC"但是被$n巧妙的躲开了！！\n";
                message_vision(msg, me, target);
                }      

/*****************************************************************************************/
/*第五击*/

        msg = MAG "   ┏━┓\n";
        msg +=MAG "   ┃土┃\n";
        msg +=MAG "   ┗━┛\n\n"; 
        msg +=MAG "土雷神将将五岳之峰搬到空中，砸向$n！\n"NOR;

        ap = me->query_skill("spells");
        ap = ( ap * ap * ap / (4 * 400) ) * (int)me->query("sen");
        ap += (int)me->query("combat_exp");
        dp = target->query("combat_exp");
        if( random(ap + dp) > dp /4) {
                
                damage = (me->query_skill("spells")+ me->query_skill("buddhism"))/2 + random((me->query_skill("spells")+ me->query_skill("buddhism"))/2) ;

                if( damage > 0 ) {

                        msg += HIC "结果$n被砸个正着，顿时血花飞溅，受伤不轻！\n" NOR;
                        target->receive_damage("sen", damage,me,"cast");
                        target->receive_wound("sen", damage,me,"cast");
                        target->receive_damage("kee", damage,me,"cast");
                        target->receive_wound("kee", damage,me,"cast");
                        if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",damage));
                }

             } 
        else
             {
                         msg += HIC"但是$n不费吹灰之力又将五岳搬回了原处。\n";
              }

        message_vision(msg, me, target);
        if( damage > 0 ) COMBAT_D->report_status(target);
        else if( damage < 0 ) COMBAT_D->report_status(me);


         me->add("force", -500);
         me->add("mana", -500);

         if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else
                        me->kill_ob(target);
                }
                me->kill_ob(target);
        }

         me->start_busy(2);

         return 1;
}

