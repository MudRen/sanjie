// huxindan.c 翠袖护心丹
// Created by kuku@sjsh 2003.2

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(GRN"翠袖护心丹"NOR, ({ "huxin dan","dan" }) );        
        set("weight", 90);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "治伤且能解毒之灵药。\n");
                set("unit", "颗");
                set("value", 2000);
                set("drug_type", "补品");
        }
        set("is_monitored",1);
        setup();
}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_drop","drop");
}

int do_eat(string arg)
{
        object ob;
        ob=this_player();
        
        if (arg!="dan" && arg!="huxin dan")
                return 0;
        if (arg!="dan" ) return 0;
              
        if( living(this_player()) ==0 ) return 0;
        ob->set("kee",(int)ob->query("max_kee"));
        ob->set("gin",(int)ob->query("max_gin"));
        ob->set("sen",(int)ob->query("max_sen"));       
        ob->set("eff_kee",(int)ob->query("max_kee"));
        ob->set("eff_gin",(int)ob->query("max_gin"));
        ob->set("eff_sen",(int)ob->query("max_sen"));
        
        ob->set("force", (int)ob->query("max_force"));
        ob->set("mana", (int)ob->query("max_mana"));
        
        ob->set("food",(int)ob->max_food_capacity());
        ob->set("water",(int)ob->max_water_capacity());
        if((int)ob->query_condition("ice_poison"))
                ob->clear_condition("ice_poison");
        if((int)ob->query_condition("double_ice_poison"))
                ob->clear_condition("double_ice_poison");

        write(GRN+"你吞下一颗翠袖护心丹，顿觉心清气爽，身上的伤已经痊愈，体内的寒毒也被驱除了。\n"NOR);

        message("vision", GRN + ob->name() + "吞下一颗翠袖护心丹，顿觉心清气爽，身上的伤已经痊愈，体内的寒毒也被驱除了。\n"+NOR,
                environment(ob), ob);
        destruct(this_object());
        return 1;
}

int do_drop(string arg)
{
        object ob = this_object();
        object me = this_player();
        
        if(arg == "huxin dan" || arg == "dan"){
                message_vision("好可惜呀，这么珍贵的药就这样被"+me->query("name")+"随手扔掉了，"+ob->query("name")+"转眼间就消失的无影无踪。\n",me,ob); 
                destruct(ob);
        }
        return 1;
}
