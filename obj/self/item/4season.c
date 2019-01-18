// Created by waiwai@2001/03/23
// 四季精灵(4season)
// [1;31m此文件禁止更改和移动[0m

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIG "四季"HIR"精灵" NOR, ({ "4-season", "season" }) );
	set_weight( 100 );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "缕");
		set("long", "这是一缕四季雨水化成的精灵。\n");
		set("value", 100);
		set("can_auction", 1);
		set("des", 1); // drop时消失标志
		set("material", "water");//水性物件标志
    };
	// drop时的特定输出信息
	set_temp("drop_msg", this_object()->query("name")+CYN" 随风而逝，消失在空气中不见了～～～\n"NOR);

	setup();
}

