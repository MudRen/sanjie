// Creat by waiwai@2000/11/28
//〖武器装备组合系统〗

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM"五行之针"NOR, ({"five-needle"}));
	set_weight(100);
	if( clonep() )
    		set_default_object(__FILE__);
  	else {
		set("no_sell",1);
		set("value",100000);
		set("no_drop",1);
		set("no_steal",1);
		set("no_give",1);
		set("no_sell",1);
		set("can_auction", 1);
		set("unit","根");
		set("long","一根细长的银针，五彩斑斓,上面刻着＂金木水火土＂几个蝇头小字。\n");
	}
	setup();
}
