//春秋刀
inherit SKILL;
mapping *action = ({
        ([      "name":         "「春花秋月」",
                "action":       "$N一式「春花秋月」，脚起翩翩，
身形一晃，从$n眼前遁去，忽地在$n身旁出现，
挥刀起舞，手中$w无声无息地刺向$n的$l",
                "dodge":        5,
                "parry":        0,
                "damage":       20,
                "damage_tupe":  "刺伤",
                "parry_msg":    "$N一式「春花秋月」，脚起翩翩，
身形一晃，从$n眼前遁去，忽地在$n身旁出现",
                "parry_power":  0,
        ]),
        ([      "name":         "「春华秋实」",
                "action":       "$N一式「春华秋实」，凝住脚步，
手中$w化做一道光芒, 似慢实快，洒向$n$l",
                "dodge":        10,
                "parry":        -10,
                "damage":       25,
                "damage_type":  "劈伤",
                "parry_msg":    "$N一式「春华秋实」，凝住脚步，
手中$w化做一道光芒, 向$n劈去",
                "parry_power":  0,
        ]),
        ([      "name":         "「春兰秋菊」",
                "action":       "$N一式「春兰秋菊」，展开身形，
手中$w幻出无数刀花，向$n全身罩去",
                "dodge":        10,
                "parry":        -5,
                "damage":       25,
                "damage_type":  "砍伤",
                "parry_msg":    "$N一式「春兰秋菊」，展开身形，
手中$w幻出无数刀花，罩住$N全身要害",
                "parry_power": 0,
        ]),
        ([      "name":         "「春草闭闲门」",
                "action":       "$N一式「春草闭闲门」，加快步伐，
身形化作一团幻影，从意想不到之处，随意向$n$l劈出一刀",
                "dodge":        15,
                "parry":        -10,
                "damage":       30,
                "damage_type":  "砍伤",
                "parry_msg":    "$N一式「春草闭闲门」，加快步伐，
身形化作一团幻影，躲开$n的攻势",
                "parry_power":  0,
        ]),
        ([      "name":         "「秋花落更迟」",
                "action":       "$N一式「秋花落更迟」，身体急速旋转，
一个倒翻，手中$w唰地从胁下砍向$n的$l",
                "dodge":        10,
                "parry":        0,
                "damage":       20,
                "damage_type":  "砍伤",
                "parry_msg":    "$N一式「秋花落更迟」，身体急速旋转，
一个倒翻，化去$n的方才凌厉的攻击",
                "parry_power":  0,
        ]),
        ([      "name":         "「春风吹又生」",
                "action":       "眼见$N刀势已尽，不料其一式「春风吹又生」，
手中$w以一不可思异之角度，劈向$n要害",
                "dodge":        20,
                "parry":        -5,
                "damage":       30,
                "damage_type":  "劈伤",
                "parry_msg":    "眼见$N刀势已尽，不料其一式「春风吹又生」，
手中$w以一不可思异之角度，磕向$n的$l",
                "power_power":  0,
        ]),
        ([      "name":         "「春梦无痕，秋毫无犯」",
                "action":       "$N一式「春梦无痕，秋毫无犯」，脚踩虚步，
手中$w暗带内劲，从几个方向向$n的$l击去",
                "dodge":        5,
                "parry":        0,
                "damage":       20,
                "damage_type":  "割伤",
                "parry_msg":    "$N一式「秋山又几重」，脚踩虚步，
手中$w暗带内劲，从几个方向向$n的$l击去，震得$n手上发麻",
                "parry_power":  0,
        ]),
        ([      "name":         "「秋山又几重」",
                "action":       "$N一式「秋山又几重」，脚下频频换位，
手中$w以压顶之势连发几重刀意,攻向$n脑门要穴",
                "dodge":        20,
                "parry":        -20,
                "damage":       30,
                "damage_type":  "割伤",
                "parry_msg":    "$N一式「秋山又几重」，脚下频频换位，
手中$w以压顶之势连发几重刀意,随即脱出$n的攻势",
                "parry_power":  0,
        ]),
});
int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_force") < 200 )
                return
notify_fail("你的内力不够，没有办法学春秋刀法。\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "blade" )
                return
notify_fail("没有刀你怎么学春秋刀法？\n");

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
                return notify_fail("没有刀你怎么练春秋刀法？\n");

        if( (int)me->query("force") < 50 ) return notify_fail("你的内力不足，没办法舞刀弄枪。\n");
        if( (int)me->query("kee") < 50 )
                return
notify_fail("你的体力不够练这门刀法，还是先休息休息吧。\n");
        me->receive_damage("kee", 30);
        me->add("force", -5);
        return 1;
}
string perform_action_file(string action)
{
        return CLASS_D("zhenwu") + "/chunqiu-blade/" + action;
}

