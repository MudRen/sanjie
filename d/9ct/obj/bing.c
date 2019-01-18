// 寒洛冰 by Calvin

#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
    set("no_give","这么珍贵的药，哪能随便给人？\n");
    set("no_put","寒洛冰化成一滴清水,而后蒸发了。\n");
    set("no_drop","这么宝贵的丹药，扔了多可惜呀！\n");
    set("no_sell","凡人哪里知道"+this_object()->query("name")+"的价值？还是自己留着吧。\n");
  }
  add_action("do_eat", "eat");
}

void create()
{
  set_name(HIC "寒洛冰" NOR , ({"hanluo bing", "bing","hanluobing"}));
  set_weight(90);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "块");
    set("long", "这是逸仙天特有的珍稀药材。\n");
    set("value", 0);
    set("drug_type", "补品");
  }
  set("is_monitored",1);
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  if (arg!="hanluo bing" && arg!="bing")   return 0;
  
  message_vision(HIG "$N轻轻掰开一块寒洛冰送入嘴中，一时间全身被一道亮光笼罩。\n" NOR, me);
  me->add("combat_exp",random(4000));
  destruct(this_object());
  return 1;
}

