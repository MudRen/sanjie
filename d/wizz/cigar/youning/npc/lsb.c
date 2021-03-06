//梁山伯.c BY cigar 2002.01
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
       set_name(HIC"梁山伯"NOR, ({"liang shanbo", "liang", "shanbo","master"}));
       set("long",
"他乃是化蝶之后感动上天被文殊菩萨给予真身幻化而成的，现在身居幽谷陪伴祝英台。\n");
       set("title", HIR"蝶"+HIY"恋"NOR);
       set("gender", "男性");
       set("age", 20);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "蝶仙");
       set("per", 30);
        set("int", 30);
       set("max_kee", 500);
       set("max_gin", 500);
       set("max_sen", 500);
       set("force", 500);
       set("max_force", 500);
       set("force_factor", 20);
       set("max_mana", 300);
       set("mana", 300);
       set("mana_factor", 20);
       set("combat_exp", 200000);
  set("daoxing", 100000);


        set("eff_dx", 70000);
        set("nkgain", 260);

       set_skill("literate", 100);
       set_skill("unarmed", 80);
       set_skill("dodge", 80);
       set_skill("force", 80);
       set_skill("parry", 80);
       set_skill("hammer", 80);
       set_skill("spells", 80);
        set_skill("wuji", 80);
        set_skill("suiyu-zhang", 80);
        set_skill("lianxin-force", 80);
        set_skill("fengri-hammer", 60);
        set_skill("ningxin-step", 60);
        map_skill("spells", "wuji");
        map_skill("unarmed", "suiyu-zhang");
        map_skill("force", "lianxin-force");
        map_skill("hammer", "fengri-hammer");
        map_skill("parry", "fengri-hammer");
        map_skill("dodge", "ningxin-step");

           create_family("幽凝谷", 4, "幽谷小仙");
setup();

        carry_object("/d/moon/obj/luoyi")->wear();
        carry_object("/d/obj/weapon/hammer/falun")->wield();
}

void attempt_apprentice(object ob)
{
        if ( !((string)ob->query("gender")=="男性")){
           command("shake");
           command("say 我只收男徒，这位" +
RANK_D->query_respect(ob) + "还是去找我家内堂吧。\n");
           return;
        }

        command("pat "+ob->query("id"));
        command("say 好，希望" + RANK_D->query_respect(ob) +
"多加努力，把我们幽凝谷发扬光大。\n");
        command("recruit " + ob->query("id") );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "xian");
}
