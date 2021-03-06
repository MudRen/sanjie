// cart
// created by kuku@sjsh 2002/12

#include <ansi.h>
inherit ITEM;

void to_rob(object me);

mapping default_dirs = ([ 
        "north":        "北面",
        "south":        "南面",
        "east":         "东面",
        "west":         "西面",
        "northup":      "北边",
        "southup":      "南边",
        "eastup":       "东边",
        "westup":       "西边",
        "northdown":    "北边",
        "southdown":    "南边",
        "eastdown":     "东边",
        "westdown":     "西边",
        "northeast":    "东北",
        "northwest":    "西北",
        "southeast":    "东南",
        "southwest":    "西南",
        "up":           "上面",
        "down":         "下面",
        "enter":        "里面",
        "out":          "外面",
]);

void create()
{       
        seteuid(getuid());
        set_name(HIW"镖车"NOR, ({ "biao che", "cart", "che"}) );
        set_weight(300000);
        set("no_get", 1);
 
        set("location",1);
        set("no_clean_up",1);
        set_max_encumbrance(80000000);
        set("unit", "辆");
        set("long", "一辆黑漆漆的镖车，上面插着镖旗。\n");
        set("closed", 1);
        set("value", 2000);
}

void init()
{
    add_action("do_open","jie");
    if( this_player()->query_temp("in_dart"))
    {
         add_action("do_gan","gan"); 
         add_action("do_gan","drive");
    }
    call_out("destroy2",random(800)+1000,this_object());
}

int do_open(string arg)
{
        object me, ob;
        string mname,mid;
        mname = this_object()->query("master");
        mid = this_object()->query("masterid");
        me = this_player();
        ob = this_object();

        if(arg != "biao che")
          return notify_fail("你要干什么？\n");
        if(me->query_temp("in_dart"))
          return notify_fail("你想监守自盗？\n"); 
        if(present(mid,environment()))
          return notify_fail("护镖的还在旁边，先把他做掉吧。\n");

        message_vision("$N将$n推走了。\n", me, this_object());
        message("channel:rumor",HIM"【谣言】"+mname
         +"护的镖被"+me->query("name")+"劫去了！\n"NOR,users());
        call_out("destroy1",1,ob);
        return 1;
}

int do_gan(string arg)
{        
        object me,ob, env, obj;
        string item, dir, dest, target;
        mapping exit;
        me = this_player();
        ob = this_object();

        if(!arg) return notify_fail("你要赶什么？\n");

        if( me->query("id")!=ob->query("masterid")) return 0;
        
        if( sscanf(arg, "%s to %s", item, dir) != 2 ||
                item != "cart" && item != "che")
                return command(query_verb()+" "+arg);
                        
        if( me->is_busy() )
                return notify_fail("你现在正忙着哩。\n");

        if ( present("robber",environment()))
                return notify_fail(HIR"劫匪伸手一拦道：“想跑？没那么容易！”\n"NOR);
        
        if ( this_player()->is_fighting())
                return notify_fail("你还是先把对手解决了再说吧！\n");
 
        env = environment(me);
        if(!env) return notify_fail("你要去那里？\n");
        
        if( !mapp(exit = env->query("exits")) || undefinedp(exit[dir]) ) {
                if( query_verb()=="gan")
                        return notify_fail("这个方向过不去。\n");
                else
                        return 0;
          }
        
        dest = exit[dir];
                        
        if( !(obj = find_object(dest)) )
                call_other(dest, "???");
        if( !(obj = find_object(dest)) )
                return notify_fail("没法赶。\n");

        if( !undefinedp(default_dirs[dir]) )
                target = default_dirs[dir];
        else
                target = obj->query("short");

        message_vision(HIG "\n$N赶着镖车往" + target + "驶去。\n" NOR,
                me);
        message_vision(HIG "镖车隆隆向"+ target + "驶去。\n" NOR,me);  

        if( ob->move(obj) && me->move(obj)) {
          all_inventory(env)->follow_me(me, dir);
          message_vision(HIG "$N赶着镖车驶了过来。\n" NOR,
                        me);
          message_vision(HIG "镖车隆隆驶了过来。\n" NOR,me); 
          me->start_busy(random(3));
        }
        call_out("check1",1,ob,me);
        if (random(10)>8) { call_out("to_rob",1,me);}
        return 1;
}

int check1(object ob, object me)
{
        if (base_name(environment())==(string)me->query_temp("dart_area") 
             && present(me->query_temp("dart_id"), environment()) )
           {  
              message_vision(HIY"$N累了个半死，终于把镖运到了地头。\n\n"NOR,me);
              message_vision(HIY+me->query_temp("dart_name")+
                "拍拍$N的头说道：“"+RANK_D->query_respect(this_player())
                +"辛苦了！”\n\n"NOR,me);
              write(HIY"里间出来几个人将镖车拉了进去。\n"NOR);
              me->set_temp("over_dart",1);
              me->apply_condition("dart_limit", 0);
              call_out("destroy1",1,ob);
              return 1;
            }  
}

void destroy1(object me)
{
        destruct(me);
        return;
}

void destroy2(object me)
{
      message_vision(HIR"突然骡子大叫一声发疯似拖着镖车跑了。\n"NOR,me);
      destruct(me);
      return;
}

void to_rob(object me)
{
       object *ob;
       object robber,room;
    int i,j,level;
       room = environment(me); 
       if( environment(me)->query("no_fight") ) return;
       message_vision(HIR"忽然间跳出一群劫匪！劫匪阴笑道：“红货和人命都留下来吧！。”\n" NOR,
        me); 
       me->start_busy(2);
       j=random(5);
       for (i=0;i<=j;i++)
       {
        if(i==0) robber=new(__DIR__"robber0");
        else  if(i==1) robber=new(__DIR__"robber1");
        else  if(i==2) robber=new(__DIR__"robber2");
        else  if(i==3) robber=new(__DIR__"robber3");
        else  if(i==4) robber=new(__DIR__"robber4");    
        if(objectp(robber))
         {
            robber->set("chat_chance_combat", 2);
            robber->set("chat_msg_combat", ({
              "强盗显是以劫为生，刀刀冲要害而来。\n",
              "强盗高喊：叫你人财两空。\n",
              "强盗横刀当道，一声大喊：此山是我开，此树是我栽，若要从此过，留下买路财 !",
            }) );
                robber->move(room);
          robber->copy_status(me,level);
                robber->kill_ob(me);
                me->kill_ob(robber);
              robber->checking(robber,me);
                robber->set_leader(me);
          }      
      }
}
