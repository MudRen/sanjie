// 九天战爪 by Calvin

#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
  set_name(HIY"偷天战爪"NOR, ({ "toutian zhanzhua","zhanzhua","zhua", "dagger" }) );
   init_dagger(30);
  set("unit", "根");
  set_weight(300);
  if( clonep() )
     set_default_object(__FILE__);
  else {
             set("value", 0);
    set("material", "tron");
  }
  set("wield_msg","$N拿起$n握在手里。\n");
  setup();
}
