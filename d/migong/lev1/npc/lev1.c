// migong lev1

#include <ansi.h>

inherit NPC;

string *names = ({
    "火狐狸",
    "花狐狸",
    "野狐狸",
    "灰狐狸",
});

void create()
{
        string str;
        set_name(names[random(sizeof(names))], ({"hu li","huli", "fox"}));
        set("race", "野兽");
        set("long",
"一只狡猾的狐狸。\n");
        set("age", 40+random(51));
        set("combat_exp", 500000+random(500001));
        set("daoxing", 500000+random(500001));
        set("limbs", ({ "头部", "身体", "前爪", "尾巴", "肚皮", "后爪"}) );
        set("verbs", ({ "bite", "claw"}) );
        set("attitude", "aggressive");
        set("per", 10);
        set_skill("parry", 200);
        set_skill("unarmed", 200);
        set_skill("dodge", 200);
        set_skill("blade", 200);
        set("max_sen",2000);
        set("max_kee",2000);
        set("force",2000);
        set("max_force",1500);
        set("max_mana",1500);
        set("mana",2000);
        set("mana_factor",80);
        set("force_factor",80);
        add_temp("apply/damage", 50);
        setup();
}


void init( )

{
        object ob;      
        remove_call_out("hunting");
        if( interactive(ob = this_player())  ) {
        call_out("hunting",1);
        }
        if(!environment()->query("no_fight") && random(10) < 5)
        call_out("hunting",1);
}

void hunting()
{
        int i;
        object *ob;
        ob = all_inventory(environment());
        for(i=sizeof(ob)-1; i>=0; i--) {
        if( !ob[i]->is_character() || ob[i]==this_object() || !living(ob[i])) continue;
        if(ob[i]->query("vendetta/authority")) continue;
                kill_ob(ob[i]);
                ob[i]->fight(this_object());
        }
}

void die()
{
        object ob, me, corpse;
        
        ob = this_object();
        me = query_temp("last_damage_from");
        
        message_vision(WHT"$N一声惨叫,砰然倒地，化为一股青烟消散了。\n"NOR,ob,me);
        if( objectp(corpse = CHAR_D->make_corpse(this_object())) )
                corpse->move(environment(this_object()));
        if((int)me->query("combat_exp") < 300000)   {
                message("vision", me->name() + "成功消灭迷宫妖孽增加了40经验,二十天道行,20潜能。\n", me);
                me->add("combat_exp",40);
                me->add("daoxing",80);
                me->add("potential",20);
                destruct(ob);
        }

   
        destruct(ob);
        return;
}

