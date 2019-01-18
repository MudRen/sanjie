
#include <ansi.h>
inherit ROOM;
int do_yuntang(string arg);

void create ()
{
        set ("short", "库房");
        set ("long", @LONG
你走过一条狭窄的小巷之后来到一间仓库中。这里整齐的堆码着未经
熨烫的布匹和一些成衣。靠墙摆放着几张大桌子，桌子上放着几匹打湿的
布料和一个竖着一个已经烧得发烫的熨斗。你可以在这儿熨烫(yuntang)。
LONG);

        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"xiemao", 
        ]));

        setup();
}

void init()
{
        add_action("do_yuntang","yuntang");
}

int do_yuntang(string arg)
{
        object me=this_player(); 
        object ob;
        if (!me->query_temp("newbiejob/yunbu"))
                return notify_fail("你现在没有熨布的工作。\n");

/*        if (query_temp("bu")==0)
           return notify_fail("这里的布料都已经熨好了。\n");
*/
        if (!arg || arg != "布料")
                return notify_fail("你要熨烫什么？\n");

        if ( (int)me->query("sen")<30)
                return notify_fail("你太累了，休息一下吧。\n");

        if (me->query_temp("newbiejob/yunbu")==6)
                return notify_fail("布料已经熨好了，快把熨好的布交回去吧！\n");
   
        message_vision("$N拿起熨斗慢慢地在布料上来回移动，只见布料上立刻冒出白色的蒸气。\n",me);
        this_player()->start_busy(1+random(1));
        me->add("sen",-(15+random(15)));
        me->start_busy(3+random(1));
        me->add_temp("newbiejob/yunbu",1);
        if ( (int)me->query_temp("newbiejob/yunbu")==6)
        {
        message_vision(CYN"布匹在熨烫下逐渐平整，$N将布匹叠好后放在一边。\n"NOR,me);
        ob=new("/d/city/obj/bu.c");
        ob->move(me);
        me->add_temp("bu",-1);      
        return 1;
        }
        if (random(10)>7)
        {
        message_vision(RED"$N在蒸气缭绕之中逐渐开始漫不经心，只听得“哧”的一声$N的手被熨斗碰了一下。\n"NOR,me);     
        me->receive_damage("kee", (int)me->query("max_qi")/6);
 
        }             
        return 1;
} 

