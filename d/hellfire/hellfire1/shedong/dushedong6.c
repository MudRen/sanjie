#include <ansi.h>
#include <room.h>

inherit HELL_ROOM;//注意是MROOM

void create (int level,int num)
{
  set ("short", HIG "毒蛇洞" NOR);
  set ("long", @LONG
寒冰地狱，里面布满无色寒冰，隐隐发出冷冷寒光。
邪恶的黑暗世界，一眼看不到尽头。
    一股血腥的气味差一点儿把你熏倒，定睛一看，
原来这里盘踞着几条粗大的千年巨蛇，口中吞吐着血
红的蛇信子。
LONG);
     level=10; num=random(2)+1;
    set("exits", ([ 
                "west" : __DIR__"dushedong7",
                "east" : __DIR__"dushedong4",
                "north" : __DIR__"dushedong1",
 //              "south" : __DIR__"bing7",
                                 ]));
        set("level",level);//自己可以设定！
      set("alternative_die",1); 
       set("hellfireroom",1); 
        set("npc_npc",num);//自己可以设定！
    set("objects",([
         "/d/hellfire/npc/guai3" : num,
                  
                 ]));

  setup();
  setup2();
   
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


int valid_leave (object who, string dir)
{
  object where = this_object ();
  object obj = present ("monsters",where);



  if (obj)
    return notify_fail ( obj->name()+"露出两眼凶光要吃了你。\n");

  return ::valid_leave (who, dir);
}

