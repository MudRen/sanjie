//ROOM lianjianshi.c
inherit ROOM;

void create()
{
        set("short", "炼锏场");
        set("long",
                "这里是玄兵古洞的炼锏场。四周荒凉没有人烟，地上隐约还能看见斑斑\n"
                "的血迹，偶尔能看见的几棵树似乎也成了锏的表征，一个个剑拔弩张的。露\n"
                "天放着一个巨大的炉子，冒着蓬蓬的蓝炎，激烈的罡气震得你一阵晕眩，原\n"
                "来这里正在以内家真气锻炼兵器。\n"      
        );
        set("exits", ([
                "down" : "/d/jjf/front_yard",
        ]));

        set("objects",([__DIR__"npc/shimace" :1,]));

        setup();
        replace_program(ROOM);
}

