//Cracked by Roath
// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
inherit ITEM;
#include <ansi.h>
#include <task.h>
void create()
{
    set_name(HIW"味仙认证"NOR, ({ "weixian" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("long", "这是朝廷御赐的一本民间厨子最高荣誉证书\n");
            set("unit", "本"); 
            set("owner_name", "万口福");
          set("owner_id", "wan koufu");
          }

    setup();
}

