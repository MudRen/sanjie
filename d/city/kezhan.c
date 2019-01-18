// kezhan.c

inherit ROOM;
#include <ansi.h>
#include <liwu.h>


int block_cmd(string args); 

void create ()
{
  set ("short","南城客栈");
  set ("long", @LONG

这家客栈紧靠长安城中心，所以生意非常兴隆。兼之价钱低廉，更是
成了外地游客落脚的首选。露天摆了七八张桌子，三教九流人等在此
进进出出，络绎不绝，几个跑堂的小二来来回回招待着四方来客。二
楼上是雅厅，后面是客房。
LONG);
  set("exits", ([ /* sizeof() == 4 */
  "east" : __DIR__"sleep",
  "west" : __DIR__"zhuque-s1",
  "north" : "/d/city/misc/idleroom",
  "up": "/d/wiz/entrance",
]));
//  set("chat_room",1)
  set("objects", ([ /* sizeof() == 2 */
  "/obj/boss/city_waiter" : 1,
  "/adm/npc/liwu" : 1,
  "/d/ourhome/npc/bigeye" : 1,
  ]));


   set("no_time", 1);
  set("no_fight", 1);
  set("no_magic", 1);
        set("freeze",1);
  set("resource", ([ /* sizeof() == 1 */
  "water" : 1,
]));
  set("valid_startroom", 1);

/*
  remove_call_out ("drop_liwu");
  call_out ("drop_liwu",10);
*/
  setup();
  call_other("/obj/board/nancheng_b", "???");
}

void init()
{
    add_action("block_cmd", "", 1);
}

int block_cmd(string args)
{
string verb;
verb = query_verb();

    // if (verb == "bian") return 1; // by mon 7/15
    if (verb == "xiudao") return 1;
    if (verb == "teach") return 1;
    if (verb == "cast yueying") return 1;
    if (verb == "exert") return 1;
//      if (verb == "id here") return 1;
//    if (verb == "id") return 1;
    return 0;
}

int valid_leave(object me, string dir)
{
        object mbox,*inv;
        inv = all_inventory(me);
//        if ( sizeof(inv)&& dir == "north" ) return notify_fail("店小二不怀好意的对你说：这位客官，进发呆室前请将身上的物件清空。\n");

        if ( !me->query_temp("rent_paid") && dir == "east" )
        return notify_fail("店小二满脸堆笑地挡住了你：对不起，后面是客人的卧房，不是本店的客人，不便打扰。\n");
        if( mbox = me->query_temp("mbox_ob") ) {
                tell_object(me, "你将信箱交回给邮差。\n");
                destruct(mbox);
        }

        return ::valid_leave(me, dir);
}

#if 0
//04.2003 koker 添加随机奖励部分，增加游戏的一些可玩性。
void drop_liwu ()
{
  int i, j;
  object who;
  object *list;

  remove_call_out("drop_liwu");
        call_out("drop_liwu",random(1800)+3600*3); 
  list = users();
  j = 100;
  while  (j--)
  {
    string there;

    i = random(sizeof(list));
    if (!environment(list[i]))
      continue;
    if (!living(list[i]))
      continue;

    who = list[i];

    break;
  }
  if (! who)
    return;
  //who = find_living ("snowcat");
  remove_call_out ("liwu_down");
  call_out ("liwu_down",2,who,"你看见天空中电光闪闪……\n");
  call_out ("liwu_down",6,who,"接着四周雷声隆隆……\n");
  call_out ("liwu_down",10,who,"猛然间，一个闪电击在$N的头上。\n");
  remove_call_out ("liwu_drop");
  call_out ("liwu_drop",12,who);
}

void liwu_down (object who, string msg)
{
  message_vision (msg,who);
}

void liwu_drop (object who)
{
  string str = __DIR__;
  object ob;
  string msg;

  ob = new (liwu[random(sizeof(liwu))]);
 
 
  message_vision ("$N手中多了一件物事。\n",who);
  msg="听说"+who->query("name")+"被雷电击中，意外的获得了"+ob->name()+"。\n";
CHANNEL_D->do_channel(this_object(),"rumor",msg);
log_file("liwu","["+ctime(time())+"] "+sprintf("%s(%s)得到了"+ob->name()+"\n", 
    who->query("name"),who->query("id"))); 
  ob->move(who);

}
#endif
