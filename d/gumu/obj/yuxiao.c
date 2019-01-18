// created 4/5/1997 by snowcat
#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit ITEM;
inherit F_UNIQUE;
void init();
int do_blow(string arg);
void create()
{
  set_name(HIG "翡翠玉箫" NOR, ({ "yu xiao"})); 
  set_weight(10000);
        set("unique", 1);
  set("long","这是一支用蓝田美玉制做的箫，看起来温润光洁。\n令人爱不释手,你可以吹吹(blow)看\n");
  set("unit", "根");
  setup();
}

init ()
{
  add_action ("do_blow", "blow");
}

int do_blow (string arg)
{
  object me, where;
  int sen_cost, gain;
  
//  object xiao = this_object();
  string *msgs = ({
    "$N箫抵唇边，一曲《梅花三弄》吹的是声若凝绝。\n",
    "$N一曲《望凝梅》当真是绕梁三日 不绝于耳。\n",
    "$N凝思片刻随即一曲《高山流水》悠扬而出。\n",
    "$N闭目凝神一曲《百鸟朝凤》令人入置身百鸟林中。\n",
    "$N一曲《昙花现》毕，竟自泪流满襟。\n",
    "$N一曲《将进酒》令人心神为之一振。\n",
  });
  me = this_player();
  where=environment(me);
        if( me->is_busy() )
                        return notify_fail("你现在忙着呢，哪有闲情逸致吹箫...\n");
        if( me->is_fighting() )
                        return notify_fail("太风雅了吧？打架时还吹箫...\n");
        if( where->query("no_fight") )
                        return notify_fail("这里的人好像不喜欢你如此吵闹呀......\n");
//        if( (int)me->query_skill("xiao",1)<50 )
//                return notify_fail("你胡乱吹了几下，愣是没有吹出声音了，显然你还没有领悟到吹箫之法。\n")
        if( (int)me->query_skill("xiao",1)>250 )
                return notify_fail("你的箫艺已然炉火纯青，可以将玉箫吹的随心所欲了\n");

        sen_cost = 20 + (35-(int)me->query("int"));
        if( (int)me->query("sen")<sen_cost )
                return notify_fail("你现在头晕脑胀，该休息休息了。\n"); 
        me->receive_damage("sen", sen_cost);

        gain = (int)me->query_skill("xiao", 1)/5+(int)me->query("int")+1;
        me->improve_skill("xiao", gain);
        message_vision (msgs[random(sizeof(msgs))],me);


  
  return 1;
}


