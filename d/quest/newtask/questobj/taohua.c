#include <ansi.h>
inherit ITEM;
void create()
{
    set_name("【桃花真解】", ({ "taohua zhenjie" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "桃花仙子著录的武林秘籍。\n");
          }

    setup();
}
