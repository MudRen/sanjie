// budd_staff.c

#include <ansi.h>
#include <weapon.h>

inherit STAFF;
#include "/std/weapon/newwwd.c"; 

void create()
{
	set_weight(10000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "条");
                set("long", "一条飞舞闯关的天神之杖，上面镶著10个玉环，充满天地之灵。\n");
                set("value", 100000);
		set("material", "brass");
		set("wield_msg", "$N拿出一根金光灿然的$n握在手中。\n");
		set("unwield_msg", "$N放下手中的$n。\n");
				set("no_sell",1);
				set("no_drop","去垃圾堆丢吧，乱扔会污染环境!\n");
	}

        init_staff(105);
       updatename("staff"); 
	setup();
}
