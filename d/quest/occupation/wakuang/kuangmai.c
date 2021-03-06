// Created by kuku@sjsh 2003.2
// 职业任务 （矿工）与武器打造相结合

#include <ansi.h>
inherit ITEM;  

string *kuang1=({"/d/quest/occupation/wakuang/obj/tong-kuang","/d/quest/occupation/wakuang/obj/tie-kuang"});
string *kuang2=({"/d/quest/occupation/wakuang/obj/tong-kuang","/d/quest/occupation/wakuang/obj/tie-kuang","/d/quest/occupation/wakuang/obj/zitong-kuang"});
string *kuang3=({"/d/quest/occupation/wakuang/obj/tong-kuang","/d/quest/occupation/wakuang/obj/tie-kuang","/d/quest/occupation/wakuang/obj/zitong-kuang","/d/quest/occupation/wakuang/obj/chitie-kuang"});
string *kuang4=({"/d/quest/occupation/wakuang/obj/tong-kuang","/d/quest/occupation/wakuang/obj/tie-kuang","/d/quest/occupation/wakuang/obj/zitong-kuang","/d/quest/occupation/wakuang/obj/chitie-kuang","/d/quest/occupation/wakuang/obj/nietie-kuang"});
string *kuang5=({"/d/quest/occupation/wakuang/obj/tong-kuang","/d/quest/occupation/wakuang/obj/tie-kuang","/d/quest/occupation/wakuang/obj/zitong-kuang","/d/quest/occupation/wakuang/obj/chitie-kuang","/d/quest/occupation/wakuang/obj/nietie-kuang","/d/quest/occupation/wakuang/obj/yin-kuang"});
string *kuang6=({"/d/quest/occupation/wakuang/obj/tong-kuang","/d/quest/occupation/wakuang/obj/tie-kuang","/d/quest/occupation/wakuang/obj/zitong-kuang","/d/quest/occupation/wakuang/obj/chitie-kuang","/d/quest/occupation/wakuang/obj/nietie-kuang","/d/quest/occupation/wakuang/obj/yin-kuang","/d/quest/occupation/wakuang/obj/jin-kuang"});

void init()
{
        add_action("do_wakuang", "wakuang");
}

void create() 
{
        set_name("矿脉",({"kuang mai", "mai"}));
        set_weight(500000000);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "块");
                set("no_drop","不要乱丢，这东西打到人痛！\n");
                set("no_put",1);
                set("no_get",1);
                set("no_give",1);
                set("long", "这是一条很好的矿脉，你可以用（wakuang）来试试你的运气如何。\n");
        }
        setup();
}

int do_wakuang()
{
        object me=this_player();

        if( me->is_busy() ) return notify_fail("你现在很忙！不能挖！\n");
        if ((me->query("sen") < 30)){  
                tell_object(me,"你的精神不能集中，不可以挖矿石！\n");
                return 1;
        }
        else if ((me->query("kee") < 50 )){
                tell_object(me,"你的身体状态太差，不能挖矿石！\n");
                return 1;
        }
        
        if(!me->query("occupation") || me->query("occupation") != "矿工"){
                tell_object(me,"只有矿工才能挖矿。\n");
                return 1;
        }
                
        if(me->query("combat_exp") < 500000){
                tell_object(me,"你的武学经验不够。\n");
                return 1;
        }

        message_vision(HIC"$N挥动铁镐开始在地上挖了起来。\n"NOR,me);
        me->add("sen",-20);
        me->add("kee",-30);
        me->start_busy(6);   
        call_out("wakuang",5,me);
        me->stop_busy();
        return 1;
}

int wakuang(object me)
{
        object ob;

        if (random(10)<7){
                message_vision(CYN"一阵挖掘之后，$N什么也没挖到。\n"NOR,me);
                return 1;
        }
        else if ((int)me->query("work/wakuang") > 30000 ){
                message_vision(HIR"$N熟练的在矿脉中找来查去，不一会儿就找出一块好矿石。\n"NOR,me); 
                me->add("work/wakuang",1);
                ob=new(kuang6[random(7)]);
                ob->move(me);
                ob->set_temp("wakuang/owned",7);
                destruct(this_object());
                return 1;
        }
        else if ((int)me->query("work/wakuang") > 25000 ){
                message_vision(HIY"$N熟练的在矿脉中找来查去，不一会儿就找出一块好矿石。\n"NOR,me); 
                me->add("work/wakuang",1);
                ob=new(kuang5[random(6)]);
                ob->move(me);
                ob->set_temp("wakuang/owned",6);
                destruct(this_object());
                return 1;
        }
        else if ((int)me->query("work/wakuang") > 20000 ){
                message_vision(HIY"$N熟练的在矿脉中找来查去，不一会儿就找出一块好矿石。\n"NOR,me); 
                me->add("work/wakuang",1);
                ob=new(kuang4[random(5)]);
                ob->move(me);
                ob->set_temp("wakuang/owned",5);
                destruct(this_object());
                return 1;
        }       
        else if ((int)me->query("work/wakuang") > 15000 ){
                message_vision(HIY"$N在矿脉中翻来覆去，找出一块好矿石。\n"NOR,me); 
                me->add("work/wakuang",1);
                ob=new(kuang3[random(4)]);
                ob->move(me);
                ob->set_temp("wakuang/owned",4);
                destruct(this_object());
                return 1;
        }
        else if ((int)me->query("work/wakuang") > 10000 ){
                message_vision(HIY"$N在矿脉中找来查去，好久才找出一块矿石。\n"NOR,me); 
                me->add("work/wakuang",1);
                ob=new(kuang2[random(3)]);
                ob->move(me);
                ob->set_temp("wakuang/owned",3);
                destruct(this_object());
                return 1;
        }
        else if ((int)me->query("work/wakuang") > 5000 ){
                message_vision(HIY"$N在矿脉中摸来摸去，好不容易找出一块矿石。\n"NOR,me); 
                me->add("work/wakuang",1);
                ob=new(kuang1[random(2)]);
                ob->move(me);
                ob->set_temp("wakuang/owned",2);
                destruct(this_object());
                return 1;
        }
        else{ 
                message_vision(HIG"$N找了半天，终于发现其中一块石头是矿石。\n"NOR,me); 
                me->add("work/wakuang",1);
                ob = new( __DIR__ "obj/tong-kuang");
                ob->move(me);
                ob->set_temp("wakuang/owned",1);
                destruct(this_object());
        }
        return 1;
}
