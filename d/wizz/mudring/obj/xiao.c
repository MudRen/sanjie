#include <ansi.h>
#include <weapon.h>

inherit F_AUTOLOAD; 
inherit SWORD;

void create()
{
        set_name(HIC"洞箫"NOR,({"dong xiao","xiao"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else{
                set("unit","支");
                set("value",1000);
                set("material","blacksteel");
                set("unique", 1);
                set("treasure", 3);       
                set("sharpness", 5);
                set("rigidity", 8);
                set("weapon_prop/parry", 4);
                set("weapon_prop/sword", 4);
                set("wield_neili", 600);
                set("wield_maxneili", 1500);
                set("long","这是一支用上等"HIG"翡翠"NOR"做成的箫，做工十分精美。\n");
                set("wield_msg",WHT"$N脸庞透过一丝微笑,轻轻从腰间掏出$n"WHT"握在手中。\n"NOR);
                set("unwield_msg",WHT"$N将$n"WHT"在空中舞了一圈，轻轻插回腰间。\n"NOR);
        }

        init_sword(150);
        setup();
}

int query_autoload()
{
return 1;
}

