// score.c



#include <ansi.h>
#include <combat.h>
#include <mudlib.h>

inherit F_CLEAN_UP;

string display_attr(int gift, int value);
string status_color(int current, int max);
string date_string(int date);
string tribar_graph(int val, int eff, int max, string bcolor, string fcolor, string dcolor);

void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
        object ob;
        mapping my;
        string line, str, skill_type, *marks,*hskill,*nskill;
        object weapon;
        int i, attack_points, dodge_points, parry_points;
        hskill=({"sword", "blade","hammer","staff","whip","axe",
                 "fork","spear","mace","stick","unarmed","dodge",});
        nskill=({"剑术","刀法","大锤法","魔杖术","鞭术","大斧术","叉术","枪术","锏法",
                "棍术","拳腿术","敏捷术",});

        seteuid(getuid(me));
        if(!arg)
                ob = me;
        else if (wizardp(me)) {
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("你要察看谁的状态？\n");
        } else
                return notify_fail("只有巫师能察看别人的状态。\n");

        my = ob->query_entire_dbase();
        write(NOR YEL"≡≡≡≡≡≡≡≡≡"HIG"地"NOR YEL"≡≡"HIG"域"NOR YEL"≡≡"HIG"火"NOR YEL"≡≡"HIG"档"NOR YEL"≡≡"HIG"案"NOR YEL"≡≡≡≡≡≡≡≡≡\n"NOR);
        write("你现在的仙衔 : "+RANK_D->query_rank(ob)+"\n");
        write("你现在的职称 : "+ob->short(1)+"\n");
        if(ob->query("hell_type"))     write("你现在的角色 : "+HIR+ ob->query("hell_type")+NOR+"\n");  
                                  else write("你现在的角色 : 普通农夫\n");  
 
        line = NOR YEL"≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n"NOR;
        str = "";
 


        
      
        if( objectp(weapon = ob->query_temp("weapon")) )
                skill_type = weapon->query("skill_type");
        else
                skill_type = "unarmed";

       attack_points = CITY_D->hell_skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
        parry_points = CITY_D->hell_skill_power(ob, skill_type, SKILL_USAGE_DEFENSE);
        dodge_points = CITY_D->hell_skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);

       line += sprintf( " 体格：[%s %4s %s]  ",
                 NOR, display_attr(my["str"], ob->query_str()), NOR );
        if( my["eff_gin"] <my["max_gin"] ) str = HIR+"生病";
        else if( my["gin"]*100 / my["max_gin"]>=70 ) str = HIG + "饱满";
        else if( my["gin"]*100 / my["max_gin"]>=40 ) str = HIR + "疲倦";
        else str = HIB + "很累";
        line += "〖"HIR"精神"NOR"〗  " + tribar_graph(my["gin"], my["eff_gin"], my["max_gin"], NOR, HIR ,HIW)
                + sprintf( "  [%4s%s]\n", str,NOR);
        line += sprintf( " 根骨：[%s %4s %s]  ",
                NOR, display_attr(my["con"], ob->query_con()), NOR );
        if( my["eff_kee"] <my["max_kee"] ) str = HIR+"伤残";
        else if( my["kee"]*100 / my["max_kee"]>=70 ) str = HIG + "充沛";
        else if( my["kee"]*100 / my["max_kee"]>=40 ) str = HIR + "受伤";
        else str = HIB + "重伤";
        line += "〖"HIR"气血"NOR"〗  " + tribar_graph(my["kee"], my["eff_kee"], my["max_kee"], NOR, HIR ,HIW)
                + sprintf( "  [%4s%s]\n",str,NOR);
        
        
        
        

        if( my["food"] * 100 / ob->max_food_capacity() >= 80 ) str = HIG+"很饱";
        else if( my["food"] * 100 / ob->max_food_capacity() >= 50 ) str = HIC+"正常";
        else if( my["food"] * 100 / ob->max_food_capacity() >= 20 ) str = HIR+"缺食";
        else str = HIB + "饥饿";
        
        

        if( my["water"] * 100 / ob->max_water_capacity() > 60 ) str = HIG + "正常";
        else if( my["water"] * 100 / ob->max_water_capacity() > 30 ) str = HIR + "缺水";
        else str = HIB + "饥渴";
        line += sprintf( " 悟性：[%s %4s %s]  ",
                NOR, display_attr(my["int"], ob->query_int()), NOR );
        line += "〖"HIC"食物"NOR"〗：" + tribar_graph(my["food"], ob->max_food_capacity(),
                ob->max_food_capacity(), NOR, HIC ,HIR)
                + sprintf( "  [%4s%s]\n", str, NOR );        
        line += sprintf( " 灵性：[%s %4s %s]  ",
                NOR, display_attr(my["spi"], ob->query_spi()), NOR );
        line += "〖"HIC"饮水"NOR"〗：" + tribar_graph(my["water"], ob->max_water_capacity(),
                ob->max_water_capacity(), NOR, HIC ,HIR)
                + sprintf( "  [%4s%s]\n",  str, NOR );
              if(ob->query("age")>25)

      
        line += sprintf(NOR CYN"┏━━━━━━━━━━━━━━━HELLFIRE━━━━━━━━━━━━━━┓\n" NOR);
        line += sprintf(NOR CYN"┃"NOR WHT"〖 技能升级点 〗%s%14-d " NOR "     "WHT"〖 炼火经验 〗%s%4d "NOR"      "CYN" ┃ "NOR"\n" NOR,
                  HIY,my["hell_pot"],HIW,my["hell_exp"]);

        line +=  sprintf(NOR CYN"┃"NOR WHT"〖 魔法点 〗   %s%16-d " NOR "     "WHT"〖 魔法等级 〗%s%4d "NOR"     "CYN" ┃ "NOR"\n" NOR,
                  HIY,my["magic_pointed"],HIW,my["magiclevel"]);
        line += sprintf(NOR CYN"┗━━━━━━━━━━━━━━"HIY"S"HIR"·"HIY"J"HIR"·"HIY"S"HIR"·"HIY"H"NOR CYN"━━━━━━━━━━━━━┛\n"NOR);
        


     if(wizardp(this_player())) 
        line += sprintf("\n 战斗攻击力 " HIW "%d (+%d)" NOR "\t\t战斗防御力 " HIW "%d (+%d)\n\n" NOR,
        attack_points/100 + 1, ob->query_temp("apply/damage"),
                (dodge_points + (weapon? parry_points: 
                (parry_points/10)))/100 + 1, ob->query_temp("apply/armor"));
        else line+=sprintf(" 兵器伤害力： ["HIR"%d"NOR"]" NOR "\t\t盔甲保护力： ["HIG"%d"NOR"]\n\n" NOR,
        ob->query_temp("apply/damage"),
        ob->query_temp("apply/armor"));
     line +="地狱火角色技能:\n";
        for(i=0;i<sizeof(hskill);i++)
        {       
        
        line +=sprintf("%s %10-s %18-d  "NOR,"〖"+HIC+nskill[i]+NOR+"〗","("+hskill[i]+")",ob->query("hell_skill/"+hskill[i]));
        if (i-((i/2)*2)==1) line+="\n";
        }
        line+="\n";
        line += YEL"≡≡≡≡≡≡≡≡≡≡ "HIR"三界神话"HIY"·"HIG"蛇口站"NOR YEL" ≡≡≡≡≡≡≡≡≡≡≡\n"NOR;

        write(line+BBLK);
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

string tribar_graph(int val, int eff, int max, string bcolor, string fcolor, string dcolor)
{
        string ret;
        int i, n, eff_n, max_n = 12;

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
指令格式：score
          score <对象名称>      （巫师专用）

显示自己或者指定对象（含怪物）的基本资料。此指令可以“sc”代替。

相关讯息：hp
HELP
        );

        return 1;
}


