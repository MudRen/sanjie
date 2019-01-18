//Created by waiwai@2002/12/05
//343种随机颜色组合之二

#include <ansi.h>

inherit ITEM;

void create()
{
	string *colors = ({ HIW, HIR, HIY, HIC, HIM, HIG, HIB });
	set_name(colors[random(sizeof(colors))]+"雨"+colors[random(sizeof(colors))]+
"花"+colors[random(sizeof(colors))]+"石"NOR, ({ "yuhua stone", "stone" }) );
	set_weight(500);
	if( clonep() )
	    set_default_object(__FILE__);
	else {
	set("long", "一粒色彩斑斓的小石子，每一粒都似乎在讲述着一个故事。\n");
	set("unit", "粒");
	set("value", 5000);
//	set("no_sell", 1);
	}
}

