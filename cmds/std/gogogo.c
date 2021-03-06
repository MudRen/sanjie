//Cracked by Roath
// go.c
#pragma save_binary
#include <ansi.h>
inherit F_CLEAN_UP;
#define DIR_NAME   0
#define DIR_XX     1
#define DIR_YY     2

mapping default_dirs = ([
        "north":                ({"北", 0, 1,}),
        "south":                ({"南", 0,-1,}),
        "east":                 ({"东", 1, 0,}),
        "west":                 ({"西",-1, 0,}),
        
        "northeast":    ({"东北", 1, 1,}),
        "northwest":    ({"西北",-1, 1,}),
        "southeast":    ({"东南", 1,-1,}),
        "southwest":    ({"西南",-1,-1,}),
]);

void create() { seteuid(getuid()); }

// follow will have silent=2, so as to reduce the CPU load.
int main(object me, string arg)
{

        object env;
        mapping position;
        int pos,xx,yy;
        env = environment(me);
        if(!env) return notify_fail("你哪里也去不了。\n");
        if(!env->query("hellfireroom"))
                 return notify_fail("此处无立体方位！\n");
        if( !arg ) return notify_fail("你要往哪个方位方向走？\n");
        
        if(!me->query_temp("position"))
            {
                if(userp(me))
                  me->set_temp("position",(["xx":18+random(5),"yy":18+random(5),"zz":0,]));
                  else me->set_temp("position",(["xx":18+random(5),"yy":18+random(5),"zz":random(3),]));
             }
             position=me->query_temp("position");
        
         if (arg=="up" && (!userp(me) || wizardp(me))) 
                  {
                   if( position["zz"]+1 >=3) return 1;
                       position["zz"] +=1;
                       me->set_temp("positiom",position);
                       return 1;
                  }
                  else if (arg=="down" && (!userp(me) || wizardp(me)))
                   {
                   if( position["zz"]-1 < 0) return 1;
                       position["zz"] -=1;
                       me->set_temp("positiom",position);
                       return 1;
                   }
        if(undefinedp(default_dirs[arg]))
                 return notify_fail("你要朝哪个方位方向走一步？\n");
        
        if( env->query("position_max") && (env->query("position_max") > 2 && env->query("position_max") < 8))
                pos=env->query("position_max");
                else pos=3;
                
        if((xx=position["xx"]+default_dirs[arg][DIR_XX]) <= (20-pos) || xx >= (20+pos) )
                return notify_fail("咚的一声！！你好象撞到什么？\n");
        if((yy=position["yy"]+default_dirs[arg][DIR_YY]) <= (20-pos) || yy >= (20+pos) )
                return notify_fail("咚咚的两声！！你好象撞到什么？\n");
                
                position["xx"]=xx;
                position["yy"]=yy;
                me->set_temp("position",position);
             tell_object(me,"你朝"+default_dirs[arg][DIR_NAME]+"方位走了一步！\n");
            return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : gogogo <方向>
 
让你往指定的方位方向移动，可向八个方向方位移动一步。
 
HELP
    );
    return 1;
}

