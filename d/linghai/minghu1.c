// by dewbaby
//minghu1
  
#include <ansi.h> 
inherit ROOM; 
        
void create () 
       { 
         set ("short", HIC"大明湖畔"NOR); 
         set ("long", @LONG 
        
这里是大明湖畔，你经过一段漫长的路途后，看到眼前明如水镜的湖面
心中不觉一阵轻松之感。淡绿色的湖水随着拂面而过的轻风荡漾着。风
中夹着清甜花香。
LONG); 
       
        set("outdoors", 2); 
        set("exits", ([ /* sizeof() == 2 */ 
        "north" : __DIR__"minghu2", 
         "southeast" : __DIR__"wxy1",      
        ])); 
       
        setup(); 
       call_other("/obj/board/minghu_b", "???");  
      }
 

