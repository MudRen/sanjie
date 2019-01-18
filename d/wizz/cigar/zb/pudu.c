// 普渡法杖 by Calvin

#include <ansi.h>
#include <weapon.h>

inherit STAFF;

void create()
{
        set_name( HIY"普渡"+WHT"法杖" NOR, ({ "pudu staff", "staff","fazhang","fa zhang" }) );
        set_weight(4000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "条");
                set("long", HIY "此乃我祖如来所赐之普渡法杖，短而金辉，象征佛法无边。\n" NOR);
                set("material", "brass");
                set("value", 200000);
                set("no_get", 1);
                set("no_give", 1);
                set("no_put", 1);
                set("no_drop", 1);
                set("no_sell", "这种罕见的神兵可不是随便可以买卖的!\n");
                set("no_give", 1);
                set("wield_msg", HIY "\n$N拿出一条普渡法杖握在手中，刹那间四周一片肃穆，连天地鬼神也为之震动。\n\n" NOR);
                set("unwield_msg", HIY "\n$N放下手中的普渡法杖，周围的人才喘过一口气来。\n\n" NOR);
	}

   init_staff(200);
	setup();
}
