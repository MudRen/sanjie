/***************************************
MUDLIB：Biographies         〓悟空传〓  
Created Admin By Waiwai@2001/02/18
Admin Email：wkzstory@21cn.com         
****************************************/
//Created by waiwai@2003/01/25 鞋子(护具类)

#include <armor.h>

inherit EQUIP;

void setup()
{
	if( clonep(this_object()) ) return;

	//没有任何参数的则默然为系统限制值
	if( !query("armor_prop/armor") && !query("armor/max_armor") )
		set("armor_prop/armor",PROP_BOOTS);

	//排除带有组合类特殊标志的,带有LIMIT参数的则为限制参数有效
	if( !query("combine") && query("LIMIT")) {
	if( query("armor_prop/armor") > PROP_BOOTS )
		set("armor_prop/armor",PROP_BOOTS);
	}

	//设定最大破损默认值
	if( !query("armor/max_armor") )
		set("armor/max_armor",query("armor_prop/armor"));
	else
		set("armor_prop/armor",query("armor/max_armor"));

	set("armor_type", TYPE_BOOTS);
	if( !query("armor_apply/dodge")
	&&	weight() > 3000 )
		set("armor_prop/dodge", - weight() / 3000 );
}
