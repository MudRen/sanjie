#include <armor.h>
#include <ansi.h>
inherit SHIELD;

string *names = ({
  HIY"风盾"NOR,
  BLU"雨盾"NOR,
  CYN"雷盾"NOR,
  HIW"雪盾"NOR,
});

string *ids = ({
  "feng dun",
  "yu dun",
  "lei dun",
  "xue dun",
});

void create()
{
  int i = random(sizeof(names));
  set_name(names[i], ({ids[i], "dun", "tian dun", "shield"}));
  set_weight(1000);
  if ( clonep() )
     set_default_object(__FILE__);
  else {
   set("unit", "件");
set("value", 13000);
                set("no_give", 1);
                                set("no_drop", 1);
   set("no_put",1);
   set("no_zm",1);
   set("no_give",1);
   set("material", "skin");
   set("armor_prop/armor", 60);
               set("armor_prop/dodge", -10);
  }
   set("no_sell", "这种罕见的装备可不是随便可以买卖的!\n");
  setup();
}
