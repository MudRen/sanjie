
inherit F_VENDOR_SALE;
int ask_heal();

void create()
{
        reload("city_yanglangzhong");
        set_name("杨郎中", ({"yang langzhong", "yang", "boss"}));
        set("title", "药铺掌柜");
        set("gender", "男性");
        set("age", 37);
        set("long",
"杨郎中是长安城里祖传的名医。虽然年轻，却早已名声在外。\n");
        set("kee", 900); 
        set("max_kee", 900);
        set("sen", 200);
        set("max_sen", 200);
        set("combat_exp", 5000000);
        set("attitude", "friendly");
//      set("env/wimpy", 50);

        set("inquiry", ([
        "疗伤": (: ask_heal :),
        "治疗": (: ask_heal :),
        "heal": (: ask_heal :),
        ]) );

        set("vendor_goods", ([
                "yao": "/d/obj/drug/jinchuang",
                "dan": "/d/obj/drug/hunyuandan",
                  "yanlei": "/d/obj/drug/yanlei",
                "tao" : "/d/obj/drug/mihoutao",
        "wan" : "/d/wizz/junhyun/obj/wan",
        ]) );

        set_skill("literate", 120);
        set_skill("unarmed", 120);
        set_skill("dodge", 120);

        setup();
        carry_object("/d/obj/cloth/choupao")->wear();
        add_money("silver", 30);
}

int ask_heal()
{
        object ob;
        ob=this_player();
        if ((int)ob->query("mud_age")>900000 )
        {
//        command("say 你应该自己去把医术学精点好自己给自己弄了！\n");
        command("say 你的年龄这么大了，自己解决！\n");
        return 1;
        }
        
       
        if ((int)ob->query("eff_kee") == (int)ob->query("max_kee")
                && (int)ob->query("eff_sen") == (int)ob->query("max_sen"))
        {
                command("?"+ob->query("id"));     
                command("say 你根本没受伤，跑我这里添乱！\n");
                command("knock"+ob->query("id"));
                return 1;
        }
        else
        {
                message_vision("杨掌柜拿出一根银针轻轻捻入$N受伤的部位附近的穴道，$N感觉舒服多了。\n", ob);
                remove_call_out("recover");
                call_out("recover",2,ob);
                return 1;
        }
        }
        
int recover(object ob)
{
        ob->set("eff_kee", (int)ob->query("max_kee"));
        ob->set("eff_sen", (int)ob->query("max_sen"));  
        message_vision("一柱香的工夫过去了，你觉得伤势已经基本痊愈了。\n",ob);
        command("say 江湖险恶,不小心的话，下次你就没这么幸运了。\n");
        command("pat"+ob->query("id"));
        return 1;
}

void init()
{
        object ob;

       ::init();
        add_action("do_vendor_list", "list");

}

void accept_kill(object me)
{       object ob;
        if(is_fighting()) return;
        if( query("called") ) return;

        command("help!");

        ob=present("xunluo guanbing");
        if( !ob) {
                seteuid(getuid());
                ob=new("/d/city/npc/xunluobing");
                ob->move(environment());
        }
        message_vision("\n忽然从门外冲进来个巡逻官兵，对$N大喊一声“干什么？想杀人谋财么！\n\n",me);        

        ob->kill_ob(me);
        ob->set_leader(me);
        me->fight_ob(ob);
        set("called", 1);
        call_out("regenerate", 300);
}
int regenerate()
{
        set("called", 0);
        return 1;
}

