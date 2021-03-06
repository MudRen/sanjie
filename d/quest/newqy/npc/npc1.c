// /d/quest/newdomain/npc/npc1.c
// Created by kuku 2003.5.10 
      
inherit NPC; 
#include <ansi.h> 

void create() 
{ 
        set_name( HIW "地仙祖师" NOR, ({"dixian zushi","zushi"})); 
        set("title",HIR+"海洋探险报名处"+NOR);  
        set("long", "一位风度翩翩、仙风道骨的老者。\n");  
        set("gender", "男性");  
        set("attitude", "peaceful"); 
        set("class", "xian"); 
        set("age", 46); 
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
                "海洋探险": "你真的想去探险吗？你要知道你将去的地方是很危险的，\n"+
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
        
        if(who->query("daoxing")<1000000 || who->query("level") < 50){  
                command("say 以你现在的修为去探险太危险了，还是好好练练再来吧。\n");  
                command("pat " +who->query("id"));  
                return 1;
        } 
        
        if(who->query("daoxing") >= 5000000 || who->query("level") >= 150){  
                command("say 你的修为太高了，不想去更好玩的地方探险吗？\n");  
                command("pat " +who->query("id"));  
                return 1;
        } 
        
        if(who->query_temp("sea/baoming") ){
                command("say 你不是已经报过名了吗？请稍等片刻。\n");  
                return 1;
        }
        
        if(me->query("sea/baoming") >= 8){
                command("say 人数已经够了，你等一个小时后再来吧。\n");
                return 1;
        }
        
        ilist = all_inventory(who);
        k=0; 
        j = sizeof(ilist); 
        while (j--) { 
                if( ilist[j]->query("pass_level")<1 ) { 
                        continue; 
                }              
                k++; 
        } 
        if(k < 1 || !present("passport 1",who) ) 
                return notify_fail("你还没拿到去探险所需的通行证。\n");  
                         
        if( tt=(int)me->query("sea/enter") ) { 
                if(tt<=time() && time()<tt+3600) { 
                        message_vision("\n"+me->query("name")+"说道:报名工作已经结束，你还是等等再来吧。\n",who); 
                        return 1; 
                } 
        } 
        
        message("chat",YEL"【"+HIW"地仙祖师"+YEL"】："HIR"海底世界探险"HIW"报名工作已经开始，欢迎勇士们前往魔幻世界！\n"NOR,users());   
        who->set_temp("sky/baoming",1);        
        me->add("sky/baoming",1);
        if( me->query("sky/baoming") ==8 ){
                remove_call_out("sky_enter");
                call_out("sky_enter",300,me);           
        }
        return 1;
}

int sky_enter(object me)
{
        object passport;
        object who = this_player();
        
        passport = present("passport 1",who);
        
        message("chat",YEL"【"+HIW"地仙祖师"+YEL"】："HIR"海底世界探险"HIW"报名工作结束，一小时后可以继续报名。\n"NOR,users());   
        if (who->query_temp("sea/baoming") && passport && present(who, environment(me)) ){
                message_vision("$N将通行证交给$n。\n", who,me);  
                destruct(passport);
                tell_object(who,HIR"去那里凶多吉少啊，你要好自为之，我这就送你到那充满魅力的奇幻世界，祝你好运！\n"NOR);    
                tell_room(environment(who),HIG"\n突然一股碧绿的水波涌来，把"+who->query("name")+"卷进水里不见了。\n"NOR);
                who->move("/d/quest/newdomain/sea/enter");
                me->delete("sea/enter"); 
                who->delete_temp("sea/baoming");
                me->delete("sea/baoming");
                me->set("sea/enter",time());                 
        }        
        return 1; 
} 

void die()  
{ 
        message_vision(HIW"地仙祖师"NOR+"「唉」的一声叹了口气。\n\n",this_object());  
        message_vision(HIW"地仙祖师"NOR+"化做一道青烟消失了。。。 \n\n",this_object()); 
        destruct(this_object()); 
} 
