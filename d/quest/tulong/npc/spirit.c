#include <ansi.h>

inherit NPC;

void create()
{
        string *order = ({"风", "云", "雨", "雷", "电", "雾", "水", "火", "地", "花"});

        set_name((order[random(10)]) + "精灵", ({ "spirit" }) );
        set("long", "这是一位来自精灵界的小精灵，背后有一对透明的羽翼。\n");
        set("attitude", "friendly");

        set("max_kee", 10100);
        set("max_sen", 10101);
        set("max_mana", 10100);
        set("max_force", 10100);
        set("force_factor", 400);
        set("force", 20100);
        set("mana", 20100);
        set("mana_factor", 400);
        set("str", 25);
        set("con", 25);
        set("int", 25); 
        set("dex", 25);
        set("per", 30);

        set("combat_exp", 11100000);
        set_skill("blade", 800);
        set_skill("spirit-blade", 800);
        set_skill("spirit-dodge", 800);
        set_skill("parry", 800);
        set_skill("dodge", 800);

        map_skill("blade", "spirit-blade");
        map_skill("parry", "spirit-blade");
        map_skill("dodge", "spirit-dodge");
        setup();

        carry_object("/d/obj/weapon/blade/jindao")->wield();
}

int heal_up()
{
        if( environment() && !is_fighting() ) {
                call_out("leave", 1);
                return 1;
        }
        return ::heal_up() + 1;
}

void leave()
{
        message("vision",
                HIW + name() + "说道：我不能久留，既然事情已经结束，我要回精灵界了！\n\n"
                + name() + "化成一道柔和的光芒，渐渐消失不见了。\n" NOR, environment(),
                this_object() );
        destruct(this_object());
}

void invocation(object who)
{
        int i;
        object *enemy;

        message("vision",
                HIY "一阵清风吹过，一个小精灵随风而来。\n\n"
                + name() + "说道：我是接受精灵刀的召唤来帮忙的！\n" NOR,
                environment(), this_object() );
        enemy = who->query_enemy();
        i = sizeof(enemy);
        while(i--) {
                if( enemy[i] && living(enemy[i]) ) {
                        kill_ob(enemy[i]);
                        if( userp(enemy[i]) ) enemy[i]->fight_ob(this_object());
                        else enemy[i]->kill_ob(this_object());
                }
        }
        set_leader(who);
}


