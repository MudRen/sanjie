//魔导圣战NPC - 三界破坏神狱狂之拜狱(未完成)
//by junhyun@SK
#include <ansi.h>
inherit NPC;
int give_gift();

void create()
{
        set_name(HIW"拜狱"NOR, ({"baiyu"}));
        set("title", HIR"三界破坏神"NOR );
        set("nickname", HIC"狱狂神"NOR );
        set("gender", "男性" );
        set("age", 21);
        set("per", 40);
        set("str", 30);
            set ("long", @LONG
被永恒的不死诅咒的破环神，灵魂被深深的囚禁在人类的
身体力，堕入无尽的轮回中。
LONG);

        set("combat_exp", 290000);
        set("daoxing", 40000000000);
        set_skill("unarmed", 370);
        set_skill("dodge", 340);
        set("max_kee", 10000);
        set("max_sen", 10000);
        set("force", 6000);
        set("max_force", 3000);
        set("mana", 6000);
        set("max_mana", 3000);  
        set("force_factor", 1000);
        set("mana_factor", 1000);
        set("inquiry", ([
           "name" : "哼，想知道我的名字，就要用血来祭奠！\n",
     "here" : "这里是黑暗的边缘，你要不要来加入我们？\n",
         ]) );


            setup();
}


