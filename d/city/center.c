//changan city

inherit ROOM;
#include <allcity.h>
#include <ansi.h>
int do_climb(string arg);
void create ()
{
  set ("short","十字街头");
  set ("long", @LONG

这里便是长安城的南部中心，南安大道和朱雀街交汇于此。一座
巍峨高大的鼓楼耸立于前，与北面的钟楼遥相呼应，高是33米，
建于明洪武十七年，楼上有巨鼓一面，每到傍晚，隆隆的鼓声便
会伴着落日的余辉传向长安城的大街小巷。路口车水马龙，来往
人潮不断。路边不知什么时候种了一颗大榕树(tree)，盘根错节，
已经很有一段历史了。
LONG);

        set("item_desc", ([
        "tree"  :   "一棵枝叶茂盛的大榕树，看来似乎可以爬(climb)上去。\n",
	]));
        set("exits", 
        ([
        "south" : "/d/city/zhuque-s1",
        "north" : __DIR__"xuanwu-n0",
        "west" : __DIR__"baihu-w1",
        "up" : __DIR__"jiuguan1",
        "east" : __DIR__"qinglong-e1",
        "down" : __DIR__"droproom",
        ]));
        set("objects", 
        ([
        WAI_OBJ"tree" : 1,
        __DIR__"npc/libai" : 1,
	"/d/qujing/wuzhuang/npc/zhangguolao": 1,
// 30        "/d/wizz/passion/npc/doudou": 1,
// 31  "/d/quest/li/litianwang.c": 1,
        ]));

	set("outdoors", 1);
       set("tsj_exst","west");
	setup();
}

void init()
{

	add_action("do_climb", "climb");


	//Modified by aeddy@2002/12/05	
	if( !userp(this_player()) ) return 0;

	if (!this_player()->query_temp("armor/cloth") && this_player()->query("race")=="人类" ) {
		this_player()->add_temp("rumor/nocloth",1);

		if ((int)this_player()->query_temp("rumor/nocloth")>10) {
		if (!this_player() && !userp(this_player()) && !wizardp(this_player()) ) return;

	       if( random(10) == 0 )
		tell_room(this_object(),
		RED+log_id(this_player())+"神色慌张地从街上裸奔而过。。。\n"NOR, this_player());

            }
	} 
}

int do_climb(string arg)
{
	int i;
	object me, *inv;
    
	me=this_player();
	inv = all_inventory(me); 
   
	if( !arg || arg!="up") return notify_fail("你要往哪个方向爬？\n");
	if(me->query_temp("ridee")) return notify_fail("你的坐骑不会爬树!\n");
   
	for(i=0;i<sizeof(inv);i++)
    
    	if(inv[i]->query("is_monitored"))
    	return notify_fail(inv[i]->query("name")+"不能带上树！\n");
	if(me->query_condition("killer")) {
       message("vision",
        me->name() + "战战兢兢地拉着大榕树的盘根，屁股一扭一扭地往上爬，突然一声惨叫，又掉了下来。\n",
        environment(me), ({me}) );
        write("你战战兢兢地拉着大榕树的盘根往上爬，一不小心摔了个狗吃屎。\n");
        return 1;
	}

	if (me->query("gender")!="女性")
	message("vision",
        me->name() + "战战兢兢地拉着大榕树的盘根，屁股一扭一扭地往上爬。\n",
        environment(me), ({me}) );
	else if(me->query("age")<40&&me->query("per")>24)
	message("vision",
        me->name() + "轻轻一跳，衣裙飘飘，象仙子般飞上大榕树。\n",
        environment(me), ({me}) );
	else message("vision",
        me->name() + "战战兢兢的抓住树干往上爬去。\n", environment(me), ({me}) );
                me->move(__DIR__"misc/chatroom");

	if (me->query("gender")!="女性")
        message("vision",
        me->name() + "气喘嘘嘘地爬了上来。\n",
                environment(me), ({me}) );
	else if(me->query("age")<40 && me->query("per")>24)
	message("vision",
	"一阵清香飞来，你定眼一看，"+ me->name(1) + "已经婷婷玉立在你眼前。\n",
        environment(me), ({me}) );
	else  message("vision", me->name(1) + "战战兢兢地从下面爬了上来。\n", environment(me), ({me}) );   
	return 1;
}   
/*
void do_rumor(object me)
{
    if (!me)    return;
     if (!userp(me)) return;
    tell_room(this_object(),RED+me->name(1)+"("+me->query("id")+")神色慌张地从街上裸奔而过。\n"NOR,me);
}


int valid_leave(object me, string dir)
{
 
	if ( userp(me) && (dir == "east"||dir=="west"
		||dir=="north"||dir=="south"||dir=="down"
		||dir=="up") ) {
		TOPTEN_D->topten_checkplayer(me);
		WEAPONTOP_D->topten_checkplayer(me);
		}

	return ::valid_leave(me, dir);
}
*/