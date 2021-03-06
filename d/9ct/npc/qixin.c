// 九重天神 "枷叶摩尼 启心" by Calvin

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
       set_name(HIY"启心祖师"NOR, ({"master qixin","qixin","qi","xin" ,"tianshen","master"}));
       set("long", "天道主枷叶摩尼是弥勒佛二世,在先天界曾是菩提前身一日之师\n");
       set("title", HIY"枷叶摩尼"NOR);
       set("gender", "男性");
       set("age", 100);
        set("class", "taoist");
       set("attitude", "friendly");
       set("shen_type", 1);
       set("rank_info/respect", "天道祖");
       set("per", 40);
       set("looking", "玉面多光润，苍髯颌下飘，金睛飞火焰，长目过眉梢。");
       set("int", 35);
       set("max_gin", 1000);
       set("max_kee", 10000);
       set("force", 13000);
       set("max_sen", 10000);
       set("force_factor", 250);
       set("max_force", 4500);
       set("max_mana", 4500);
        set("daoxing", 35000000);
       set("mana", 13000);
       set("mana_factor", 250);
       set("combat_exp", 10000000);

       set_skill("literate", 350);
       set_skill("unarmed", 350);
       set_skill("dodge", 350);
       set_skill("parry", 350);
        set_skill("stick", 350);
        set_skill("sword", 350);
        set_skill("liangyi-sword", 350);
        set_skill("spells", 350);
        set_skill("dao", 350);
        set_skill("puti-zhi", 350);
        set_skill("wuxiangforce", 350);
        set_skill("force", 350);
        set_skill("qianjun-bang", 350);
        set_skill("jindouyun", 350);
        map_skill("spells", "dao");
        map_skill("unarmed", "puti-zhi");
        map_skill("force", "wuxiangforce");
        map_skill("stick", "qianjun-bang");
        map_skill("parry", "qianjun-bang");
        map_skill("dodge", "jindouyun");
        map_skill("sword", "liangyi-sword");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: cast_spell, "light" :),
                (: cast_spell, "dingshen" :),
                (: cast_spell, "thunder" :)
        }) );

        create_family("方寸山三星洞", 1, "蓝");
        setup();

        carry_object("/d/9ct/zb/zhua")->wield();
        carry_object("/d/9ct/zb/stick")->wield();
}

void attempt_apprentice(object ob)
{       ob=this_player();
        if( (string)ob->query("family/family_name")=="方寸山三星洞") {
        if ((int)ob->query("daoxing") < 2000000 ) {
        command("say 不行," + RANK_D->query_respect(ob) + "还需多加悟道啊。\n");
        return;
        }
/*
        if( (int)ob->query("pending/kick_out")) {
        command("say 这位" + RANK_D->query_respect(ob) + "我派掌门近来通告我,你有反复无常的心理,恐怕是收不了你了!\n");
        command("sigh");
        return;
        }
*/
        if ((int)ob->query_int() < 38) {
        command("say 这位" + RANK_D->query_respect(ob) + "悟性太低，恐怕收了你也难有作为！\n");
        command("sigh");
        return;
        }

        if( (int)ob->query_skill("dao", 1) < 220 ) {
        command("say 这位" + RANK_D->query_respect(ob) + "对我道家仙法领会还不够深，现在收你也是勉为其难，不如作罢！\n");
        command("sigh");
        return;
        }
        command("smile");
        command("say 很好，" + RANK_D->query_respect(ob) + "多加努力，他日必定有成。");
command("recruit " + ob->query("id") );
        return;
        }
        command("shake");
        command("say 老夫不收外门弟子，" + RANK_D->query_respect(ob) + "还是另寻他人吧！\n");
        return;
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "taoist");
        if( (string)ob->query("gender") == "女性" )
                ob->set("title", HIC"方寸山三星圣母"NOR);
        else
                ob->set("title", HIC"方寸山无量天尊"NOR);
}

