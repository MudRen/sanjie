// top.c
// modify by mudring

// #define DEBUG 1

#include <ansi.h>
#include <mudlib.h>
#include <combat.h>
#ifdef DEBUG
#include "ctop.h"
#endif
#include "valid_system.h"

inherit F_CLEAN_UP;
int top_list(object ob1,object ob2);
int get_score(object ob);

int main(object me, string arg)
{
        
        object *list, *ob;
        int i, j, k;
        string msg;
if (!wizardp(me)){
write("无法取得排名\n"); return 1;

}
        if (! arg)
                k = 10;
        else {
        sscanf(arg, "%d", k);
        if (k < 10) k = 10;
        if (k > 50) k = 50;
        }
        if (me->query("sen") < 80 )
                return notify_fail("你太累了,歇歇吧.\n");
    if (!valid_system(me)) return 0;
        me->add("sen", -10);
        ob = filter_array(users(), (: userp($1) && !wizardp($1) :));
        list = sort_array(ob, (: top_list :));

        msg =  "\n                ┏ 三界神话高手排行榜 ┓\n";
        msg += "┏━━━┯━━━┻━━━━━━━━┯━┻━━━━┯━━━━━┓\n";
        msg += "┃名 次 │    名        字        │  门    派  │ 综合评价 ┃\n";
        msg += "┠───┴────────────┴──────┴─────┨\n";
        if (k > sizeof(list)) k = sizeof(list);
        for (i = 0 ;i < k ; i++) {
                if(list[i] == me) msg += BBLU HIY;
                msg += sprintf("┃  %-4d  %-12s %-10s    %-12s   %6d  ┃\n",
                        i+1, list[i]->query("name"), "("+list[i]->query("id")+")",
                        list[i]->query("family")?list[i]->query("family/family_name"):"普通百姓",
                        get_score(list[i]));
                reset_eval_cost();
        }
        msg += "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
        msg +=  "\n "+HBYEL HIW+"你目前的评价是：";
        msg += sprintf("%5d \n"NOR, get_score(me));
        me->start_more(msg);
        return 1;

}
int top_list(object ob1, object ob2)
{
        int score1,score2;

        reset_eval_cost();
        score1 = get_score(ob1);
        score2 = get_score(ob2);
        return score2 - score1;
}

int get_score(object ob)
{
    string skill_type;
    object weapon;
    int attack_points, dodge_points, parry_points;
    int score;

    if (objectp(weapon = ob->query_temp("weapon")))
        skill_type = weapon->query("skill_type");
    else
        skill_type = "unarmed";

#ifdef DEBUG
    attack_points = skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
    parry_points  = skill_power(ob, skill_type, SKILL_USAGE_DEFENSE);
    dodge_points  = skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);
#else
    attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
    parry_points  = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_DEFENSE);
    dodge_points  = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);
#endif

    score = attack_points + (dodge_points + parry_points) / 2;
    score = attack_points;
    return (score / 1000 + 1);
}

int help(object me)
{
write(@HELP
指令格式 : top
 
这个指令可以让你知道在线十大高手是哪些，别去惹他们。 
 
HELP
    );
    return 1;
}
