//Last modified by waiwai@2002/12/05

#include <armor.h>

inherit OTHERS;

void create()
{
	set_name(HIW "钻石" NOR, ({ "diamond" }) );
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
        else {
	        set("long", HIW "一粒精光闪闪的钻石。\n" NOR);
                set("value", 50000);
		    set("unit", "粒");
//              set("can_be_enchased", 1);
		set("can_auction", 1);
                set("magic/type", "lighting");
                set("magic/power", 100);
	}
        setup();
}
