// 日金轮（试） by Calvin

#include <armor.h>
#include <dbase.h>
#include <ansi.h>

inherit SHIELD;
inherit NECK;

void create()
{
        set_name(HIR"日精轮"NOR, ({"rjing lun","shield","rjing shield","lun","jinglun","rjing"}));
        set_weight(6000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("material", "wood");
                set("long","此乃昆仑山镇山之宝,相传是昆仑祖师月牧淇所识相传! \n
               因此而得灵气,且代代倍增。\n");
                set("value", 100000);
                set("no_sell", 1);
                set("no_give", 1);
                set("no_put", 1);
                set("no_drop", 1);
    set("armor_prop/armor", 100);
    set("armor_prop/stick", 25);
    set("armor_prop/whip", 25);
    set("armor_prop/hammer", 25);
    set("armor_prop/throwing", 25);
    set("armor_prop/rake", 25);
    set("armor_prop/sword", 25);
    set("armor_prop/unarmed", 25);
    set("armor_prop/literate", 25);
    set("armor_prop/spells", 100);
    set ("armor_prop/force", 100);
    set("armor_prop/parry", 100);
    set("armor_prop/dodge", 100);
        }
        setup();
}

int do_wear (string arg)
{
  object me = this_player();
  object zhu = this_object();
  string name = zhu->query("name");
  string msg;

if(arg!="all"&&arg != "yuejing lun" )
    return notify_fail("你要佩带什么？\n");
  msg = "$N轻声嘀咕了几句,只见$N的手心慢慢凝聚成了一只"+name+"。\n"; 
  zhu->set("wear_msg",msg);
remove_call_out("shengzhuconditions");
call_out("shengzhuconditions",1,me,zhu);
  return 0;
}

int do_remove (string arg)
{
  object me = this_player();
  object zhu = this_object();
  string name = zhu->query("name");
  string msg;

if ( arg!= "all" && arg != "sheng lingzhu")
    return notify_fail("你要干什么？\n");

  msg = "$N轻声嘀咕了几句,只见$N的手心的"+name+"渐渐淡去。\n"; 
  zhu->set("unequip_msg",msg);
remove_call_out("shengzhuconditions");
  return 0;
}

int init()
{
        object who = this_player();
        {
        if ( interactive(environment()) && 
        environment()->query("combat_exp") < 800000 )
        this_object()->move("/obj/empty"); 
         }
        add_action("do_wear","wear");
        add_action("do_remove", "remove");
}

{
        int sz;
        object *enemy;

        enemy = me->query_enemy();
        if( !enemy || !arrayp(enemy) ) return 0;

        sz = sizeof(enemy);
        if( sz > 4 ) sz = 4;

        if( sz > 0 ) return enemy[random(sz)];
        else return 0;
}

void shengzhuconditions(object who,object ob)
{
     object target;
     int ap,dp,damage;
     string msg;

string type;
type = ob->query("armor_type");
if( who->query_temp("armor/" + type) && ob->query("equipped")!="worn")
return;
  if( who->is_fighting())
     {
        target = offensive_target(who);
  if( ! target ) return ;      
 if( ! present( target,environment(who)) ) return ;    
        msg = HIR"日精轮"HIR"忽然出现在"NOR"$N"HIR"的面前,在$N周围形成一道球形护障!\n"NOR;
                ap = 5000000;
                dp = target->query("combat_exp");

                if( random(ap + dp) > dp )
                 {
                        damage = 500+random(300);
                        damage -= (int)target->query("max_mana") / 5 + random((int)target->query("eff_sen") / 5);
                        damage -= random((int)target->query("mana_factor"));

                        if( damage > 0 ) 
                        {
                                msg += HIC "结果$n一招夺面而来,却躲避不及,被日精轮的护障反抵回去。\n
日精轮一道金光,$N的防御力更高了。\n" NOR;

                                target->receive_damage("sen", damage*8/5);
                                target->receive_wound("sen", damage*2/3);
                                target->receive_damage("kee", damage*8/5);
                                target->receive_wound("kee", damage/2);
                                target->start_busy(1);
                        } 
            else
                msg += HIC "\n谁知$n闪过日精轮的护障,丝毫没有被弹伤。\n" NOR;   
                }
                else
                        msg += "但是被$n闪了过去。\n";
                message_vision(msg, who, target); 
        }
call_out("shengzhuconditions",7,who,ob);
}
