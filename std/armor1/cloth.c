/***************************************
MUDLIB：Biographies         〓悟空传〓  
Created Admin By Waiwai@2001/02/18
Admin Email：wkzstory@21cn.com         
****************************************/
//Created by waiwai@2003/01/25 上衣(护具类)

#include <armor.h>

inherit EQUIP;

void setup()
{
	if( clonep(this_object()) ) return;

	//没有任何参数的则默然为系统限制值
	if( !query("armor_prop/armor") && !query("armor/max_armor") )
		set("armor_prop/armor",PROP_CLOTH);

	//排除带有组合类特殊标志的,带有LIMIT参数的则为限制参数有效
	if( !query("combine") && query("LIMIT")) {
	if( query("armor_prop/armor") > PROP_CLOTH )
		set("armor_prop/armor",PROP_CLOTH);
	}

	if( !query("armor/max_armor") )
		set("armor/max_armor",query("armor_prop/armor"));
	else
		set("armor_prop/armor",query("armor/max_armor"));

	set("armor_type", TYPE_CLOTH);
	if( !query("armor_apply/dodge")
	&&	weight() > 3000 )
		set("armor_prop/dodge", - weight() / 3000 );
}

void init() {	add_action("do_tear", "tear"); }

int do_tear(string str)
{
	object ob;

	if( !id(str) ) return 0;

	if( (string)query("material") != "cloth" 
		|| (string)query("material") != "pants" )
		return notify_fail(	WHT"你只能撕一般布料(上衣或者裤子)的衣服。\n"NOR);

	if( (string)query("material") == "cloth" ) {
	if( (int)query("teared_count") >= 4 )
		return notify_fail( name() + "的袖口，下面已经没有多余的布可撕了。\n");
	}

	if( (string)query("material") == "pants" ) {
	if( (int)query("teared_count") >= 4 )
		return notify_fail( name() + "的裤脚，下面已经没有多余的布可撕了。\n");
	}

	message_vision("$N从" + name() + "撕下一条布条。\n", this_player() );
	add("teared_count", 1);
	ob = new("/obj/bandage");
	ob->set_name("从" + name() + "撕下的布条", ({ "cloth piece", "piece", "cloth" }) );
	if( !ob->move(this_player()) )
		ob->move(environment(this_player()));
	return 1;
}
