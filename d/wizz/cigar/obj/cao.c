// 千绝草 by Calvin

#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
    set("no_give","这么珍贵的药，哪能随便给人？\n");
    set("no_put","千绝草化成一滴清水,而后消失了。\n");
    set("no_drop","这么宝贵的丹药，扔了多可惜呀！\n");
    set("no_sell","凡人哪里知道"+this_object()->query("name")+"的价值？还是自己留着吧。\n");
  }
  add_action("do_eat", "eat");
}

void create()
{
  set_name(HIG "千绝草" NOR , ({"qianjue cao", "qianjuecao","cao"}));
  set_weight(90);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "棵");
    set("long", "这是精华台特有的珍稀药材。\n");
                set("value", 400000);
                set("no_sell", "这种罕见的草药可不是随便可以买卖的!\n");
    set("drug_type", "补品");
  }
  set("is_monitored",1);
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  if (arg!="qianjue cao" && arg!="cao")   return 0;
  
  me->add("max_force",(random(10)+90));
  me->add("max_mana",(random(10)+90));
//      me->add("max_kee",(random(1)+9));
//      me->add("max_sen",(random(1)+9));
//        me->add("daoxing",(random(1000)+1000));
//       me->add("combat_exp",(random(25000)+5000));
  me->set("food", (int)me->max_food_capacity()*2+random(100));
  me->set("water", (int)me->max_water_capacity()*2+random(100));
  message_vision(HIG "$N轻轻地将一颗千绝草送入嘴中，一时间全身被一道绿色光笼罩。\n" NOR, me);
  destruct(this_object());
  return 1;
}

