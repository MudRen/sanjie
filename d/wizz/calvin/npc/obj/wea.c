#include <armor.h>
#include <ansi.h>
inherit SURCOAT;

void create()
{
  set_name(HIW"流云"NOR, ({"wea"}));
  set_weight(4500);
  if( clonep() )
    set_default_object(__FILE__);
  else
  {
    set("long", "一件披风。\n");
    set("material", "leather");
    set("unit", "件");
    set("value", 700);
    set("armor_prop/armor", 60);
  }
  setup();
}
