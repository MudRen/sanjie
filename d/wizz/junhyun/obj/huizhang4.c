//贤者徽章
//by junhyun
#include <ansi.h>

inherit ITEM;

int do_zhuan(string);
void create()
{
  set_name(HIW "贤者徽章" NOR, ({"guangming huizhang", "huizhang"}));
  set_weight(50);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "枚");
    set("long", HIW"象征着智慧与光明的徽章\n"NOR);
    set("value", 50000000);
    set("no_sell", 1);
  }
  
  setup();
}

void init()
{
        add_action("do_zhuan", "zhuan");
        call_out("announce",random(10),this_player());
}


void announce(object who)
{
    if(!this_object()) return;
    if(!who) return;
    CHANNEL_D->do_channel(this_object(), "rumor", 
            who->query("name")+"得到了"+name()+"！\n");
}

int do_zhuan(string arg)
{
  object me = this_player();
  string msg; 
  if (!id(arg))
    return notify_fail("你要转什么职业？\n");

        message_vision(HIC"$N向光明女神缇雅祈祷，$N成功转职为贤者！
\n"NOR, me);  
  
        me->add("bellicosity", -random( (int)me->query_kar() * 10));
        if ((int)me->query("bellicosity") < 0 ) me->set("bellicosity", 0);

        me->set("title", HIW"贤者"NOR);
        me->delete("betray");
        me->save();
        msg="听说"+ me->query("name")+ "转职为贤者了！\n";
     CHANNEL_D->do_channel(this_object(),"rumor",msg);
  destruct(this_object());
  return 1;
}

