/***************************************
MUDLIB：Biographies         〓悟空传〓  
Created Admin By Waiwai@2001/02/18
Admin Email：wkzstory@21cn.com         
****************************************/
//Created by waiwai@2001/05/12

inherit ROOM;

void create()
{
	  set("short", "花园小径");
        set("long",@LONG

这里是尚书府的花园小径。小径的南方就是花园，阵阵花香随风
飘过来，使人精神大振。厨房在小径的东面，而往南则去往尚书
府的庭院。
LONG
        );

        set("exits", ([
		"north":	__DIR__"yuan",
		"south":	__DIR__"huayuan",
		"east":		__DIR__"chufang",
                ]));

        set("outdoors", "city");

 	setup();
        replace_program(ROOM);
}

