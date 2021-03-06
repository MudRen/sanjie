// CMDS /cmds/std/score.c
// Created by waiwai@2000/12/21
// Update by waiwai@2001/07/07
// update by koker@2003/07/22
// 人物出生地(目前主要配合买卖，因此设置的主要是店铺多一点的国家)
// string *changed = ({ 
// "长安", "开封", "宝象", "祭赛", "江州", "乌鸡", "车迟", 
// "朱紫", "比丘", "钦法", "凤仙", "玉华", "天竺", "灵山"
// });
// Last modified by waiwai@2003/01/16
// 为魂魄精灵做必要设置修改

#include <ansi.h>
#include <login.h>
#include <combat.h>
#include <mudlib.h>
#include <command.h>
inherit F_CLEAN_UP;

string query_time(int time);
string display_attr(int gift, int value);
string status_color(int current, int max);
string date_string(int date);
string tribar_graph(int val, int eff, int max, string bcolor, string fcolor, string dcolor);
string transfer_string(string str, int length);

void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
        object ob, killer, area, mastername, sexname, npcsx;
        mapping my, quest;
        string line, temp, str, skill_type, *marks, banghui, last_fainted_from;
        object weapon;
        int i, age, attack_points, dodge_points, parry_points, quest1;
        int obstacles, office, dntg;  
        string msg, race, player, sx;
        mixed dir, file;

       seteuid(getuid(me));

        if(!arg ) ob = me;
        else if (wizardp(me) ) {
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("你要察看谁的个人档案情况？\n");
        } else if( stringp(banghui=me->query("banghui"))) {
                ob =present(arg,environment(me));
                if(!ob || !ob->is_character())
                        return notify_fail("你要察看谁的个人档案情况？\n");
                if((string)ob->query("banghui")!=banghui)
                        return notify_fail("你只能查看本帮会帮众的个人档案情况。\n");
                } else
                return notify_fail("只有巫师或同帮会的人才能察看别人的个人档案情况。\n");

                // Added by waiwai@2002/01/16
                if( wiz_level(me) < wiz_level(ob) )
                        return notify_fail("你要察看谁的个人档案情况？\n");

        my = ob->query_entire_dbase();

        write(NOR YEL"≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡"HIG"个"NOR YEL"≡≡≡"HIG"人"NOR YEL"≡≡≡"HIG
"档"NOR YEL"≡≡≡"HIG"案"NOR YEL"≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n"NOR);
        write("你现在的头衔 : "+RANK_D->query_rank(ob)+"\n");
        write("你现在的职称 : "+ob->short(1)+"\n");
        line = NOR YEL"≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n"NOR;
        str = "";

        if( mapp(my["family"]) ) {
                if( my["family"]["master_name"] ) 
                str =my["family"]["family_name"]+WHT+my["family"]["master_name"];
        }

        if( mapp(my["marks"]) ) {
                marks = keys( my["marks"] );
                for( i = 0; i < sizeof(marks); i ++ ) {
                        if( str != "" ) str += "、";
                        str += marks[i];
                }
        }

        line += sprintf( " 年龄：[%4d]      生日：[%-24s]\n",
                 ob->query("age"), XYJTIME_D->check_usr_birthday(ob) ); 

        line += sprintf( " 性别：[%-4s]      体重：[%-14s] 帮会：[%-8s]",
                 ob->query("gender"), chinese_number((int)ob->query_weight()/1300)+"公斤",
                 ob->query("club")?ob->query("club"):"未入帮会" );

        // Added By waiwai@2001/05/01
        if( (int)ob->query("impurity")>(int)ob->query("Fimpurity") ) 
                ob->set("Fimpurity",ob->query("impurity")); 

