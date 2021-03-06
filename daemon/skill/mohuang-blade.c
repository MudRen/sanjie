// 魔皇刀法
//轩辕古墓特殊攻击技能
//by junhyun@sk
//

inherit SKILL;
#include <ansi.h>
mapping *action = ({
        ([      "action":
"$N一招"+HIW"「刀影连身」"NOR"手中$w如影随形刀刀不离$n周身要命之处！",
                "damage":               20,
                "dodge":                -10,
                "parry":                0,
                "damage_type":  "割伤"
        ]),
        ([      "action":
"$N一招"+HIM"「如封似闭」"NOR"将手中$w舞的弥补透风，将$n围在刀光之中！",
                "damage":               20,
                "dodge":                -10,
                "parry":                -10,
                "damage_type":  "划伤"
        ]),
        ([      "action":
"$N一招"HIG"「破碎虚空」"NOR"手中$w寒光一闪，无数刀影飞出刺向$n的$l！",
                "damage":               20,
                "dodge":                -10,
                "parry":                10,
                "damage_type":  "刺伤"
        ]),
        ([      "action":
"$N一招"HIC"「斩神灭佛」"NOR"手中的$w舞成扇型，斜刺刺的扫向$n的$l",
                "damage":               20,
                "dodge":                -10,
                "parry":                0,
                "damage_type":  "砍伤"
        ]),
        ([      "action":
"$N一招"HIR"「刀破长空」"NOR"手中$w带者丝丝冷风由上至下划向$n的$l",
                "damage":               20,
                "dodge":                -10,
                "parry":                10,
                "damage_type":  "划伤"
        ]),
        ([      "action":
"$N一招"HIM"「血染灵霄」"NOR"双手紧握$w带着逼人的杀气，刺向$n的$l",
                "damage":               20,
                "dodge":                -10,
                "parry":                -10,
                "damage_type":  "刺伤"
        ]),
});

int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_force") < 80 )
                return
notify_fail("你的内力不够，没有办法学魔皇刀法。\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "blade" )
                return
notify_fail("你必须先找一把刀才能学魔皇刀法。\n");

        return 1;
}

int valid_enable(string usage)
{
        return (usage=="blade") || (usage=="parry");
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon = me->query_temp("weapon"))
        ||      (string)weapon->query("skill_type") != "blade" )
                return notify_fail("你必须先找一把刀，才能练刀法。\n");

        if( (int)me->query("kee") < 40 
   ||   (int)me->query("force") < 5 )
                return
notify_fail("你的体力不够练这门刀法，还是先休息休息吧。\n");
        me->receive_damage("kee", 30);
        me->add("force", -5);
        return 1;
}
string perform_action_file(string func)
{
return CLASS_D("gumu") + "/mohuang-blade/" + func;
}

