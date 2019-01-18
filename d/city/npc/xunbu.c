// xunpu.c 巡捕
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("巡捕", ({ "xun bu", "bu", "xun" }));
        set("gender", "男性");
        set("age", random(10) + 40);
        set("str", 25);
        set("dex", 16);
        set("long",       "这是个正在执行公务的巡捕，如果你杀了人，还是。。。快跑啊！！！\n");
        set("combat_exp", 100000+random(6000000));
        set("shen_type", 1);
        set("attitude", "peaceful");
        set_skill("unarmed", 60+random(100));
        set_skill("force", 110);
        set_skill("sword", 360+random(200));
        set_skill("dodge", 660+random(200));
        set_skill("parry", 360+random(200));
        set_temp("apply/attack", 250+random(50));
        set_temp("apply/defense", 250+random(50));
        set_temp("apply/armor", 250+random(50));
        set_temp("apply/damage", 230+random(30));
        set("force", 3400+random(1500)); 
        set("maximum_force", 3400+random(1500));
		set("max_force", 3400+random(1500));
        set("enforce", 10+random(100));
        set("chat_chance", 20);
        set("chat_msg", ({
       "\n巡捕拍了拍胸口，说道：有我在，谁都不可以杀人，谁杀了人就要偿命！\n",
       "\n巡捕看了你几眼，说道：可别杀人啊，否则老子一定不会放过你！\n",
        "\n巡捕说道：怎么今天没人杀人？闷死老子了！\n",
        (: random_move :)
        }) );
 
        setup();
        carry_object("/d/obj/weapon/sword/tiejian")->wield();
        carry_object("/d/obj/cloth/zhanpao")->wear();
}

void init()
{
        object ob;
        ::init();
        if (!living(this_object())) return;
        if (!userp(this_object())) return;

        if (interactive(ob = this_player())){
                        if ( (int)ob->query_condition("killer")) {
                    command("say "+ob->name()+"，你杀了人，还想往那逃？！");
			this_object()->set_leader(ob);

                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob);
                                        return ;
                }

                if (  ((int)ob->query_condition("killer")>0) && ob->query("race")=="人类" 
                   && ((int)ob->query("summon_time")+3600)< time() ) {
                remove_call_out("summon_ob");
                call_out("summon_ob", 1, ob);
                                return;
        }

            add_action("do_kill","kill");
        }

}

void summon_ob(object ob)
{
    object room;

    if (!ob || environment(ob)!=environment())
            return;
       if( ob->query("env/invisibility") ) return;
       if( !userp(ob) && wizardp(ob) ) return;

        if (! room=find_object("/d/city/misc/dalao"))
            room=load_object("/d/city/misc/dalao");

	if (!this_player()->query_temp("armor/cloth") && this_player()->query("race")=="人类" ) {
//        message_vision("\n$N一把抓住$n，光天化日，当街裸跑，有伤风化！\n\n",this_object(),ob);
        message_vision("\n$N一把抓住$n，大胆逃犯，光天化日，招摇过市，与我回衙门！\n\n",this_object(),ob);
        message_vision("$N拎着$n向衙门走去！\n",this_object(),ob);
        ob->move(room);
	ob->set("summon_time",time()+3600);
	message("vision",YEL+"\n\n当啷一声，一个赤条条的家伙被扔了进来。\n\n"+NOR,room,({ob}));
	}
        if (! room=find_object("/d/city/baihu-w1"))
            room=load_object("/d/city/baihu-w1");
        this_object()->move(room);
}

int do_kill(string arg)
{
        object ob;
      if (!environment()) return 0;
        if (ob=present(arg,environment()))
        if (userp(ob)){

            command("say 想在大爷面前撒野？找死呀！");
            kill_ob(this_player());
        }
    return 0;
}