// Added By kuku@2003/09/06 
        if( ob->query("impurity")>0 && ob->query("impurity")<=100 ) 
                line += "   善恶：[小偷小摸]\n"; 
        else if(ob->query("impurity")>100 && ob->query("impurity")<=200 ) 
                line += "   善恶：[死不悔改]\n"; 
        else if(ob->query("impurity")>200 && ob->query("impurity")<=300 ) 
                line += "   善恶：[杀人如麻]\n"; 
        else if(ob->query("impurity")>300 && ob->query("impurity")<=400 ) 
                line += "   善恶：[千夫所指]\n"; 
        else if(ob->query("impurity")>400 && ob->query("impurity")<=500 ) 
                line += "   善恶：[茹毛饮血]\n"; 
        else if(ob->query("impurity")>500 && ob->query("impurity")<=600 ) 
                line += "   善恶：[穷凶极恶]\n"; 
        else if(ob->query("impurity")>600 && ob->query("impurity")<=700 ) 
                line += "   善恶：[恶贯满盈]\n"; 
        else if(ob->query("impurity")>700 && ob->query("impurity")<=800 ) 
                line += "   善恶：[罪大恶极]\n"; 
        else if(ob->query("impurity")<0 && ob->query("impurity")>=-100 ) 
                line += "   善恶：[好人好报]\n"; 
        else if(ob->query("impurity")<-100 && ob->query("impurity")>=-250 ) 
                line += "   善恶：[一心向善]\n"; 
        else if(ob->query("impurity")<-250 && ob->query("impurity")>=-625 ) 
                line += "   善恶：[心存善念]\n"; 
        else if(ob->query("impurity")<-625 && ob->query("impurity")>=-1562 ) 
                line += "   善恶：[从善如流]\n"; 
        else if(ob->query("impurity")<-1562 && ob->query("impurity")>=-3905 ) 
                line += "   善恶：[爱憎分明]\n"; 
        else if(ob->query("impurity")<-3905 && ob->query("impurity")>=-9762 ) 
                line += "   善恶：[疾恶如仇]\n"; 
        else if(ob->query("impurity")<-9762 && ob->query("impurity")>=-24405 ) 
                line += "   善恶：[爱思泉涌]\n"; 
        else if(ob->query("impurity")<-24405 && ob->query("impurity")>=-61012 ) 
                line += "   善恶：[大慈大悲]\n"; 
        else 
                line += "   善恶：[ 心平气和 ]\n"; 

        /*******************************************************************************/             
         // Added By waiwai@2001/05/01
        if(ob->query("zhongzu")){
              if(ob->query("zhongzu")=="god")
                      line +=" 种族：[神族"NOR"]";
              if(ob->query("zhongzu")=="man")
                      line +=" 种族：[人族"NOR"]";
              if(ob->query("zhongzu")=="ghost")
                      line +=" 种族：[魔族"NOR"]";
        }else line+=" 种族：[不明"NOR"]";

        line += sprintf( "      职业：[%s%-6s%s]   ",
        HIC, ob->query("occupation")?ob->query("occupation"):"没有注册", NOR );
        if( ob->query("club") )
         line += sprintf("    帮职：[%-8s]", 
                ob->query("bh_rank")?ob->query("bh_rank"):"普通帮众");
         else
         line+= "    帮职：[未入帮会]"NOR;
        /*******************************************************************************/

        // Addded By waiwai@2001/07/07 增加阳寿信息参数设置
        age = (int)ob->query("life/life_time");
        age -= (int)ob->query_age() / 86400;
        msg = sprintf("[%-6s年]", chinese_number(age) );
        if( userp(ob) ) {
        if( !ob->query("life/live_forever_announced") && !ob->query("life/live_forever") ) {
        if(wizardp(me) ||
                RANK_D->grade_dx(RANK_D->describe_dx(ob->query("daoxing")))>=
                RANK_D->grade_dx(HIY"脱胎换骨"NOR)) {
                line+= "  阳寿："+msg+"\n";}
         else
         line+= "  阳寿：[暂时隐藏]\n"NOR;
         } else  line+= "   阳寿：["RED"不生不灭"NOR"]\n"NOR;
        } else  
        if( !userp(ob) ) { // 魂魄精灵所需
        if(!age)
        line+= "  阳寿：["RED"不生不灭"NOR"]\n"NOR;
        else
        line+= "  阳寿：["RED"+msg+"NOR"]\n"NOR;
        }

        /*******************************************************************************/
        // Addded By waiwai@2001/05/28
        if (ob->query("married")) { 
         if (ob->query("gender")=="女性") {
              line += sprintf(" 丈夫：[%-8s]", ob->query("couple/name"));
           } else {
              if ((int)me->query("married")<=1) {
            line += sprintf(" 妻子：[%-8s]", ob->query("couple/name"));
                  } else {
        if( ob->query("couple/name") && ob->query("couple2/name"))
         line += sprintf(" 发妻：[%-8s] 小妾[%-8s] ", 
        ob->query("couple/name"),ob->query("couple2/name"));
        else
        if( ob->query("couple/name") && !ob->query("couple2/name"))
         line += sprintf(" 发妻：[%-8s] 小妾[ 不 明 ] ", 
        ob->query("couple/name"));
        else
        if( ob->query("couple2/name") && !ob->query("couple/name"))
         line += sprintf(" 发妻：[ 不 明 ] 小妾[%-8s] ", 
        ob->query("couple/name"));
              }
        }
        } else {
           if (!ob->query("unmarryed"))
          line += " 婚姻: [未婚]    ";
              else line += " 婚姻: ["RED"离异"NOR"]    ";
        }

           //Added By waiwai@2001/05/01
