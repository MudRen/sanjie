// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// 欢乐棒 huanlebang.c
// lizuole 99.12.16

#include <weapon.h>

inherit STICK;

void create()
{
   set_name("欢乐棒", ({"huanle bang", "bang"}));
   set_weight(10000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("unit", "根");
     set("value", 5000);
     set("material", "steel");
     set("long", "一把淡绿色的玉棒，入手滑腻，颇有些份量。\n");
     set("wield_msg", "$N拿起一根$n，顺手舞了个棍花。\n");
     set("unwield_msg", "$N哼了一声，将$n插回后腰。\n");
   }
   init_stick(45);
   setup();
}
