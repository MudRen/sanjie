inherit ROOM; 
#include <room.h> 
#include <ansi.h> 
void create () 
{
set("short","山坡");
set("long",@LONG 
修仙之道，原本渺渺，只有极大毅力之人方能成仙，“世人皆谓神仙好，有谁知道
成仙难。“
　　一眼看上去，这山好高好高，好象接到了云端，不知道云深几许，不知路在何方。
这山本不是用走的，据说真正修道成仙的是人架着浮云上去的，还没修成的就只有爬上
去了。
LONG);
set("exits", ([ /* sizeof() == 1 */ 
"up": __DIR__"shanding", 
])); 
setup();
}
