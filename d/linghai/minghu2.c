//by dewbaby

//minghu2
  
#include <ansi.h> 
inherit ROOM; 
        
void create () 
       { 
         set ("short", HIC"大明湖畔"NOR); 
         set ("long", @LONG 
        
这里是大明湖畔，岸上翠柳垂荫，婀娜多姿。湖中碧
波泛荡，荷花似锦；水面小舟争渡，画舫徐行。更有那
楼台亭树，隐现其间。简直美不胜收。
LONG); 
       
        set("outdoors", 2); 
        set("exits", ([ /* sizeof() == 2 */ 
        "north" : __DIR__"minghu3", 
         "south" : __DIR__"minghu1",      
        ])); 
       
        setup(); 
      }
 

