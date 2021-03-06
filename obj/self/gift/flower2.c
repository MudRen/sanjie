// Created by aeddy@2003/05/05
// 小护身符类，容貌40男性装备

#include <armor.h>
inherit OTHERS;

void create ()
{
	set_name(HIW "樱花玉配" NOR, ({ "prunus serrulata", "prunus", "serrulata" }));
	set_weight(100);
	set("long",
"樱花(sweet osmanthus) 学名(Prunus serrulata)
双子叶植物，蔷薇科。落叶乔木，高10～25米。树皮褐色，有皮孔。
叶卵圆形，叶缘有锯齿。由3～5朵花组成伞房花序或总状花序，花瓣
白色或粉红色，4～5月开放。7月果熟，核果球形，黑色。
原产中国，日本，朝鲜。喜排水良好的肥沃土壤和湿润环境，不耐盐
碱。野外多生在山沟溪旁，杂树林中。一般用嫁接繁殖，栽培品种有
几百种。樱花是春季重要观花乔木，园林中常种植在道路两旁，或山
坡上。叶和核仁可入药，木材是雕刻工艺的好材料。
此外，在园林中常见的其他樱花有：日本樱花(Prunus ye-doensis)，
又称东京樱花，高达16米，树皮带银灰色，花梗，萼筒有毛，花期较
短，但花很茂盛。日本晚樱(Prunus lannesiana)，花期较晚，花大，
重瓣，粉红色，有香气。\n"NOR);
	set("unit", "个");
	set("value", 1000000);
	set("no_break", 1); // 不破损
	set("deadfly", 1); // 死亡飞掉
	set("no_get", 1);
	set("no_give", 1);
	set("no_putin", 1); // 不能放保险库
	set("no_putto", 1); // 不能捐献
	set("no_stock", 1); // 不能放黑店
	set("armor_type", "others");
	set("material", "silk"); // 主材质
	set("Fmaterial", "gem"); // 辅材质
	set("no_sell", "这么珍贵的樱花玉配你也要换钱吗？\n");
	set("no_drop", "仍掉了樱花玉配，就象仍掉了一个梦想，还是好好珍惜它吧。\n");
	set("no_give", "樱花玉配需要珍惜，不能轻易送人。\n");
	set("no_put", "樱花玉配需要展示出来，不能私藏的。\n");
	set("armor_prop/armor", 2);
	set("armor_prop/personality", 1);
	set("unequip_msg","$N将漂亮的"+query("name")+"轻轻地收了起来……。\n");
	set("wear_msg", "$N将一个漂亮的"+query("name")+"小心地拿了出来，佩带在身上。\n" );
	setup();
}