//          sexname=ob->query("couple/id");
         if ( !ob->query("sex/times") && !ob->query("sex/times2") ) {
         if (ob->query("gender")=="女性") line += sprintf("  状态：[ 处  女 ]");
           else line += sprintf("  状态：[ 童  男 ]");
           }  else
         if ( ob->query("sex/times") && ob->query("sex/times2") ) {
//              if( ob->query("sex/firstid") == sexname )
                line += sprintf("  状态：["HIG"%-8s"NOR"]",ob->query("sex/first") );
           } else
        if ( !ob->query("sex/times") &&  ob->query("sex/times2") ) 
                line += sprintf("  状态：["HIG"%-8s"NOR"]",ob->query("sex/first") );
           else 
        if ( ob->query("sex/times") &&  !ob->query("sex/times2") ) 
                line += sprintf("  状态：[%-8s]",ob->query("sex/first") );
           else line += "  状态: [ 不  明 ]";
        mastername= ob->query("family/master_name");
        line += sprintf( "       婚次：[ %-2d/ %2d ]   祖籍：[%s人士]\n",
         ob->query("marryed"),ob->query("unmarryed"),ob->query("changed")?ob->query("changed"):WHT"不明"NOR); 
        line += sprintf( " 官职：[%-5d]  官拜：[%s]",
         ob->query("office_number"), ob->query("degree")?ob->query("degree"):"未入仕途");
        if( userp(me) && userp(ob) ) {
        if( !(string)me->query("Pfamily") ) {
        if ( mastername )
        line += sprintf( "       师承：[%-8s]\n\n ",filter_color(mastername));
              else
        line += sprintf( "       师承：[未入师门]\n\n ");
        } else
        line += sprintf( "       师承：["HIR+(string)me->query("Pfamily")+"弃徒"NOR"] \n\n");
        } else { // 魂魄精灵所需
        if( ob->query("family/family_name") )
        line += sprintf( "       师承：[%-8s]\n\n ",ob->query("family/family_name") );
        else
        line += sprintf( "       师承：[无门无派]\n\n ");
        }


        /*******************************************************************************/

        line += sprintf( "力量：[%2d/%4s %s]",
                 my["str"], display_attr(my["str"], ob->query_str()), NOR );

        if( my["eff_sen"] <my["max_sen"] ) str = HIR+"生病";
        else if( my["sen"]*100 / my["max_sen"]>=70 ) str = HIG + "饱满";
        else if( my["sen"]*100 / my["max_sen"]>=40 ) str = HIR + "疲倦";
        else str = HIB + "很累";
        line += " ·精神状态·" + tribar_graph(my["sen"], my["eff_sen"], my["max_sen"], NOR, HIR ,HIW)
                + sprintf( "  [%4s%s]  \n", str,NOR);

        line += sprintf( " 根骨：[%2d/%4s %s]", 
                my["con"], display_attr(my["con"], ob->query_con()), NOR );

        if( my["eff_kee"] <my["max_kee"] ) str = HIR+"受伤";
        else if( my["kee"]*100 / my["max_kee"]>=70 ) str = HIG + "充沛";
        else if( my["kee"]*100 / my["max_kee"]>=40 ) str = HIR + "伤残";
        else str = HIB + "重伤";
        line += " ·气血状态·" + tribar_graph(my["kee"], my["eff_kee"], my["max_kee"],NOR, HIR ,HIW)
                + sprintf( "  [%4s%s]\n",str,NOR);

        if( my["food"] * 100 / ob->max_food_capacity() > 100 ) str = HIY+"辟谷";
        else if( my["food"] * 100 / ob->max_food_capacity() >= 90 ) str = HIC+"很饱";
        else if( my["food"] * 100 / ob->max_food_capacity() >= 50 ) str = HIC+"正常";
        else if( my["food"] * 100 / ob->max_food_capacity() >= 20 ) str = HIR+"缺食";
        else str = HIB + "饥饿";
        
        line += sprintf( " 悟性：[%2d/%4s %s]",
                 my["int"], display_attr(my["int"], ob->query_int()), NOR );

        line += " ·食物状态·" + tribar_graph(my["food"], ob->max_food_capacity(),
                ob->max_food_capacity(), NOR, HIC ,HIR)
                + sprintf( "  [%4s%s]\n", str, NOR );

        line += sprintf( " 灵性：[%2d/%4s %s]",
                my["spi"], display_attr(my["spi"], ob->query_spi()), NOR );

        if( my["water"] * 100 / ob->max_water_capacity() > 100 ) str = HIY + "辟谷";
        else if( my["water"] * 100 / ob->max_water_capacity() > 50 ) str = HIC + "正常";
        else if( my["water"] * 100 / ob->max_water_capacity() > 30 ) str = HIR + "缺水";
        else str = HIB + "饥渴";

        line += " ·饮水状态·" + tribar_graph(my["water"], ob->max_water_capacity(),
                ob->max_water_capacity(), NOR, HIC ,HIR)
                + sprintf( "  [%4s%s]\n",  str, NOR );

        if(wizardp(me) ||
                RANK_D->grade_dx(RANK_D->describe_dx(ob->query("daoxing")))>=
                RANK_D->grade_dx(HIY"脱胎换骨"NOR)) {
        line += sprintf( " 容貌：[%2d/%4s %s]", my["per"], display_attr(my["per"], ob->query_per()), NOR );
         } else
        line+=" 容貌：[ 隐藏 ]  ";
        /*******************************************************************************/

        if(ob->query("namecolor")){
                line += " ·拼杀记录·" 
                + sprintf( "杀害玩家：普[%d]黄[%d] 总[%d/%d]"NOR" 位,杀死敌人：%d 位\n",  
                (int)ob->query("color_pk/common"), (int)ob->query("color_pk/yellow"), 
                (int)ob->query("color_pk/total"), my["PKS"],my["MKS"]);
        }
        else{
                line += " ·拼杀记录·" 
                + sprintf( "杀害玩家：普[0]黄[0] 总[%d/%d]"NOR" 位,杀死敌人：%d 位\n",  
                (int)ob->query("color_pk/total"), my["PKS"],my["MKS"]);
        }

        if(wizardp(me) ||
                RANK_D->grade_dx(RANK_D->describe_dx(ob->query("daoxing")))>=
                RANK_D->grade_dx(HIY"脱胎换骨"NOR)) {
        line += sprintf( " 福缘：[%2d/%4s %s]",
                my["kar"], display_attr(my["kar"], ob->query_kar()), NOR );
         } else
        line+=" 福缘：[ 隐藏 ]  ";

        line += " ·阵亡记录·" 
                + sprintf( "正常阵亡：%s%d%s 次,离奇阵亡：%s%d%s 次\n",  YEL, my["dietimes"], NOR,
                YEL, my["normal_die"], NOR);

        if(wizardp(me) ||
                RANK_D->grade_dx(RANK_D->describe_dx(ob->query("daoxing")))>=
                RANK_D->grade_dx(HIY"脱胎换骨"NOR)) {
        line += sprintf( " 定力：[%2d/%4s %s]",
                my["cps"], display_attr(my["cps"], ob->query_cps()), NOR );
         } else
        line+=" 定力：[ 隐藏 ]  ";

        attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK); 
        parry_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_DEFENSE); 
        dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE); 

        // 加入可以借款，所以更改原设置
        if( (int)ob->query("balance")>0 )
        line+= " ·钱庄存款·"+"/adm/daemons/moneyd.c"->money_str((int)ob->query("balance"))+"\n\n";
        else
        if( (int)ob->query("balance")<0 ) 
        line+= RED" ·钱庄欠款·"+MONEY_D->money_str((-(int)ob->query("balance")))+"\n\n"NOR;
        else
        line+= " ·钱庄存款·目前是个穷鬼\n\n";
        /*******************************************************************************/
        if(wizardp(this_player())) 
        line += sprintf("\n 战斗攻击力 " HIW "%d (+%d)" NOR "\t\t战斗防御力 " HIW "%d (+%d)\n\n" NOR,
        attack_points/100 + 1, ob->query_temp("apply/damage"),
                (dodge_points + (weapon? parry_points: 
                (parry_points/10)))/100 + 1, ob->query_temp("apply/armor"));
        else line+=sprintf(" 兵器伤害力： ["HIR"%d"NOR"]" NOR "\t\t盔甲保护力： ["HIG"%d"NOR"]\n\n" NOR,
        ob->query_temp("apply/damage"),
        ob->query_temp("apply/armor"));
        /*******************************************************************************/
        if(ob->query("quest/number"))
        line+= "〖"HIG"解  迷"NOR"〗：你已经解了"HIR+chinese_number(ob->query("quest/number"))+NOR"个迷\n";
        else line+="〖"HIG"解  迷"NOR"〗："+HIR"你还没有解迷"NOR+"\n";
        obstacles = ob->query("obstacle/number");
        if(obstacles)
        line += sprintf(RED" 西天取经"NOR"：你已经历了"RED"%s"NOR"道劫难。\n", chinese_number(obstacles));
        else line += RED" 西天取经"NOR"：你还未曾踏上取经之路\n";
        dntg = ob->query("dntg/number");
        if (dntg == 0) line += " "RED"大闹天宫"NOR"：你还未曾大闹天宫\n";
        else line+= RED" 大闹天宫"NOR"：你大闹天宫已过"HIR+chinese_number(dntg)+NOR"关。\n";
        if (ob->query("die_reason"))  
        line +=sprintf(RED" 上次遇害"NOR"：%s\n\n", ob->query("die_reason")); 

        /*******************************************************************************/        
        if(ob->query("BHPJ")<0) ob->set("BHPJ",0);

        line += sprintf(" 门派罪孽度： "YEL"%5d   " NOR "     帮会忠诚度： "YEL"%4d / %4d"NOR"        帮会评价值： "YEL"%5d \n"NOR,
        ob->query("MP_killM"), ob->query("zhongcheng"), ob->query("max_zhongcheng"), ob->query("BHPJ"));

        line += sprintf(" 门派忠诚度： "YEL"%5d   " NOR "     可分配点数： "YEL"%4d / %4d"NOR"        潜能储存数： "YEL"%5d \n\n"NOR,
           (int)ob->query("faith"), ob->query("gift_points"), 
        ob->query("used_gift_points"), (int)ob->query("qn_balance"));

        /*******************************************************************************/
        //Added By waiwai@2001/05/01
        if( !ob->query("killtocity"))  ob->set("killtocity","不明区域");

        if( ob->query("killtoname") && ob->query("killtoid") )
        line+=sprintf(" 上次杀戮：[%s] 将"YEL"%s(%s)"NOR"杀死在%s \n",
                ob->query("killtotime"), ob->query("killtoname"),
                ob->query("killtoid"), ob->query("killtocity"));
              else
        if( !ob->query("killtoname")) line+= "\n";

        //Added By waiwai@2001/05/01
        if( !ob->query("killbycity"))  ob->set("killbycity","不明区域");

        if( ob->query("killbyname") && ob->query("killbytime") && ob->query("killbyname")!="死因不明"){
        line+=sprintf(" 上次死因：[%s] 被"YEL"%s(%s)"RED"%s"NOR"而死在%s\n",
                ob->query("killbytime"), ob->query("killbyname"),ob->query("killbyid"),
                ob->query("killbyB")?ob->query("killbyB"):"", ob->query("killbycity"));
              } else
        if( ob->query("killbyname") && ob->query("killbyname")!="死因不明"){
                line+= " 上次死因：因"YEL+ob->query("killbyname")+"("+ob->query("killbyid")+")"RED+
(ob->query("killbyB")?ob->query("killbyB"):"")+NOR"而死在"+ob->query("killbycity")+" 时间不明 \n";
          }
        if( ob->query("killbyname") && ob->query("killbytime") && ob->query("killbyname")=="死因不明"){
        line+=sprintf(" 上次死因： [%s] 死因不明 而死在%s\n",ob->query("killbytime"),  ob->query("killbycity"));
              } else
        if( ob->query("killbyname") && ob->query("killbyname")=="死因不明"){
                 line+= "上次死因："YEL"死因不明 时间不明 "NOR"在"+ob->query("killbycity")+"\n"NOR;
          } 

        if( !ob->query("killbyname")) line+= "\n";
        /*******************************************************************************/

        if(ob->query("kill/pkgain") ) { 
                line +=sprintf(NOR" ＰＫ道行：%s  \n", XYJTIME_D->check_daoxing(ob->query("kill/pkgain")));
                if(!ob->query("kill/pklose") && !ob->query("kill/nkgain") ) line+="\n";
        }

        if(ob->query("kill/nkgain") ) 
                line +=sprintf(NOR" ＮＫ道行：%s\n\n", XYJTIME_D->check_daoxing(ob->query("kill/nkgain")));
        else   line +="\n";
        /*******************************************************************************/

        line += sprintf(" 道行境界：%s 武学境界：%s 法力修为：%s 内力修为：%s\n",
                 RANK_D->describe_dx(ob->query("daoxing")),  RANK_D->describe_exp(ob->query("combat_exp")), 
                 RANK_D->describe_fali(ob->query("max_mana")),RANK_D->describe_neili(ob->query("max_force")));

        line += YEL"≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡ "HIG+INTERMUD_NAME+NOR+YEL" ≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n"NOR;
        if( userp(me) && userp(ob) ) {
        line += sprintf("在三界神话%s已经历了 "YEL"%s"NOR" 的岁月 "NOR,
        ob==me?"你":ob->name(1),FINGER_D->age_string( (int)ob->query("mud_age")) );
        line += sprintf("本次上线%s的停留时间为 "YEL"%s \n"NOR,
              ob==me?"你":ob->name(1),FINGER_D->age_string(time()-ob->query_temp("logon_time")) );
        }

        write(line);
        return 1;
}

