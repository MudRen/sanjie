// /d/quest/newdomain/npc/npc3.c
// Created by kuku 2003.5.10 
      
inherit NPC; 
#include <ansi.h> 

void create() 
{ 
        set_name( HIB "地狱使者" NOR, ({"hell envoy","envoy"})); 
        set("title",HIR+"奇幻世界探密报名处"+NOR);  
        set("long", "他看上去一脸严肃的样子。\n");  
        set("gender", "男性");  
        set("attitude", "peaceful"); 
        set("class", "xian"); 
        set("age", 16); 
        set("str", 40+random(10)); 
        set("int", 30); 
        set("per", 30+random(4)); 
        set("con", 20); 
        set("max_kee", 50000);    
        set("max_sen", 50000);     
        set("kee", 50000);   
        set("sen", 50000);    
        set("max_force", 30000);   
        set("force", 30000);  
        set("force_factor", 450);  
        set("max_mana", 30000);   
        set("mana", 30000);   
        set("mana_factor", 450);  
        set("combat_exp", 15000000);   
        set("daoxing", 15000000);   
    
        set("inquiry", ([   
                "奇幻探密": "你真的想去探险吗？你要知道你将去的地方是很危险的，\n"+
                "不过如果你有胆量前去一试，全身而退后还是会得到很丰厚的奖励的。\n"+
                "如果你已经决定了，请使用baoming先报名，不要走开，五分钟后我自\n"+
                "会送你进入那个神秘而充满挑战的世界。\n",
        ]));
         
        setup(); 
         
        carry_object("/d/obj/cloth/linen")->wear();   
        carry_object("/d/obj/weapon/sword/qinghong")->wield();   
} 

void init ()
{
        add_action ("do_baoming","baoming");
}
             
int do_baoming (string arg)
{ 
        int tt,j,k; 
        object *ilist;    
        object me = this_object();
        object who = this_player();
        
        if(who->query("daoxing")<5000000 || who->query("level") < 150){  
                command("say 以你现在的修为去探险太危险了，还是好好练练再来吧。\n");  
                command("pat " +who->query("id"));  
                return 1;
        } 
        
        if(who->query_temp("dyzz/baoming") ){
                command("say 你不是已经报过名了吗？请稍等片刻。\n");  
                return 1;
        }
        
        if(me->query("dyzz/baoming") >= 8){
                command("say 人数已经够了，你等一个小时后再来吧。\n");
                return 1;
        }
        
        ilist = all_inventory(who);
        k=0; 
        j = sizeof(ilist); 
        while (j--) { 
                if( ilist[j]->query("pass_level")<3 ) { 
                        continue; 
                }              
                k++; 
        } 
        if(k < 1 || !present("passport 3",who) ) 
                return notify_fail("你还没拿到去探险所需的通行证。\n");  
                         
        if( tt=(int)me->query("dyzz/enter") ) { 
                if(tt<=time() && time()<tt+3600) { 
                        message_vision("\n"+me->query("name")+"说道:报名工作已经结束，你还是等等再来吧。\n",who); 
                        return 1; 
                } 
        } 
        
        message("chat",YEL"【"+HIB"地狱使者"+YEL"】："HIR"奇幻世界探密"HIW"报名工作已经开始，欢迎勇士们前往奇幻世界！\n"NOR,users());   
        who->set_temp("dyzz/baoming",1);        
        me->add("dyzz/baoming",1);
        if( me->query("dyzz/baoming") ==8 ){
                remove_call_out("dyzz_enter");
                call_out("dyzz_enter",300,me);          
        }
        return 1;
}

int dyzz_enter(object me)
{
        object passport;
        object who = this_player();
        
        passport = present("passport 3",who);
        
        message("chat",YEL"【"+HIB"地狱使者"+YEL"】："HIR"奇幻世界探密"HIW"报名工作结束，一小时后可以继续报名。\n"NOR,users());   
        if (who->query_temp("dyzz/baoming") && passport && present(who, environment(me)) ){
                message_vision("$N将通行证交给$n。\n", who,me);  
                destruct(passport);
                tell_object(who,HIR"去那里凶多吉少啊，你要好自为之，我这就送你到那充满魅力的奇幻世界，祝你好运！\n"NOR);    
                tell_room(environment(who),HIB"\n突然一股阴风平地而起，把"+who->query("name")+"刮得无影无踪。\n"NOR);
                who->move("/d/quest/dyzz/saiwai");
                me->delete("dyzz/enter"); 
                who->delete_temp("dyzz/baoming");
                me->delete("dyzz/baoming");
                me->set("dyzz/enter",time());                 
        }        
        return 1; 
} 

void die()  
{ 
        message_vision(HIB"地狱使者"NOR+"「唉」的一声叹了口气。\n\n",this_object());  
        message_vision(HIB"地狱使者"NOR+"化做一道青烟消失了。。。 \n\n",this_object()); 
        destruct(this_object()); 
} 
