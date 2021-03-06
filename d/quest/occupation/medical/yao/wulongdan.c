// wulongdan.c 五龙丹
// Created by kuku@sjsh 2003.2

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(BLU"五龙丹"NOR, ({ "wulong dan","dan" }) );        
        set("weight", 50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","一颗灵药，可解奇毒。\n");
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
        
        if (arg!="dan" && arg!="wulong dan")
                return 0;
        if (arg!="dan" ) return 0;

        if((int)ob->query_condition("cold_poison"))
                ob->clear_condition("cold_poison");
        if((int)ob->query_condition("hb_poison"))
                ob->clear_condition("hb_poison");
        if((int)ob->query_condition("yyz_hurt"))
                ob->clear_condition("yyz_hurt");
        if((int)ob->query_condition("scorpion_poison"))
                ob->clear_condition("scorpion_poison");

        write(BLU+"你拿出一颗五龙丹，放入口中，吞了下去，不消片刻，身体里的奇毒就被祛除干净了。\n"NOR);

        message("vision", BLU + ob->name() + 
"拿出一颗五龙丹，放入口中，吞了下去，不消片刻，身体里的奇毒就被祛除干净了。\n"+NOR,
                environment(ob), ob);
        destruct(this_object());
        return 1;
}

int do_drop(string arg)
{
        object ob = this_object();
        object me = this_player();
        
        if(arg == "wulong dan" || arg == "dan"){
                message_vision("好可惜呀，这么珍贵的药就这样被"+me->query("name")+"随手扔掉了，"+ob->query("name")+"转眼间就消失的无影无踪。\n",me,ob); 
                destruct(ob);
        }
        return 1;
}
