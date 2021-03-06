
inherit NPC;
void create()
{
	set_name("程玉环", ({ "cheng yuhuan", "cheng", "yuhuan" }));
	set("long", 
		"她就是程知府的独生女儿，长得如花似玉，貌赛天仙的程玉环。\n"
		"据说她曾经在武当门下学过剑法。\n");
		
	set("title", "知府千金");
	set("nickname", "玉仙姑");
	set("gender", "女性");
	set("age", 18);
       set("per",25);

	set("force", 400);
	set("max_force", 400);
	set("max_kee", 400);
	set("max_sen", 200);

	set_skill("force", 50);
	set_skill("unarmed", 40);
	set_skill("dodge", 60);
	set_skill("parry", 60);
	set_skill("sword", 60);
	set("combat_exp", 50000);
	setup();
}
