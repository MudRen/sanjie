#include <ansi.h>
#include <weapon.h>

inherit FORK;
#include "/std/weapon/newwwd.c"; 

void create()
{
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "这是一把相当厉害的腾龙铲，铲锋如龙牙般，看起来要命的很。\n");
                set("value", 100000);
                set("material", "iron");
                set("wield_msg", "$N拿出一把$n，试了试重量，然后握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
				set("no_sell",1);
				set("no_drop","去垃圾堆丢吧，乱扔会污染环境!\n");
        }
        init_fork(105);
       updatename("fork"); 
        setup();
}

