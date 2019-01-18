//五嶽槍魂之五嶽山神
//Created by wuyou@sk_sjsj
//2003-8-13
 
#include <ansi.h>
inherit NPC;
void create()
{
        set_name(HIM"北岳山神"NOR, ({"shan shen", "shen"}));
        set("age", 800);
        set("long", "北嶽恆山之山神。\n");
        set("str", 100);        
        set("cor", 40);
        set("con", 40);
        set("cps", 40);
        set("spi", 40);
        set("int", 40);
        set_temp("apply/damage", 150);
        set_temp("apply/armor", 800);
        set("max_kee", 7200);
        set("max_sen", 7200);
        set("force", 18000);
        set("max_force", 10000);
        set("force_factor", 500);
        set("mana", 18000);
        set("max_mana", 10000);
        set("mana_factor", 500);
        set_skill("unarmed", 650+random(50));
        set_skill("parry", 650+random(50));
        set_skill("wuyue-spear", 650+random(50));
        set_skill("dodge", 650+random(50));
        set_skill("spear", 650+random(50));
        set_skill("moshenbu", 650);
        map_skill("spear", "wuyue-spear");
        map_skill("parry", "wuyue-spear");
        map_skill("dodge", "moshenbu");
        set("combat_exp", 60000000);
        set_weight(900000);
        setup();
        carry_object("/d/obj/armor/jinjia")->wear();
        carry_object("/d/obj/weapon/spear/huaji2")->wield();            
        
}


