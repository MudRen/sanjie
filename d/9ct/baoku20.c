// /d/quest/yaota/baoku1.c  宝库
inherit ROOM;  
#include <ansi.h> 
#include <banned1.h>

void create() 
{ 
        set("short", HIW"废弃的宝库"NOR); 
        set("long", @LONG 
这是一间不大的石室，四壁俱是坚硬的岩石。 
LONG); 
        set("objects", ([ 
     ])); 
        set("exits", ([ 
                "north" : __DIR__"jiu", 
        ])); 
        set("9ctroom",1);
        setup(); 
} 

void init()
{
        object me=this_player();
        add_action("do_quit",banned_action);  
        if (me->query("env/invisibility"))  
            me->delete("env/invisibility");
                   
        if( !wizardp(me) && userp(me) ) {        
                remove_call_out("kick_ob");
                call_out("kick_ob",60);
        }
        add_action("do_cast","cast");
        add_action("do_exert","exert");
}

void kick_ob()
{
        object room,*obj;
        int i;

        obj=deep_inventory(this_object());
        if (!sizeof(obj))   return;
        for (i=0;i<sizeof(obj);i++){
                if (interactive(obj[i]) && (time()-obj[i]->query_temp("sky_enter_time"))>1800){
                        message_vision(CYN"一阵清风吹来,清烟消散,$N也随着清烟散去！\n"NOR,obj[i]);
                        if (!room=find_object("/d/city/kezhan") )
                                room=load_object("/d/city/kezhan");
                        obj[i]->move(room);
                        obj[i]->dismiss_team(); 
                        message("vision",CYN"一个人影随着一阵清烟从魔幻世界飘了出来!\n"NOR,room,({obj[i]}));
                        call_out("kick_ob",60);
                        return;
                }
        }
        call_out("kick_ob",60);
}

int do_quit(string arg) 
{  
        write("你不能在这里用这条命令。\n");  
        if (wizardp(this_player())) write("巫师请参阅同一路径内的banned.h文档。\n");  
        return 1;  
}  

int do_cast(string arg) { 
        if(!arg) return 0;
        if(arg !="transfer" ) write("你不能在这里用这条命令。\n");    
        command("cast transfer");
        return 1;
}

int do_exert(string arg) { 
        if(!arg) return 0;
        if(arg !="recover" && arg != "heal" && arg != "refresh") return 0;
        command("exert "+arg);  
}

