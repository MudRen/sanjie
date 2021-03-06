//Jitian-zhang【祭天神掌】
//BY Cigar 2002.04.19
#include <ansi.h>; 
inherit SKILL;

mapping *action = ({
        ([      "action":
"只见$N耸身提气，全身骨骼一阵爆响！"+HIR""+BLINK"「祭天天无应」"NOR"$N双手急速拍向$n的$l",
                "dodge":                5,
                "parry":                5,
            "force":            120,
                "damage_type":  "抓伤"
        ]),
        ([      "action":
"$N双腿连连踢出，身形亦节节拔高，"+HIY""+BLINK"「祭神神渺然」"NOR"$N倒转身形，踢向$n$l",
                "dodge":                5,
                "parry":                5,
            "force":            60,
                "damage_type":  "抓伤"
        ]),
        ([      "action":
"$N左手在$n眼前一划，右手带风，"+HIC""+BLINK"「祭灵灵无心」"NOR"由下而上往$n的$l狠命一拍",
                "dodge":                5,
                "parry":                5,
            "force":            80,
                "damage_type":  "抓伤"
        ]),
        ([      "action":
"$N单足点地，双臂一提，使了个"+HIG""+BLINK"「祭鬼鬼缠身」"NOR"势不可挡地扑向$n",
                "dodge":                5,
                "parry":                5,
            "force":            120,
                "damage_type":  "抓伤"
        ]),
        ([      "action":
"只见$N连退几步，突然一个矮身贴地而飞，"+HIW""+BLINK"「祭天神掌」"NOR"双掌异常的拍向$n$l",
                "dodge":                15,
                "parry":                15,
            "force":            180,
                "damage_type":  "抓伤"
        ]),
        ([      "action":
"$N大喝一声，双手青筋凸起，前后一抄，"+HIM""+BLINK"「无望无我」"NOR"似乎要把$n撕得粉身碎骨而后快",
                "dodge":                5,
                "parry":                5,
            "force":            180,
                "damage_type":  "砸伤"
        ]),
        ([      "action":
"$N往前一个轻纵，几乎与$n贴面而立，"+HIG""+BLINK"「弃天弃地」"NOR"一声阴笑中右手往$n的$l恶狠狠地一拍",
                "dodge":                5,
                "parry":                5,
            "force":            100,
                "damage_type":  "抓伤"
        ]),
        ([      "action":
"$N一个倒翻，背后就象长了眼睛似的，"+HIW""+BLINK"「堕落天使」"NOR"一掌又一掌延绵不绝地拍向$n的$l",
                "dodge":                5,
                "parry":                5,
            "force":            160,
                "damage_type":  "抓伤"
        ]),
});

int valid_learn(object me)
{
        if( me->query_temp("weapon") || me->query_temp("secondary_weapon")
)
                return notify_fail("练祭天神掌必须空手。\n");
        return 1;
}

int valid_enable(string usage)
{
        return usage=="unarmed";
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( (int)me->query("sen") < 50)
                return notify_fail(CYN"你的精神无法集中了，心有杂念休息一下再练吧。\n"NOR);
        if( (int)me->query("kee") < 50 )
                return notify_fail(CYN"你现在手足酸软，有伤内脏休息一下再练吧。\n"NOR);
        if( (int)me->query("force") < 50 )
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("kee", 40);
        me->add("force", -20);

        return 1;
}
     string perform_action_file(string func) 
     { 
             return CLASS_D("lunhui") + "/jitian-zhang/" + func; 
     } 
