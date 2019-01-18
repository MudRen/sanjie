// monkey.c

inherit NPC;
#include <ansi.h>

int ask_chenxiang ();

void create()
{
        set_name("小猴子", ({ "xiao houzi","xiaohouzi","monkey","hou" }) );
        set("long", "一只和沉香经常玩的小猴子。\n");
        set("gender","男性");
        set("age", 6);
        set("per",20+random(5));
        set("str", 30);
        set("cor", 26); 
        set("combat_exp", 50);
  set("daoxing", 0);

            set_skill("dodge",20);
            set_skill("unarmed",10);
        set("limbs", ({ "头部", "身体", "前爪", "后脚", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("chat_chance", 10);
        set("chat_msg", ({
                (: call_other, this_object(), "random_move" :),
                "小猴子说道：沉香你真命苦呀！\n",
                "小猴子说道：这几天真不知道沉香在干吗。\n",
                "小猴子说道：沉香我该怎么帮你呢？\n",
                "小猴子说道：真想和沉香好好玩一下。\n" }) );

          set("inquiry", ([
    "沉香" : (: ask_chenxiang :),
    "chenxiang" : (: ask_chenxiang :),
  ]) );

       setup();
}


int ask_chenxiang ()
{     
        object ob;
ob = new ("/d/quest/bld/npc/chenxiang");

        if (this_player()->query("bld/done") == 1)
        {
               command("heng");
               command("say 你都救过了还来问我？ \n");
               return 1;
        }
         
if (this_player()->query("bld/monkey") == 1)
return notify_fail("你不是知道了吗？ \n");

        command("heihei");
        command("say 你可问对人了！ \n");
        command("say 沉香就在花果山哦！自己去找找吧！ \n");
        command("addoil");
        command("say 走了，我去找沉香了！ \n");
        message_vision("小猴子一晃身子消失了！ \n",this_player());
        this_player()->set("bld/monkey",1);
ob->move("/d/dntg/hgs/flowerfruit");
        destruct(this_object());
        return 1;
}

