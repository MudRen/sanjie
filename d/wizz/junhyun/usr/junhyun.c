//玩家NPC
//plum.c   by junhyun@SK

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
void create()
{
        set_name("数码宝贝", ({"junhyun's"}));
        set("title", HIW"神天の月"NOR);
        set("gender", "女性" );
        set("age", 20);
        set("per", 40);
        set("str", 330);
set("long","
蛇口站程序开发巫师，没什么本事，整天就会瞎折腾
估计快被踢出蛇口站了，赶紧给自己做个塑像纪念一
下……
\n");

       set("shen_type", 1);
       set("combat_exp", 50000000);
       set("daoxing", 2000000000);
       set("max_kee",90000);
       set("max_gin",90000);
       set("max_sen",90000);
       set("force", 180000);
      set("max_force", 90000);
       set("force_factor", 500);
       set("max_mana", 90000);
       set("mana", 180000);
       set("mana_factor", 500);

       set_skill("dodge", 550);
       set_skill("kongming-steps", 550);
       set_skill("force", 550);
       set_skill("jiuyin-force", 550);
       set_skill("spells", 550);
       set_skill("youming-spells", 550);
       set_skill("sword", 550);
       set_skill("qinghu-jian", 550);
       set_skill("shengling-sword", 550);
       set_skill("blade", 550);
       set_skill("zizhi-blade", 550);
       set_skill("mohuang-blade", 550);
       set_skill("unarmed", 550);
       set_skill("jiuyin-zhua", 550);
       set_skill("literate", 550);
       set_skill("parry", 550);
       set_skill("mace", 550);
       set_skill("yinlei-mace", 550);



        map_skill("dodge", "kongming-steps");
        map_skill("force", "jiuyin-force");
        map_skill("parry", "qinghu-jian");
        map_skill("spells", "youming-spells");
        map_skill("blade", "zizhi-blade");
        map_skill("unarmed", "jiuyin-zhua");
        map_skill("sword", "qinghu-jian");

       set("chat_msg_combat", ({
              (: perform_action, "sword", "ji" :),
              (: perform_action, "sword", "po" :),
              (: perform_action, "sword", "hebi" :),
                }) );
        set_temp("apply/armor",50);
        set_temp("apply/damage",25);
        setup();
        carry_object("d/wizz/junhyun/usr/obj/godshield")->wear();
        carry_object("d/wizz/junhyun/usr/obj/godarmor")->wear();
        carry_object("d/wizz/junhyun/usr/obj/sessword.c")->wield();
}

