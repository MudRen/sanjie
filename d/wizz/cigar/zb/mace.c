//ironmace.c
//created 5-30-97 pickle

#include <weapon.h>
#include <ansi.h>

inherit MACE;

void create()
{
  set_name(HIB"除"+HIR"魔"+HIC"锏"NOR, ({"chumo mace", "mace"}));
  set_weight(6000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "根");
                set("value", 200000);
                set("no_sell", "这种罕见的神兵可不是随便可以买卖的!\n");
    set("no_put",1);
    set("no_zm",1);
    set("no_give",1);
                set("no_get", 1);
                set("no_give", 1);
                set("no_put", 1);
                set("no_drop", 1);
    set("material", "iron");
    set("long", CYN"上古十二神兵之一：除魔锏\n"NOR);
    set("wield_msg", "$N操起一根$n，一股"+MAG"紫气"NOR+"缓缓从$N身上升起。\n");
    set("unwield_msg", "$N将$n别回腰间,周围的"+MAG"紫气"NOR+"渐渐淡了下来。\n");
  }
  
   init_mace(200);
  setup();
}

