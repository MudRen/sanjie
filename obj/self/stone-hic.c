// Created by waiwai@2001/03/23

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIC "青色神石" NOR, ({ "cyan stone", "stone" }) );
	set_weight( 10000 );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "块");
		set("long", "这是一块青色的神石，里面含有一些稀有的物质，或许可以组合(combine)。\n");
		set("value", 100);
		set("can_auction", 1);
    };
}

void init() 
{	
	if( this_player()==environment() )
	add_action("do_combine","combine"); 
}

int do_combine()
{
	object me, a, b, c, d, e, f, g, item;

	me=this_player();
	a=this_object();

	if( !wizardp(me) && userp(me) ) {
       if(!environment(me)->query("cold"))
             return notify_fail("此地灵气不够，无法合并物品。\n");

	if( (int)me->query("force") < (int)me->query("max_force") )
		return notify_fail("你的内力不足，很难将物品合并。\n");

	if( (int)me->query("mana") < (int)me->query("max_mana") )
		return notify_fail("你的法力不足以支持合并物品。\n");
       }

       if ( !(b=present("blue stone",me)))
                return notify_fail(CYN"你将手中 "HIC"青色神石 "NOR CYN"摆弄了几下，却一点反应也没有。\n"NOR);

       if ( !(c=present("green stone",me)))
                return notify_fail(CYN"你将手中 "HIC"青色神石 "NOR CYN"摆弄了几下，却一点反应也没有。\n"NOR);

       if ( !(d=present("magenta stone",me)))
                return notify_fail(CYN"你将手中 "HIC"青色神石 "NOR CYN"摆弄了几下，却一点反应也没有。\n"NOR);

       if ( !(e=present("red stone",me)))
                return notify_fail(CYN"你将手中 "HIC"青色神石 "NOR CYN"摆弄了几下，却一点反应也没有。\n"NOR);

       if ( !(f=present("silver stone",me)))
                return notify_fail(CYN"你将手中 "HIC"青色神石 "NOR CYN"摆弄了几下，却一点反应也没有。\n"NOR);

       if ( !(g=present("gold stone",me)))
                return notify_fail(CYN"你将手中 "HIC"青色神石 "NOR CYN"摆弄了几下，却一点反应也没有。\n"NOR);

	if( item=new("/obj/self/item/7stone")){
		if( me->query_encumbrance() + item->query_weight()
			> me->query_max_encumbrance())
		return notify_fail("你的负重过高不能合并物品。\n");
		destruct(b);
		destruct(c);
		destruct(d);
		destruct(e);
		destruct(f);
		destruct(g);

	item->move(me);
//	me->save();
	me->start_busy(3);
	message_vision(WHT"$N将手中的七块颜色的神石摆在一起，只见几道耀眼霞光掠过,竟然合并出一块七色神石。\n"NOR,me);

	destruct(a);
	}
	return 1;
}
