#include <ansi.h>
#include <room.h>

inherit HELL_ROOM;//注意是HELL_ROOM 不ROOM

void create (int level,int num)
{
  set ("short", HIW "寒冰地狱" NOR);
  set ("long", @LONG
寒冰地狱，里面布满无色寒冰，隐隐发出冷冷寒光。
LONG);
     level=10;num=3;
//
//level 是怪的级别，10-30, num 是怪的数目
    set("exits", ([
 /*              "east" : __DIR__"luohun",
               "west" : __DIR__"dilie",
               "north" : __DIR__"huaxue",
               "south" : __DIR__"fenghou",
  */
               "north" : __DIR__"bing1",
                 ]));
        set("level",level);//自己可以设定！
// 房间以后怪的的等级
      set("alternative_die",1); 
       set("hellfireroom",1); 
//炼火地狱房间标志，cmds npc 判断所需！
//
        set("npc_num",0);//自己可以设定！
// 房间以后怪的的数目
    set("objects",([
                  
                 ]));

  setup();
  setup2();
// setup2();不能少
   
}
void init2()
{
}
/*
int blowing(object ob)
{
 int i;
 int damage;
        if(  ob && environment(ob) == this_object())
{
 tell_object(this_object(), HIW "\n\n你被冰冻得动弹不得。\n\n" NOR);
 ob->start_busy(3);
 if( environment(ob) == this_object())
 call_out("blowing",random(30)+1, ob);
}
 else
 return 1;
}
*/
/* 以下是更新时间、 内容的设定*/
void reset()
{
        object guai;
        int i,level;
 
        this_object()->add_temp("npc_times",1);
       if (this_object()->query_temp("npc_times")>10)
       {
        this_object()->set_temp("npc_times",1);
       if(this_object()->qurey("npc_number")> 1){
          for(i=0;this_object()->query("npc_number");i++) { 

                guai=new("/d/hellfire/npc/guai");
                level=this_object()->query("level");
                 guai->create(level,level);
                guai->move(this_object());
                                           }
                                              }
         }
        ::reset();
}


