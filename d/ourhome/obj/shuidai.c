// shuidai.c 睡袋

inherit ITEM;

void create()
{
        set_name("睡袋", ({"shui dai", "sleepbag", "dai"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是一个亚麻棉织的睡袋，是出门远行必备之物\n");
                set("unit", "口");
                 set("value", 5000);
        }
}

