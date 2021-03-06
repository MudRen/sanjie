
/* <SecCrypt CPL V3R05> */
 
// lzl.c
//lizuole 99.11.12

#include <ansi.h>
#include <login.h>
inherit NPC;

void create()
{
        set_name(HIR"李作乐"NOR, ({"lizuole","lzl","le"}));
        set("title",HIC"银行老板"NOR);
        set("gender", "男性" );
        set("age", 23);
        set("class","taoist");
        set("long", "这是潜能银行的总裁，年轻有为，目光中带着亲切。\n");
        set("combat_exp", 8000000);
        set("attitude", "peaceful");
       set("max_kee", 5000);
       set("max_gin", 1000);
       set("max_sen", 5000);
       set("force", 5000);
       set("max_force", 4500);
       set("force_factor", 150);
       set("max_mana", 4500);
       set("mana", 5000);
       set("mana_factor", 150);
       set("combat_exp", 3000000);
       set_skill("literate", 150);
       set_skill("unarmed", 150);
       set_skill("dodge", 170);
       set_skill("parry", 170);
       set_skill("stick", 150);
       set_skill("spells", 200);
       set_skill("dao", 180);
       set_skill("puti-zhi", 150);
       set_skill("wuxiangforce", 180);
       set_skill("force", 200);
       set_skill("qianjun-bang", 180);
       set_skill("jindouyun", 180);
       map_skill("spells", "dao");
       map_skill("unarmed", "puti-zhi");
       map_skill("force", "wuxiangforce");
       map_skill("stick", "qianjun-bang");
       map_skill("parry", "qianjun-bang");
       map_skill("dodge", "jindouyun");
       set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: cast_spell, "light" :),
                (: cast_spell, "dingshen" :),
                (: cast_spell, "thunder" :),
                (: cast_spell, "fenshen" :),
                (: cast_spell, "pili" :),
                (: cast_spell, "qiankun" :),
                (: cast_spell, "invocation" :),
        }) );
        setup();
        carry_object("/d/lizuole/obj/choupao")->wear();
        carry_object("/d/lizuole/obj/huanlebang")->wield();
       // carry_object("/d/obj/book/chunyang")->tear();
}

void init()
{
        object ob;

        ::init();
        set("chat_chance", 3);
        set("inquiry", ([
                "name" : "我是潜能银行的总裁，也是朋友最多的人。\n",
                "here" : "你没来过长安？这地方可是天下第一繁华所在。\n", 
   ]) );

   /*     set("chat_msg", ({
       "李作乐高声说：怕死的来我这存潜能呀。\n",   
                "李作乐上上下下打量了你几眼。\n",
                "李作乐用眼角瞥了你一眼说：没钱的一边凉快去！\n",
       }) );*/
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
        object stone;

        this_object()->add("time", 1);
        if( (int)this_object()->query("time") >= 3 ) {
        message("vision",name() + "吐了口唾沫，狠狠说道：下次别叫我碰到！
李作乐走了出去。\n", environment(),this_object() );
        destruct(this_object());

        }
        return;
}

