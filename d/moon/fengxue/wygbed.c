// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
inherit ROOM;

void create()
{
        set("short", "白玉床");
        set("long", @LONG

一张月色的软榻，榻四周雕着竹叶格，看上去极为精致。床上
挂着一副纱幔，上面不知用什么丝线绣着一轮冷冷的弯月。纱
衾鸳枕之间散发出一丝丝淡淡的幽香。
LONG
        );
        
        set("exits", ([
                "out": __DIR__"woshi",
            ]));
        set("no_fight", 1);
        set("no_magic", 1);
        set("sleep_room",1);
        set("if_bed",1);
                                              
        setup();
}