string display_attr(int gift, int value)
{
        if( value > gift ) return sprintf( HIY "%4d", value );
        else if( value < gift ) return sprintf( HIC "%4d", value );
        else return sprintf("%3d", value);
}

string status_color(int current, int max)
{
        int percent;

        if( max ) percent = current * 100 / max;
        else percent = 100;

        if( percent > 100 ) return HIC;
        if( percent >= 90 ) return HIG;
        if( percent >= 60 ) return HIY;
        if( percent >= 30 ) return YEL;
        if( percent >= 10 ) return HIR;
        return RED;
}

string transfer_string(string str, int length)
{
        string str1, str2, tmp;
        int i;

        tmp=str;
        while(sscanf(str,"%s*sm%s",str1,str2)==3)
                str=str1+str2;
        i=length-strlen(str);
        while(i>0)
        {
                tmp+=" ";
                i--;
        }
        return tmp;
}

string tribar_graph(int val, int eff, int max, string bcolor, string fcolor, string dcolor)
{
        string ret;
        int i, n, eff_n, max_n = 10;

        if( max == 0 ) max = 1;
        n = val * 100 / max / 10;
        eff_n = eff * 100 / max / 10;

        if( n < 0 ) n = 0;
        if( eff_n < 0 ) eff_n = 0;
        if( n > max_n ) n = max_n;
        if( eff_n > max_n ) eff_n = max_n;

        ret = NOR  + bcolor + fcolor ;
        for( i = 0 ; i < max_n; i ++ ) {
                if( i > eff_n ) ret += dcolor;
                if( i < n )  ret += "━";
                else ret += HIW"━"NOR;
        }
        ret += fcolor + NOR ;
        return ret;
}

int help(object me)
{
        write(@HELP

指令格式：score/sc
          score <对象名称>  （巫师专用）

显示自己或者指定对象（含怪物）的基本资料。
此指令可以“sc”代替。

对于隐藏参数只有当你道行达到脱胎换骨时才
可以看到。。。

相关讯息：hp

HELP
        );

        return 1;
}
