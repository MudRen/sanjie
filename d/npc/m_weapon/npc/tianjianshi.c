// npc: /d/xingxiu/npc/afanti.c
// Jay 3/26/96
// modify by five
#include <ansi.h>
inherit NPC;

int do_weapon();
object creat_weapon();

void create()
{
        set_name("欧冶子", ({ "ouye zi", "zi" }) );
        set("nickname", RED "赤心剑胆" NOR );
          set("title", "兵器大师" );
        set("gender", "男性" );
        set("age", 60);
        set("long",     
            "他头上包着头巾，三缕长髯飘洒胸前，面目清瘦但红晕有光，\n"
            "二目炯炯有神，烁烁闪着竟似是凛凛的剑光，浑身似乎都包围\n"
            "在一股剑气之中。\n");
        set("str", 25);
        set("kar", 17);
        set("int", 30);
        set("daoxing", 3000000);
        set("combat_exp", 5000000);

        set_skill("unarmed", 340);
        set_skill("dodge", 340);
        set_skill("parry", 340);
        set_skill("spells", 340);  
        set_skill("dao", 340);
        set_skill("literate", 340);
        set_skill("stick", 340);  
        set_skill("qianjun-bang", 340);
        set_skill("puti-zhi", 340);  
        set_skill("jindouyun", 340);
        set_skill("dodge", 340);  
        set_skill("force", 340);   
        set_skill("wuxiangforce", 340);

        map_skill("spells", "dao");
        map_skill("unarmed", "puti-zhi");
        map_skill("force", "wuxiangforce");
        map_skill("stick", "qianjun-bang");
        map_skill("parry", "qianjun-bang");
        map_skill("dodge", "jindouyun");


        set("per", 30);
        set("max_kee", 2000);
        set("max_gin", 2000);
        set("max_sen", 2000);
        set("force", 4500);
        set("max_force", 4500);
        set("force_factor", 100);
        set("mana", 4500);
        set("max_mana", 4500);
        set("mana_factor", 100);
        
        set("inquiry", ([
            "铸剑"  : "铸剑可是件十分艰苦的事，要消耗人的精气和内力，你有决心和毅力吗？\n",
            "原料"  : "铸剑可用千年玄铁。。。你找到了我才能帮你铸剑。\n",
       ]) );
            set("no_get",1);
        setup();
        set("chat_chance", 3);
        set("chat_msg", ({
             "欧冶子抚剑而歌：巨阙神兵兮，人铸就。盖世宝剑兮，配英雄！\n",
             "欧冶子低头沉吟，似乎在思考什么。\n"
             "欧冶子叹了一口气：神兵配英雄，可英雄。。。。。。\n"
       }) );
        carry_object("/d/obj/cloth/choupao")->wear();
        carry_object("/d/obj/weapon/stick/bintiegun")->wield();
}

void init()
{
        ::init();
        add_action("do_answer","answer");
}


int accept_object(object who, object ob)
{       
        if(!who->query("bld/done") ){
                say("欧冶子一声叹道：沉香这个小孩真可怜，你能帮帮他吗？\n");
                return 2;
        }
        if((who->query("weapon/make")) ){
                say("欧冶子一脸茫然：您已经有一把自造的武器了，还来干什么？难到不可手么？\n");
       call_out("destrory",0,ob);
                return 2;
        }
        switch ((string)ob->query("name") ) 
        {
                case "千年神木": 
                        who->set_temp("or",1);
                        who->set_temp("get_orc",1);
                        break;
                case "海底金母":
                        who->set_temp("or",2);
                        who->set_temp("get_orc",1);
                        break;
                case "寒丝羽竹": 
                        who->set_temp("or",3);
                        who->set_temp("get_orc",1);
                        break;
                default :
                        message("vision","这是什么！这不能用来打造兵器！",who);
                        return 2;
        }
        message("vision","欧冶子低头检视了一下手中的"+(string)ob->query("name")+
                        "点了点头说：\n",who);

        write("我这儿可以打造以下兵器：\n"+
              "     剑(sword)\n"+
              "     刀(blade)\n"+
              "     棍(stick)\n"+
              "     杖(staff)\n"+
              "     棰(hammer)\n"+
              "     枪(spear)\n"+
              "     锏(mace)\n"+
              "     斧(axe)\n"+
              "     叉(fork)\n"+
              "     鞭(whip)\n");               
        say("这位"+RANK_D->query_respect(who)+"要造什么兵器？决定了告诉我(answer)。\n");
       call_out("destrory",0,ob);
        return 2;

}

