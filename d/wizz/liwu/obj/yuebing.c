#include <ansi.h> 
#include <localtime.h> 
#define REMON 8  // 月份，实际月份等于这个数字加1 
#define REDAY 15 // 日期 从20到24为止 
#define REEXP 120000 // 获得一般奖励最小需要的exp 
inherit ITEM; 

string *GetName = ({ 
        "豆沙月饼", 
        "莲蓉月饼", 
        "椰蓉月饼", 
        "火腿月饼", 
        "芝麻月饼", 
        "桂花月饼", 
        "素月饼", 
        "冰皮月饼", 
        "果蔬月饼", 
        "海味月饼", 
        "蛋黄月饼", 
        "椰奶月饼", 
        "甜玉米月饼", 
        "改良月饼", 
        "五仁月饼", 
        "枣泥月饼", 
        "百果月饼",
        "水果月饼",
}); 

varargs string GetColor(int flag) 
{ 
        string color; 
        if (flag) 
                color = COLOR_D->random_color(4); 
        else { 
                if (random(2)) 
                        color = COLOR_D->random_color(4); 
                else 
                        color = COLOR_D->random_color(3); 
        } 
        return color; 
} 

string SetName() 
{ 
        int i = random(sizeof(GetName)); 
        return (GetColor() + GetName[i] + NOR); 
} 


void create() 
{ 
        string myName; 
        myName=SetName(); 
        set_name( myName, ({ "cake"}) ); 
        set("long","一个小小的" + myName + "，香喷喷的，刚出炉，还是热的呢！\n"+
                   "命令格式eat cake (0-4)。\n"
                   "0：道行奖励 1：潜能奖励 2：武学奖励 3：宝石奖励  4：黄金奖励！");
 
        set_weight(50); // 一两 
        if( clonep() )  
                set_default_object(__FILE__); 
        else { 
                set("unit", "个"); 
                set("value", 5000); // 50 silver one 
                set("no_sell","穷到这份上了？月饼也要卖？\n"); 
                set("no_get","捡月饼吃？\n"); 
                set("no_put","想收藏啊？\n"); 
                set("no_drop","嘿嘿......！\n"); 
                set("no_give","自己留着吧！\n"); 
        } 
        set("is_monitored",1); 
        setup(); 
}

void init()
{
    if (!wizardp(this_player())) {
        set("no_get"," 嘿嘿，做梦吧! \n");
        set("no_drop","这么宝贵的东东，哪能乱扔! \n");
        set("no_give","你太慷慨了吧！\n");
        set("no_put","你别做梦了！\n");
        set("no_sell","这么宝贵的东西，哪里可以买卖的！\n");
       }
        add_action("do_eat", "eat");
       

}

int do_eat(string arg)

{
        object me,newob;
        int exper,dx,tt1,tt2,qn,i,improve=0;

        me = this_player();


        if (!arg)
        return notify_fail("你要吃什么？\n");

        if ( this_object()->query("owner") != me->query("id"))
        {
           message_vision(HIR"\n偷吃月饼，打入天牢。\n"NOR,me);
           me->move("/d/wiz/jail");
           return 1;
        }
      
        
       switch(arg){
        case "cake 0":
               dx= me->query("daoxing");
               tt2= dx/60+random(dx/100)+300;
               if(tt2 > 100000) tt2=100000;
               message_vision(HIY"$n对$N道，恭喜恭喜，你拿到中秋礼物了。\n"NOR,me,this_object());
               me->set("daoxing",dx + tt2);
               message_vision(HIY+me->name()+"的道行大增"+tt2+"点。　\n"NOR,me);
               break;
        case "cake 1":
               qn= me->query("potential");
               if( (int)me->query("potential") > (int)me->query("learned_points"))
                        qn=(int)me->query("potential")-(int)me->query("learned_points");
               tt1= qn/60+random(qn/100)+60;
               me->add("potential",tt1);
               message_vision(HIY"$n对$N道，恭喜恭喜，你拿到中秋礼物了。\n"NOR,me,this_object());
               message_vision(HIY+me->name()+"的潜能大增"+tt1+"点。　\n"NOR,me);
               break;
       case "cake 2":
               exper = me->query("combat_exp");
               improve=exper/50+random(exper/30)+3000;
               if(improve > 100000) improve=100000;
               message_vision(HIY"$n对$N道，恭喜恭喜，你拿到中秋礼物了。\n"NOR,me,this_object());
               me->set("combat_exp",exper+improve);
               message_vision(HIY+me->name()+"的武学增加"+improve+"点。　\n"NOR,me);
               break;
        case "cake 3":
                for(i=0;i<3;i++)
                {
                        
                newob=new("/d/quest/baoshi/baoshi");
                newob->move(me);
                }
                message_vision(HIY"$n对$N道，恭喜恭喜，你拿到中秋礼物了。\n"NOR,me,this_object());
                message_vision(HIY+me->name()+"等到若干个宝石！。　\n"NOR,me);
                break;
        case "cake 4":
                newob=new("/obj/money/gold");
                improve=(me->query("daoxing"))/10000+1;
                if(improve > 518) improve=518;
                newob->set_amount(improve);
                newob->move(me);
                message_vision(HIY"$n对$N道，恭喜恭喜，你拿到中秋礼物了。\n"NOR,me,this_object());
                message_vision(HIY+me->name()+"等到"+improve+"两黄金！。　\n"NOR,me);
                break;
       default :
                tell_object(me,"命令格式eat cake (0-4)。\n");
                return 1;
        }               
        if( random(400) < 2)
          {
           message_vision(HIY"恭喜发财,"+me->name()+"中了头奖。　\n"NOR,me);
/*
           switch(random(5)){
              case 0:
              me->add("str",1);
              message_vision(HIY+me->name()+"的体格大增一点。　\n"NOR,me);
              me->add("cor",1);
              message_vision(HIY+me->name()+"的胆识又增加了一点。\n"NOR,me);
              break;
              case 1:
              me->add("per",1);
              message_vision(HIY+me->name()+"的容貌又漂亮了一点。\n"NOR,me);
              me->add("cor",1);
              message_vision(HIY+me->name()+"的胆识又增加了一点。\n"NOR,me);
              break;
              case 2:
              me->add("cor",1);
              message_vision(HIY+me->name()+"的胆识又增加了一点。\n"NOR,me);
              me->add("cps",1);
              message_vision(HIY+me->name()+"的定力又增加了一点。\n"NOR,me);
              break;
              case 3:
              me->add("cps",1);
              message_vision(HIY+me->name()+"的定力又增加了一点。\n"NOR,me);
              me->add("str",1);
              message_vision(HIY+me->name()+"的体格大增一点。　\n"NOR,me);
              break;
              case 4:
              me->add("cps",1);
              message_vision(HIY+me->name()+"的定力又增加了一点。\n"NOR,me);
              me->add("per",1);
              message_vision(HIY+me->name()+"的容貌又漂亮了一点。\n"NOR,me);
              break;
                }
*/
                me->add("balance",30000000);
                message_vision(HIY+me->name()+"的存款增加了3000两黄金。\n"NOR,me);
             }
       else {
             message_vision(HIY"恭喜发财,"+me->name()+"没有中头奖,可惜呀,下次再来吧。　\n"NOR,me);

           }
        destruct(this_object());
        return 1;


}


