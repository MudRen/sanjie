// created 4/5/1997 by snowcat
#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit NECK;

void create ()
{
  set_name(HIM "情人玫瑰" NOR, ({ "rose"}));
  set_weight(100);
  set("long",HIW"这是情人在清晨的花园中采摘的"NOR+query("name")+HIW"，上面还滚动着几颗晶莹的露珠。 \n" NOR);
  set("unit", "朵");
  set("armor_prop/armor", 1);
  set("armor_prop/personality", 2);
  set("unequip_msg",HIW"$N将"+query("name")+HIW"轻轻地摘下来，想起远方的他，心中一酸，不禁落下泪来……。 

          花信来时，恨无人似花依旧。又成春瘦，折断门前柳。
          天与多情，不与长相守。分飞后，泪痕和酒，占了双罗袖。

\n" NOR);
  set("wear_msg", HIW"$N戴上"+query("name")+HIW"，不禁想起那个夜夜入梦的情人，脸上飞起一片红云。 

          无言独上西楼，月如钩，寂寞梧桐深院锁清秋。
          剪不断，理还乱，是离愁。别是一般滋味在心头。

\n" NOR);
  setup();
}


//
int query_autoload() { return 1; }
