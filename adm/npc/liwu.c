// liwu.c

inherit NPC;
#include <ansi.h>

#include "2002.h"
int give_newbie();
int give_family();
int give_bag();
int give_book();
int answer_me();
int give_saozhou ();
void create()
{
    set_name("小小财神", ({"xiao caishen","caishen"}));
    set ("long", @LONG
他是在这里负责给新手做指引的，大家可以向他要(saozhou)
来打工，开始自己的三界神话历程(ask caishen about 扫大街)
LONG);
    set("gender", "男性");
    set("title",HIW"三界神话"HIG"「嘉峪关」"HIC"魔导师"NOR);
    set("age", 20);
    set("max_kee", 10000);
    set("kee", 10000);
    set("per", 40);
    set("attitude", "peaceful");
    set("inquiry", ([ //
        "bonnet"   : "这里有“金丝禅衣”，那个更好，我的天师法冠过时了，哎！",
       "newbie"    :(:give_newbie:),
         "gift"    :(:give_newbie:),
         "礼物"    :(:give_newbie:),
       "family"    :(:give_family:),
       "新手礼物"  :(:give_newbie:),
       "门派礼物"  :(:give_family:),
        "百宝袋"   : (: give_bag :),
        "魔法书"   : (: give_book :),
        "name"     : (: answer_me :),
        "扫大街"   : (: give_saozhou :),
    ]));

    setup();
    carry_object("/d/lingtai/obj/faguan")->wear();
}

int answer_me()
{
    command("say 小心我扁你！嘿嘿 。\n");
    return 1;
}


