#include <weapon.h>
#include <ansi.h>
inherit STICK;
void create()
{
        set_name(HIW"双龙银丝虬龙棒"NOR, ({ "qiulong bang" }) );
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                 set("material", "iron");
 set("long", "一种软中有硬的奇形兵器，为燕赵双侠中的老二矮金刚蓝和所持。\n");
             }
        init_stick(15);
        setup();
}
