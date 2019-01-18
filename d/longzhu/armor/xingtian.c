// 行天战衣 by Calvin

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIY"行天战衣"NOR, ({"xingtian zhanyi","zhanyi","xingtian","yi","cloth"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("is_monitored", 1);
                set("no_give", 1);
                set("no_drop", 1);
                set("no_put", 1);
set("replace_file", "/d/quest/longzhu/armor/xingtianfake.c"); 
  set("unique", 1);
                set("name_recognized", "行天战衣");
                set("unit", "件");
                set("armor_prop/armor", 120);
                set("spells", 200);
        }
        setup();
}
