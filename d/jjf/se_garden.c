// Room: /d/jjf/se_garden.c

inherit ROOM;

void create()
{
	set("short", "花园");
	set("long", @LONG
一个小花园，虽然比不上富豪大院里的万紫千红，但也布置得
精致可人。秦府里显然不乏高雅之士。春天里桃花盛开，夏日池塘
里荷花田田，秋天里菊花争艳，冬天则是一片香雪海。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
  "southeast" : __DIR__"son_cabinet",
  "north" : __DIR__"ne_garden",
  "west" : __DIR__"sw_garden",
  "northwest" : __DIR__"nw_garden",
]));
	set("no_clean_up", 0);
//        set("no_fight", 1); 
        set("no_magic", 1); 

	setup();
	replace_program(ROOM);
}
/*
      void init() 
      { 
          add_action("do_perform", "perform"); 
      } 
      int do_perform(string arg) 
      { 
              object who = this_player(); 
             object me = this_object(); 
                      tell_object(who, "将军府后花园乃是清静之地，不可弄刀弄抢。！\n"); 
                return 1; 
      } 
*/
