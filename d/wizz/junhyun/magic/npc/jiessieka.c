//魔导圣战NPC - 大魔导师杰希卡(未完成)
//by junhyun@SK
#include <ansi.h>
inherit NPC;
int give_gift();

void create()
{
        set_name(HIW"杰希卡"NOR, ({"jiessieka"}));
        set("title", HIW"大魔导师"NOR );
        set("nickname", HIW"永恒的贤者"NOR );
        set("gender", "女性" );
        set("age", 21);
        set("per", 40);
        set("str", 30);
            set ("long", @LONG
人类中最杰出的魔法师，拥有不老不死的身躯和灵魂
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


