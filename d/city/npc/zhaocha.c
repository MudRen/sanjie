//Creat by waiwai@2000/07/20

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("乞丐", ({ "qi-gai" }) );
	set("long", "这是一个普通的乞丐，但是似乎身怀绝技。\n");
	set("attitude", "friendly");

	set("str", 40+random(60));
	set("cor", 30);
	set("cps", 25);

	set("combat_exp", 5000000+random(9000000));

	set("chat_chance", 30);
	set("chat_msg_combat", ({
		"乞丐喝道：敢在这撒野！活得不耐烦了！\n",
		(: command("crazy") :),
	}) );
	set_skill("unarmed", 500+random(1000));
	set_skill("dodge", 500+ random(1000));
	set_skill("parry", 500+ random(1000));

	setup();

	carry_object("/d/tianpeng/hu/obj/jncloth")->wear();
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
		HIW + name() + "狠狠往地下啐了一口道：下次没这么便宜！\n\n"
		+ name() + "恨恨地跺了跺脚，一溜烟跑了。\n" NOR, environment(),
		this_object() );
	destruct(this_object());
}