int do_answer(string arg)
{
        object me,w_or;
        me = this_player();
        if(!(me->query_temp("get_orc") ) ){
                write("你找到原料了吗？\n");
                return 0;
        }
        
        if(!arg){
           write("你要造什么兵器？\n");
          return 0;
        }
        message("vision",me->name()+"对欧冶子轻声说了几句。\n",environment(me), ({me}) );
        switch (arg) {
          case "sword" :
                me->add_temp("sword",1);
                write("带着原料去找侍剑吧!\n");
                message("vision","去吧！"+me->name()+"!\n",me);
                break;
          case "blade" :
                me->add_temp("blade",1);
                write("带着原料去找侍刀吧!\n");
                message("vision","去吧！"+me->name()+"!\n",me);
                break;
          case "stick" :
                me->add_temp("stick",1);
                write("带着原料去找侍棍吧!\n");
                message("vision","去吧！"+me->name()+"!\n",me);
                break;
          case "staff" :
                me->add_temp("staff",1);
                write("带着原料去找侍杖吧!\n");
                message("vision","去吧！"+me->name()+"!\n",me);
                break;
          case "whip" :
                me->add_temp("whip",1);
                write("带着原料去找侍鞭吧!\n");
                message("vision","去吧！"+me->name()+"!\n",me);
                break;
          case "spear" :
                me->add_temp("spear",1);
                write("带着原料去找侍枪吧!\n");
                message("vision","去吧！"+me->name()+"!\n",me);
                break;
          case "mace" :
                me->add_temp("mace",1);
                write("带着原料去找侍锏吧!\n");
                message("vision","去吧！"+me->name()+"!\n",me);
                break;
          case "axe" :
                me->add_temp("axe",1);
                write("带着原料去找侍斧吧!\n");
                message("vision","去吧！"+me->name()+"!\n",me);
                break;
          case "fork" :
                me->add_temp("fork",1);
                write("带着原料去找侍叉吧!\n");
                message("vision","去吧！"+me->name()+"!\n",me);
                break;
          case "hammer" :
                me->add_temp("hammer",1);
                write("带着原料去找侍锤吧!\n");
                message("vision","去吧！"+me->name()+"!\n",me);
                break;

          default :
                message_vision(HIC "欧冶子一脸狐疑：什么兵器？\n" NOR,me);
                return notify_fail("欧冶子仔细的说：此事不可儿戏，请慎重!!\n");
        }
        switch ( me->query_temp("or") ) {
          case 1:
                w_or = new("/m_weapon/tan/item/shenmu",1);
                w_or->move(me);
                message_vision(HIC "欧冶子给了$N一块千年神木\n" NOR, me);
                break;
          case 2:
                w_or = new("/m_weapon/tan/item/jinmu",1);
                w_or->move(me);
                message_vision(HIC "欧冶子给了$N一块海底金母\n" NOR, me);
                break;
          case 3:
                w_or = new("/m_weapon/tan/item/hanzhu",1);
                w_or->move(me);
                message_vision(HIC "欧冶子给了$N一块寒丝羽竹\n" NOR, me);
                break;
        }
        me->delete_temp("or");
        return 1;
}
void destrory(object ob)
{
      destruct(ob);
     return;
}
