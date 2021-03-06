// hua.c
// created by kuku@sjsh 2002/12

#include <ansi.h>
inherit NPC;
int ask_jiu();
#include "huajob.c"

void create()
{
     set_name("花木兰", ({"hua mulan", "hua", "mulan"}));
    set("gender", "女性");
    set("title",HIM"替父从军"NOR);
    set("age", 20);
    set("long", "她就是远近闻名的女英雄花木兰。\n");
    set("attitude", "peaceful");
    set_max_encumbrance(100000000);   
    set("per", 40);
    set("str", 18);
    set("int", 30);
    set("con", 21);
    set("kee", 2000);
    set("max_kee", 2000);
    set("sen", 1000);
    set("max_sen", 1000);
    set("force", 2000);
    set("max_force", 2000);       
    set("combat_exp", 8000000);
    set_skill("force", 600);
    set_skill("lengquan-force", 600);
    set_skill("unarmed", 600);
    set_skill("changquan", 600);
    set_skill("dodge", 600);
    set_skill("yanxing-steps", 600);
    set_skill("parry", 600);
    set_skill("spear", 600);
    set_skill("bawang-qiang", 600);
    set_skill("spells", 600);
    set_skill("baguazhou", 600);
  set("inquiry", ([ 
                 "job"   : (: ask_job :),
               "黄酒" : (: ask_jiu :),
         "fangqi": (: ask_fangqi :),
         "放弃"  : (: ask_fangqi :),
                 ]));      
    map_skill("force"  , "lengquan-force");
    map_skill("unarmed", "changquan");
    map_skill("dodge"  , "yanxing-steps");
    map_skill("spear"  , "bawang-qiang");
    map_skill("spells"  , "baguazhou");

    create_family("将军府", 2, "弟子");
    setup();
    carry_object("/d/obj/cloth/skirt")->wear();
    carry_object("/d/obj/cloth/shoes")->wear();
    carry_object("/d/obj/weapon/spear/jinqiang")->wield();
}
