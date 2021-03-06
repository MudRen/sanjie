//焚心刀法
//fenxin-blade.c
//by dewbaby@sksj 12.2002

//force max=30, dodge max=20, parry max=5

 
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action":  "$N向上跃起，一招"BLINK" "HIC"「我心何在」"NOR"，手中$w在空中画了一圆，直击向$n的脸颊",
        "force":    -30,
        "dodge":    -10,
        "damage":    30,
        "skill_name" : "我心何在",
        "damage_type":  "劈伤"
]),
([      "action":  "$N一招"BLINK""HIY"「诚心似锦」"NOR"，微微一笑间，手中$w直绕向$n的$l",
        "force":   -30,
        "dodge":   -10,
        "damage":   30,
        "skill_name" : "诚心似锦",
        "damage_type":  "内伤"
]),
([  "action":  "$N一招"BLINK" "HIB"「心心相印」"NOR"，手中$w化为一道寒月光，将$n团团围住，$n只觉身上一阵巨痛!",
        "force":   -30,
        "dodge":   -20,
        "parry":    -5,
        "damage":   30,
        "skill_name" : "心心相印",
        "damage_type":  "内伤"
]),
([  "action":  "$N举头望天，随手一刺，手中$w顿时逼向$n。这一招"BLINK" "HIM"「心神不宁」"NOR"，使$n迷茫失去了方向!",
        "force":    -30,
        "dodge":    -15,
        "damage":    30,
        "skill_name" : "心神不宁",
        "damage_type":  "刺伤"
]),
([  "action":  "$N跃在半空，回头焉然一笑，一招"BLINK" "HIW"「兰心惠畅」"NOR"如流水般涌向$n。$w在$n手臂上砍出一道鲜红的口子!",
        "force":    -30,
        "dodge":    -15,
        "damage":    30,
        "skill_name" : "兰心惠畅",
        "damage_type":  "砍伤"
]),
([  "action":  "$N身形忽快忽慢，如鬼魅飘摇不定。这正一招"BLINK" "MAG"「心阔如海」"NOR"直到$w砍到跟前，才发现为时已晚，被逼得连连后退。",
        "force":    -30,
        "dodge":    -15,
        "damage":    30,
        "skill_name" : "心阔如海",
        "damage_type":  "砍伤"
]),
([ "action":
     "$N右脚轻点地面,左手将$w向天抛起, 这一招"BLINK" "HIR"「心灰意冷」"NOR"直逼$n的后背，$n背上顿时鲜血淋淋！",
        "force":    -30,
        "dodge":    -10,
        "damage":    30,
        "skill_name": "心灰意冷",
        "damage_type":"割伤"
]),
 (["action":    "$N飞身向前跃到$n身后,随手就是一招"BLINK" "WHT"「心伤意绝」"NOR"只见一道长长的伤痕从$n手臂上显现,简直惨不忍睹!",
        "force":   -30,
        "dodge":   -15,
        "damage":   30,
        "skill_name": "心伤意绝",      
        "damage_type": "刺伤"
]),
(["action":   "$N抬起左手，弓身鬼秘一笑，一招"BLINK" "HIM"「剑胆琴心」"NOR"将$n的手臂砍得鲜血淋漓!",
        "force":  -30,
        "dodge":  -10,
        "damage":  35,
        "skill_name": "剑胆琴心",
        "damage_type": "砍伤"
]),
(["action":  "$N微然一笑，双足点地一跃而起，手中$w忽然力度巨增，一波一波向$n涌去。这正是一招"BLINK" "HIG"「心动一笑」"NOR"!",
        "force":  -30,
        "dodge":  -15,
        "damage":  40,
        "skill_name": "心动一笑",
        "damage_type": "劈伤"
]),
(["action":   "$N双手轻击，将$w夹于腋下，神情似乎已然厌站。转瞬间却使出一招"BLINK" "HIW"「心力憔悴」"NOR",$n顿时眼花缭乱，动作慢了下来。",
        "force":  -30,
        "dodge":  -10,
        "damage":  40,
        "skill_name": "心力憔悴",
        "damage_type": "刺伤"
]),
(["action":  "$N侧首凝望$n，双目含情，似醉非醉，$n正疑惑不解，$N却全力使出最后一招"BLINK" "HIR"「魔由心生」"NOR"！",
        "force":  -30,
        "dodge":  -10,
        "damage":  35,
        "skill_name": "魔由心生",
        "damage_type": "刺伤"
])
});

int valid_enable(string usage) { return (usage == "blade");}

int valid_learn(object me)
{
        object weapon;

        if ((int)me->query("force", 1) < 10)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query("sen",1) < 10)
                return notify_fail("你的精神太弱了! \n");
        if ( !objectp(weapon = me->query_temp("weapon"))
        || ( string)weapon->query("skill_type") != "blade" )
                return notify_fail("你必须先找一把刀才能练习刀法。\n");
        if( (int)me->query_skill("huanyue-jianfa") <= (int)me->query_skill("fenxin-blade") )
                return notify_fail("你的环月剑法还不够，无法由剑法领悟刀法！\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
         return action[random(sizeof(action))];
}

string query_parry_msg(object weapon)
{
         return action[random(sizeof(action))]["parry_msg"];
}

string query_dodge_msg(string limb)
{
         return action[random(sizeof(action))]["dodge_msg"];
}
int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n"); 
        if ((int)me->query("qi") < 50)
                return notify_fail("你的体力不够练习环月剑法。\n");
        me->add("kee", -30);
        me->add("force",-5);
        write(HIB"心伤心残心灰意冷...无心忘心悠悠我心...\n"NOR,me);
        return 1;
}
string perform_action_file(string func) {
       return CLASS_D("linghai") + "/fenxin-blade/" + func;
}


