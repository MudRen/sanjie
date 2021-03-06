// Created by waiwai@2001/03/23

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIM "蓝晶" NOR, ({ "lan crystal", "lan" }) );
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long", HIB "一块闪烁这奇异光芒的蓝色水晶，"
                    "让人感到一阵阵的心悸。\n" NOR);
                set("value", 200000);
		set("unit", "块");
		set("no_zm", 1);
                set("can_be_enchased", 1);
                set("magic/type", "magic");
                set("magic/power", 150);
		set("material", "crystal");
		};
}

void init()
{
 	if( this_player()==environment() ) {
	add_action("do_enchase", "enchase");
	add_action("do_enchase", "insert");
	}
}

int do_enchase(string arg)
{
   object in_obj;
   string item;
   string mats;
   int rd,inset_num ;
   object me = this_player();
   object ob = this_object();
   string *colors = ({ HIW, HIR, HIY, HIC, HIM, HIG, HIB });

   if(!arg) return notify_fail("你要干什么？\n");

   if(sscanf(arg, "%s", item)!=1) return notify_fail("你要把宝石镶嵌到什么上？\n");

   if(!objectp(in_obj = present(item, me))) return notify_fail("你身上没有这样东西。\n");

   if( in_obj->query("equipped") )
      return notify_fail("你必须放下这样东西才能镶嵌宝石。\n");

   if( !wizardp(me) && !environment(me)->query("cold"))
             return notify_fail("此地灵气不够，无法镶嵌物品。\n");

   if( in_obj->query("no_zm")||in_obj->query_unique())
      return notify_fail("这件物品不能镶嵌宝石。\n");

   mats = in_obj->query("material");       //装备或武器
   inset_num = in_obj->query("inset_num");  // 嵌了几个了
   if(!inset_num) inset_num = 1;
   else inset_num = inset_num + 1;
   if(inset_num > 5) return notify_fail(in_obj->query("name")+WHT"上已经镶嵌了太多的宝石了！\n"NOR);
   
   if(!in_obj->query("weapon_prop/damage")) {   //防具
       message_vision(CYN"$N把$n"CYN"镶嵌到"+in_obj->query("name")+CYN"上 \n"NOR,me,ob);
       tell_room(environment(me),
	HIB"只见"+ob->name()+HIB"化做一道白光,钻入了"+in_obj->query("name")+HIB"里面,不见了！ \n"NOR);
       in_obj->add("armor_prop/armor",5+random(2));
       in_obj->add("armor_prop/dodge",5+random(2));
       in_obj->set("armor/max_armor",in_obj->query("armor_prop/armor"));

       message_vision(CYN""+in_obj->query("name")+CYN"似乎变得更加轻盈了！\n"NOR,me);
       in_obj->set_weight(in_obj->query_weight()+500);      
       in_obj->set("inset_num",inset_num);
       in_obj->set("Fmaterial","gem");
       in_obj->add("inset_b",inset_num);
	// 满5个便不破损
       if( (int)in_obj->query("inset_num")>=5) {
       in_obj->set("no_break",1);
       in_obj->set("name",colors[random(sizeof(colors))]+in_obj->query("name")+HIR"("HIY"嵌-"+in_obj->query("inset_num")+HIR")"NOR);
	} else
       in_obj->set("name",colors[random(sizeof(colors))]+in_obj->query("name")+NOR);

       if(!in_obj->query("old_long")) in_obj->set("old_long",in_obj->query("long"));
       in_obj->set("long",in_obj->query("old_long")+"上面镶嵌了"HIW+(inset_num)+"颗宝石\n"NOR);
       in_obj->save();
       destruct(ob);
       return 1;
	}else{
	//武器
       message_vision(CYN"$N把$n"CYN"镶嵌到"+in_obj->query("name")+CYN"上 \n"NOR,me,ob);
       tell_room(environment(me),
	HIB"只见"+ob->name()+HIB"化做一道白光,钻入了"+in_obj->query("name")+HIB"里面,不见了！ \n"NOR);
       message_vision(CYN""+in_obj->query("name")+CYN"似乎变得更加灵气活现了！\n"NOR,me);
       in_obj->add("weapon_prop/damage",1 + random(10)); //增加武器伤害度
       in_obj->set("max_weapon",in_obj->query("weapon_prop/damage"));

       in_obj->set_weight(in_obj->query_weight()+500);
       in_obj->set("inset_num",inset_num);
       in_obj->set("Fmaterial","gem");
       in_obj->add("inset_b",inset_num);
	// 满5个便不破损
       if( (int)in_obj->query("inset_num")>=5) {
       in_obj->set("no_break",1);
       in_obj->set("name",colors[random(sizeof(colors))]+in_obj->query("name")+HIR"("HIY"嵌-"+in_obj->query("inset_num")+HIR")"NOR);
	} else
       in_obj->set("name",colors[random(sizeof(colors))]+in_obj->query("name")+NOR);

       if(!in_obj->query("old_long")) in_obj->set("old_long",in_obj->query("long"));
       in_obj->set("long",in_obj->query("old_long")+"上面镶嵌了"HIW+(inset_num)+"颗宝石\n"NOR);
       in_obj->save();
       destruct(ob);
       return 1;
	}
	return notify_fail("你镶嵌宝石失败！\n");
}

