// 三界神袍 by Calvin

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
  set_name(YEL"三界神袍"NOR, ({"sanjie shenpao", "cloth","pao"}));
  set_weight(4000);
  if( clonep() )
    set_default_object(__FILE__);
  else
  {
    set("long", "一件如来赠送给木惠的护身神袍。\n");
    set("material", "cloth");
    set("unit", "件");
             set("value", 0);
                set("armor_prop/armor", 80);
   set("armor_prop/dodge", 50);
    set("armor_prop/spells", 50);
    set ("armor_prop/force",20);
    set("armor_prop/parry", -20);
  }
  setup();
}
