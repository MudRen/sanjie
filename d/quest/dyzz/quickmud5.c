// Room: /d/quest/dyzz/quickmud5.c

#include <ansi.h>
#include <room.h>
inherit ROOM;
int do_sanddrop(object me, object obj);

void create()
{
        set("short", "沼泽中");
        set("long", @LONG
你以经陷入沼泽之中，四周没有一点着力的地方。你一点点的向下落去。
除非有人拉(pull)你一把，想活着离开这里恐怕比登天还难。你似乎已
经绝望了。
LONG
        );

        set("NONPC",1);
        set("no_move",1);
        
        setup();
}

void init()
{       object ob;
        if( interactive( ob = this_player())){
                remove_call_out("sinking");
                call_out("sinking", 1, ob);
        }
        add_action("do_accept","accept");
        add_action("do_cast","cast");
        add_action("do_quit","quit");
        
        if( !wizardp(ob) && userp(ob) ) {        
                remove_call_out("kick_ob");
                call_out("kick_ob",900);
        }        
}

int sinking(object ob)
{
        int i;
        int damage;
        if( ob && environment(ob) == this_object()){
                message_vision(HIW"$N又在沼泽中陷深了一些！！\n"NOR, ob);
                message_vision("$N几乎在绝望中哭了出来！！\n", ob);
                damage = random(20)+5;
                i =  (int)ob->query("kee");
                ob->set("kee",i - damage);
                if( environment(ob) == this_object())
                        call_out("sinking",random(5)+5, ob);    
        }
        return 1;
}

void kick_ob()
{
        object room,*obj;
        int i;

        obj=deep_inventory(this_object());
        if (!sizeof(obj))   return;
        for (i=0;i<sizeof(obj);i++){
                if (interactive(obj[i]) && (time()-obj[i]->query_temp("dyzz_enter_time"))>1800){
                        message_vision(CYN"一阵清风吹来,清烟消散,$N也随着清烟散去！\n"NOR,obj[i]);
                        if (!room=find_object("/d/city/kezhan") )
                                room=load_object("/d/city/kezhan");
                        obj[i]->move(room);
                        obj[i]->dismiss_team(); 
                        message("vision",CYN"一个人影随着一阵清烟从魔幻世界飘了出来!\n"NOR,room,({obj[i]}));
                        call_out("kick_ob",900);
                        return;
                }
        }
        call_out("kick_ob",900);
}

int do_accept(string arg) 
{  
        write("都陷进来了还想做什么啊？没人救你就哭吧。\n");  
        return 1;  
}   

int do_cast(string arg) 
{  
        write("都陷进来了还想做什么啊？没人救你就哭吧。\n");  
        return 1;  
}   

int do_quit(string arg) 
{  
        write("都陷进来了还想做什么啊？没人救你就哭吧。\n");  
        return 1;  
}   