int give_newbie()
{
        object who=this_player();
        if (!userp(who)){
                command("heng");
                command("say 什么小猫小狗也来要礼物？！");
                command("qi");
                return 1;
        }

         if (who->query("combat_exp") > 410000 ){
                command("hammer "+who->query("id") );
                command("say 你都这么厉害了还差这么一点小东西么？");
                return 1;
         }


         if (this_player()->query("lll/gai") == "got" ){
         message_vision("$N对着$n哼了一声。\n",this_object(),this_player());
                command("say 新人礼物只有一份！领过就不给了！\n");
        return 1;
        }

        who->add("combat_exp",80000);
        who->add("daoxing",80000);
        who->add("force",800);
        who->add("mana",800);
        who->add("maximum_force",1000);
        who->add("max_mana",1000);
        who->add("max_force",1000);
        who->add("maximum_mana",1000);
        who->add("mud_age",86400);

        who->add("potential",80000);
        who->set("lll/gai","got");
message_vision("$N对着$n神秘的笑了笑，$n觉得身体发生剧烈的变化，顿时晕倒在地。\n",this_object(),this_player());
        command("tell "+who->query("id")+"
        你的道行增加了八十年!\n
        你的潜能增加了80000。\n
        您现在有1000点内力和1000点法力，您可以在Enable没有超过上述两值的情况下不用打坐明思\n");
        command("chat 恭喜恭喜，"+who->query("name")+"得到了新人礼物！");
        return 1;
}
int give_family()
{
        object who=this_player();
        string family;
        family=who->query("family/family_name");
        if (!userp(who))
        {
                command("heng");
                command("say 什么小猫小狗也来要礼物？！");
                command("qi");
                return 1;
        }
         if (who->query("combat_exp") < 0 ){
                command("addoil "+who->query("id") );
                command("say 现在拿礼物要求有诚心，你看看够不够武学5000,够了再来找我！？");
                return 1;
         }
        if (this_player()->query("lll/skills") == "got" ){
         message_vision("$N对着$n哼了一声。\n",this_object(),this_player());
                command("say 门派礼物只有一份！领过就不给了！\n");
        return 1;
        }
        if (who->query("combat_exp") > 700000 ) {
                        command("hammer "+who->query("id") );
                command("say 你都这么厉害了还差这么一点小东西么？");
                return 1;
         }
        if ( family == 0 )
        {
                command("heng");
                command("say "+who->query("name")+"你还是先去拜师吧，拜师之前你可以用\nhelp menpai来看《三界神话》的各个门派介绍。\n");
                return 1;
        }
        switch(family) {
                case "方寸山三星洞":
                
                who->set_skill("force",50);
                who->set_skill("dodge",50);
                who->set_skill("spells",50);
                who->set_skill("literate",50);
                who->set_skill("parry",50);
                who->set_skill("liangyi-sword",50);
                who->set_skill("stick",50);
                who->set_skill("dao",50);
                who->set_skill("puti-zhi",50);
                who->set_skill("qianjun-bang",50);
                who->set_skill("wuxiangforce",50);
                who->set_skill("unarmed",50);
                who->set_skill("jindouyun",50);
                who->set_skill("sword",50);
                break;
                                case "轩辕古墓":
                who->set_skill("force",50);
                who->set_skill("jiuyin-force",50);
                who->set_skill("sword",50);
                who->set_skill("qinghu-jian",50);
                who->set_skill("blade",50);
                who->set_skill("zizhi-blade",50);
                who->set_skill("parry",50);
                who->set_skill("dodge",50);
                who->set_skill("mace",50);
                who->set_skill("jiuyin-zhua",50);
                who->set_skill("youming-spells",50);
                who->set_skill("unarmed",50);
                who->set_skill("spells",50);
                who->set_skill("kongming-steps",50);
                who->set_skill("literate",50);
                break;
                                case "大雪山":
                
                who->set_skill("literate",50);
                who->set_skill("dodge",50);
                who->set_skill("force",50);
                who->set_skill("spells",50);
                who->set_skill("parry",50);
                who->set_skill("ningxie-force",50);
                who->set_skill("dengxian-dafa",50);
                who->set_skill("throwing",50);
                who->set_skill("unarmed",50);
                who->set_skill("xiaoyaoyou",50);
                who->set_skill("blade",50);
                who->set_skill("bingpo-blade",50);
                who->set_skill("cuixin-zhang",50);
                who->set_skill("sword",50);
                who->set_skill("bainiao-jian",50);
                break;
                                case "月宫":
                who->set_skill("force",50);
                who->set_skill("dodge",50);
                who->set_skill("unarmed",50);
                who->set_skill("blade",50);
                who->set_skill("xuanhu-blade",50);
                who->set_skill("baihua-zhang",50);
                who->set_skill("literate",50);
                who->set_skill("parry",50);
                who->set_skill("spells",50);
                who->set_skill("sword",50);
                who->set_skill("snowsword",50);
                who->set_skill("moonshentong",50);
                who->set_skill("moondance",50);
                who->set_skill("moonforce",50);
                who->set_skill("whip",50);
                who->set_skill("jueqingbian",50);
                break;
                               case "三界山":
                               case "天一宫":
                               case "天妖宫":
                               case "天魔宫":
                               case "藏尸地":
                               case "雷刀门":
                who->set_skill("dodge",50);
                who->set_skill("zhaoyangbu",50);
                who->set_skill("sword",50);
                who->set_skill("huxiaojian",50);
                who->set_skill("unarmed",50);
                who->set_skill("huxiaoquan",50);
                who->set_skill("liushenjue",50);
                who->set_skill("stick",50);
                who->set_skill("tianyaofa",50);
                who->set_skill("literate",50);
                who->set_skill("force",50);
                who->set_skill("huntianforce",50);
                who->set_skill("spells",50);
                who->set_skill("tianmogong",50);
                who->set_skill("blade",50);
                who->set_skill("zileidao",50);
                who->set_skill("dodge",50);
                who->set_skill("zhaoyangbu",50);
                who->set_skill("parry",50);
                break;
                                case "东海龙宫":
                who->set_skill("unarmed",50);
                who->set_skill("force",50);
                who->set_skill("dodge",50);
                who->set_skill("parry",50);
                who->set_skill("spells",50);
                who->set_skill("seashentong",50);
                who->set_skill("dragonfight",50);
                who->set_skill("dragonforce",50);
                who->set_skill("dragonstep",50);
                who->set_skill("hammer",50);
                who->set_skill("huntian-hammer",50);
                who->set_skill("literate",50);
                who->set_skill("fork",50);
                who->set_skill("fengbo-cha",50);
                break;
                                case "南海普陀山":
                who->set_skill("force",50);
                who->set_skill("parry",50);
                who->set_skill("dodge",50);
                who->set_skill("unarmed",50);
                who->set_skill("spells",50);
                who->set_skill("staff",50);
                who->set_skill("jienan-zhi",50);
                who->set_skill("lotusforce",50);
                who->set_skill("lotusmove",50);
                who->set_skill("lunhui-zhang",50);
                who->set_skill("buddhism",50);
                who->set_skill("literate",50);
                break;
                                case "盘丝洞":
                who->set_skill("dodge",50);
                who->set_skill("unarmed",50);
                who->set_skill("parry",50);
                who->set_skill("spells",50);
                who->set_skill("force",50);
                who->set_skill("jiuyin-xinjing",50);
                who->set_skill("lanhua-shou",50);
                who->set_skill("pansi-dafa",50);
                who->set_skill("qingxia-jian",50);
                who->set_skill("sword",50);
                who->set_skill("literate",50);
                who->set_skill("qin",50);
                who->set_skill("sword",50);
                who->set_skill("chixin-jian",50);
                who->set_skill("whip",50);
                who->set_skill("yinsuo-jinling",50);
                who->set_skill("yueying-wubu",50);
                break;
                                case "陷空山无底洞":
                who->set_skill("force",50);
                who->set_skill("spells",50);
                who->set_skill("parry",50);
                who->set_skill("dodge",50);
                who->set_skill("unarmed",50);
                who->set_skill("blade",50);
                who->set_skill("kugu-blade",50);
                who->set_skill("yaofa",50);
                who->set_skill("literate",50);
                who->set_skill("yinfeng-zhua",50);
                who->set_skill("sword",50);
                who->set_skill("qixiu-jian",50);
                who->set_skill("huntian-qigong",50);
                who->set_skill("lingfu-steps",50);
                who->set_skill("sword",50);
                break;
                                case "五庄观":
                who->set_skill("parry",50);
                who->set_skill("dodge",50);
                who->set_skill("unarmed",50);
                who->set_skill("spells",50);
                who->set_skill("force",50);
                who->set_skill("sword",50);
                who->set_skill("literate",50);
                who->set_skill("taiyi",50);
                who->set_skill("zhenyuan-force",50);
                who->set_skill("xiaofeng-sword",50);
                who->set_skill("baguazhen",50);
                who->set_skill("hammer",50);
                who->set_skill("fumo-zhang",50);
                who->set_skill("staff",50);
                who->set_skill("wuxing-quan",50);
                who->set_skill("blade",50);
                who->set_skill("yange-blade",50);
                who->set_skill("sanqing-jian",50);
                break;
                                case "阎罗地府":
                who->set_skill("unarmed",50);
                who->set_skill("force",50);
                who->set_skill("dodge",50);
                who->set_skill("parry",50);
                who->set_skill("spells",50);
                who->set_skill("literate",50);
                who->set_skill("ghost-steps",50);
                who->set_skill("gouhunshu",50);
                who->set_skill("tonsillit",50);
                who->set_skill("whip",50);
                who->set_skill("hellfire-whip",50);
                who->set_skill("sword",50);
                who->set_skill("jinghun-zhang",50);
                who->set_skill("zhuihun-sword",50);
                who->set_skill("stick",50);
                who->set_skill("kusang-bang",50);
                break;
                                case "火云洞":
                who->set_skill("force",50);
                who->set_skill("dodge",50);
                who->set_skill("parry",50);
                who->set_skill("literate",50);
                who->set_skill("spells",50);
                who->set_skill("unarmed",50);
                who->set_skill("dali-bang",50);
                who->set_skill("fork",50);
                who->set_skill("huomoforce",50);
                who->set_skill("moshenbu",50);
                who->set_skill("moyun-shou",50);
                who->set_skill("pingtian-dafa",50);
                who->set_skill("yueya-chan",50);
                who->set_skill("fork",50);
                who->set_skill("huoyun-qiang",50);
                who->set_skill("spear",50);
                who->set_skill("stick",50);
                break;
                                case "蜀山剑派":
                who->set_skill("sword",50);
                who->set_skill("literate",50);
                who->set_skill("dodge",50);
                who->set_skill("force",50);
                who->set_skill("parry",50);
                who->set_skill("spells",50);
                who->set_skill("unarmed",50);
                who->set_skill("hunyuan-zhang",50);
                who->set_skill("whip",50);
                who->set_skill("sevensteps",50);
                who->set_skill("taoism",50);
                who->set_skill("yujianshu",50);
                who->set_skill("zixia-shengong",50);
                break;
                                case "将军府":
                who->set_skill("literate",50);
                who->set_skill("baguazhou",50);
                who->set_skill("force",50);
                who->set_skill("dodge",50);
                who->set_skill("spells",50);
                who->set_skill("parry",50);
                who->set_skill("unarmed",50);
                who->set_skill("archery",50);
                who->set_skill("bawang-qiang",50);
                who->set_skill("changquan",50);
                who->set_skill("lengquan-force",50);
                who->set_skill("mace",50);
                who->set_skill("spear",50);
                who->set_skill("wusi-mace",50);
                who->set_skill("xuanyuan-archery",50);
                who->set_skill("yanxing-steps",50);
                break;
        default:
                command("heng");
                command("say "+who->query("name")+"你还是先去拜师吧，拜师之前你可以用\nhelp menpai来看《三界神话》的各个门派介绍。\n");
                return 1;
}
        who->set("lll/skills","got");
        command("nod "+who->query("id") );
        command("chat "+family+"弟子"+who->query("name")+"得到了门派奖励，希望以后多为本门派争光。");
        return 1;
}

/*
void init()
{
    call_out("greeting", 1, this_player());
    ::init();
}

void greeting(object who) {

if( !who || environment(who) != environment() ) return;
if( who->query("combat_exp") < 600000) {
        tell_object(who,"小小财神悄悄告诉你：可以向我要礼物哦(ask)(l xiao caishen)。\n");
        tell_object(who,"小小财神悄悄告诉你：可以向我要门派礼物哦(ask caishen about family)。\n");
         }
}
*/
int give_bag()
{
    object bag,who;
    who = this_player();

        if (who->query("daoxing") < 500000 && !metep(who))
    {
        command("addoil "+who->query("id") );
                command("say 拿百宝袋需要五百年道行,够了再来找我！");
        return 1;
    }

    if (present("baibao bag",who))
    {
         message_vision("$N对着$n哼了一声。\n",this_object(), who);
         return 1;
    }
    bag =new("/obj/sjsh_bag");
    if (!objectp(bag))
    {
        command("say 百宝袋一时难拿到，等等！");
        return 1;
    }

    bag->set("owner_id", who->query("id"));
    who->start_busy(3);

    if (!who->query("sjsh_bag"))
    {
        who->set("sjsh_bag",1);
        bag->save();
        who->save();
    }
    if (bag->restore())
    {
        bag->save();
        bag->move(who);
        message_vision("$N对着$n神秘的笑了笑。\n$N拿出一个三界神话百宝袋给了$n。\n",
                       this_object(), who);
        return 1;
    } else
    {
        command("say 百宝袋一时难拿到，等等！");
        destruct(bag);
        return 1;
    }
}

int give_book()
{
    object book, who;
    who = this_player();

    if (present("magic book",who))
    {
        message_vision("$N对着$n哼了一声。\n",this_object(),this_player());
        return 1;
    }

    book =new("/obj/book/magic_book");
    if (!book)
    {
         command("say 魔法书一时难拿到，等等！");
         return 1;
    }

    book->set("owner_id",who->query("id"));
    who->start_busy(3);

    book->move(who);
    message_vision("$N对着$n神秘的笑了笑。\n$N拿出一个"+book->name()+"给了$n。\n",
                   this_object(),who);
    return 1;
}

int give_saozhou ()
{
    object ob;
    object who = this_player();

    if (present("sao zhou", who))
    {
        command_function("hmm");
        tell_object(who, CYN"你不是刚拿过吗，想倒卖啊？\n"NOR);
        return 1;
    }
    command_function("nod");
    ob = new("/d/quest/small/saozhou");
    ob->move(who);
    tell_object(who, CYN"小小财神拿出一把大扫帚给你，去扫大街吧！\n"NOR);
    tell_object(who, "你可以用(look saozhou)来获得帮助！\n");
    return 1;
}

