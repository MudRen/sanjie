//十本刀之天剑·濑田宗次郎
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("濑田宗次郎", ({"kasuki zinomiya","zongcilang"}));
        set("nickname", HIB"天剑"NOR  );
        set("title", HIW"十本刀"NOR );
        set("gender", "男 性" );
        set("age", 21);
        set("per", 40);
        set("str", 20);
            set ("long", @LONG
志志雄的左膀右臂，也许是十本刀中真正可称为最强
的天才剑士，由于有着亲手将自己的家族全部杀戮殆
尽的经历，因此养成了在任何情况之下都只有笑这种
感情的习性，在同剑心的战斗中，丧失已久的感情回
到了他的身体里，使他最终背弃了志志雄。
LONG);

        set("combat_exp", 150000000);
        set("daoxing", 150000000);
        set_skill("unarmed", 600);
        set_skill("dodge", 600);
        set_skill("force", 600);
        set_skill("spells",600);
        set_skill("sword",600);
        set_skill("feitian-jian",600);
        map_skill("sword", "feitian-jian");
        set("max_kee", 6000);
        set("max_sen", 6000);
        set("force", 12000);
        set("max_force", 6000);
        set("mana", 12000);
        set("max_mana", 6000);  
        set("force_factor", 100);
        set("mana_factor", 100);


        set("inquiry", ([
           "name" : "我就是十本刀之夜伽·驹形由美\n",
     "here" : "我也不知道这是那里。\n",
     "志志雄" : "我所爱的男人，他才是真正的英雄！\n",
     "十本刀" : "你是不可能战胜十本刀的！\n", 
         ]) );


            setup();

        carry_object("d/wizz/junhyun/japan-sword1")->wield();

}

