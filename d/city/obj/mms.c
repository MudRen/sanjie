// Created by waiwai@2000/09/16

#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
    set("no_get","你手里一松"+this_object()->query("name")+"豆豆从指间滑落！\n");
    set("no_give","这么珍贵的豆豆，哪能随便给人？\n");
    set("no_drop","这么宝贵的豆豆，扔了多可惜呀！\n");
    set("no_put","这么宝贵的豆豆，还想攥着呀，快吃吧，别坏了！\n");
    set("no_sell","凡人哪里知道"+this_object()->query("name")+"的价值？还是自己留着吧。\n");
  }                                    
  add_action("do_eat", "eat");
//    call_out("self_dest",3600+random(60),this_object());
//    remove_call_out("announce");
//    call_out("announce",random(60),this_player());

}

void create()
{
        set_name(HIR"Ｍ"HIY"＆"HIB"Ｍ"HIW"'"HIG"ｓ"NOR, ({"mms"}));
	set_weight(20);
	if (clonep())
	    set_default_object(__FILE__);
	else {
	set("unit", "颗");
	set("long", "一捧五颜六色的"+this_object()->name()+"巧克力豆，●○●○●○●○～～ 只溶在口不熔在手。\n");
	set("eat_msg", "$N拿起一颗"+this_object()->name()+"巧克力豆放进嘴里，嘻嘻地笑着说：“我还要！” \n");
	set("value", 1000000);
	set("drug_type", "补品");
	}
//  	set("is_monitored",1);

	setup();
}

int do_eat(string arg)
{
  object me = this_player();
  
  if (!id(arg))
    return notify_fail("你要吃什么？\n");
  
  me->set("food", (int)me->max_food_capacity());
  me->add_maximum_force(5);
  me->add_maximum_mana(5);
  message_vision(HIM "$N拿起一颗"+this_object()->name()+HIM"巧克力豆放进嘴里，嘻嘻地笑着说：“我还要！”  \n" NOR, me);
  
  destruct(this_object());
  return 1;
}
/*
void self_dest(object me)
{
    if(!me) return;
    if(!environment(me)) return;
    tell_object(environment(me),name()+
	    "突然落在地上，不见了。\n");
    destruct(me);
}
*/
