//玄天青狐剑法
//轩辕古墓特殊攻击技能
//by ivy 2002.2.9
 

inherit SKILL;
#include <ansi.h>

//灵狐探首 飞狐冲天 妖狐灵动 青狐扑食
//狐死首丘 狐疑未决 狐媚魇道 狐假虎威

mapping *action = ({
   ([  "action": "$N一招"+BLINK""+HIW"「灵狐探首」"NOR",身形一低，手中$w嗡嗡直刺$n的$l",
     "dodge":     0,
     "damage":     40,
     "damage_type":   "刺伤"
   ]),
([ "action":"只见$N纵身跃起,一招"+BLINK""+HIY"「飞狐冲天」"NOR",剑光如水,一泄千里,洒向$n全身",
     "dodge":     0,
     "damage":     40,
     "damage_type":   "割伤"
   ]),
   ([   "action":
"$N飘然而进,手中$w陡然突进,刹那间连出数剑,分刺$w全身各处要害,正是一招"+BLINK""+HIB"「妖狐灵动」"NOR".\n",
     "dodge":     0,
     "damage": 35,
     "damage_type":   "割伤"
   ]),
   ([ "action":
"$N手中$w斜斜的一指$n,犹如灵狐出洞，以迅雷之速直取$n的$l,却是一招"+BLINK""+HIR"「青狐扑食」"NOR".\n",
     "dodge":     0,
     "damage": 45,
     "damage_type":   "刺伤"
   ]),
  ([  "action":      
 "$N一招"+BLINK""+HIC"「狐死首丘」"NOR",剑尖指天，弓身探上，竟然是同归于尽的招式.\n",
     "dodge":     0,
     "damage": 40,
     "damage_type":   "刺伤"
   ]),
  ([   "action": 
"$N手中$w自左而右地划了一个大弧,刺向$n的$l,突然间又转到另一方向，这正是一招"+BLINK""+HIM"「狐疑未决」"NOR".\n",
     "dodge":     0,
     "damage":     50,
     "damage_type":   "刺伤"
   ]),
  ([ "action": 
"$N一式"+BLINK""+HIM"「狐媚魇道」"NOR",手中$w急转,化为一道血光,虚幻不定地出现在$n周围.\n",
     "dodge":     0,
     "damage":     30,
     "damage_type":   "刺伤"
   ]),
   ([ "action": 
"$N纵身轻轻跃起,剑光如轮急转,晃得$n头晕目眩,正是一招"+BLINK""+HIG"「狐假虎威」"NOR".\n",
     "dodge":     0,
     "damage":     35,
     "damage_type":   "割伤"
   ]),
});

int valid_learn(object me)
{
   object ob;

   if( (int)me->query("max_force") < 50 )
    return notify_fail("你的内力不够,没有办法练玄天青狐剑法.\n");

//   if( (string)me->query_skill_mapped("force")!= "jiuyin-force")
//     return notify_fail("青狐剑法必须配合玄天九阴真经才能练.\n");

   if( !(ob = me->query_temp("weapon"))
   ||   (string)ob->query("skill_type") != "sword" )
     return notify_fail("你必须先找一把剑才能练剑法。\n");

   return 1;
}

int valid_enable(string usage)
{
   return usage=="sword" || usage=="parry"|| usage=="throwing";
}

mapping query_action(object me, object weapon)
{
     mapping* m_actions;
     m_actions=me->query("skill_qinghu-jian");
     if(me->query("skill_qinghu-jian")==0 )
     return action[random(sizeof(action))];
     if( random(4) == 1 )
     return m_actions[random(sizeof(m_actions))];
     else
     return action[random(sizeof(action))];
}

int practice_skill(object me)
{
   if( (int)me->query("kee") < 30
   ||   (int)me->query("force") < 3 )
    return notify_fail("你的内力或气不够,没有办法练习玄天青狐剑法.\n");
   me->receive_damage("kee", 30);
   me->add("force", -3);
//  write("你按着所学练了一遍玄天青狐剑法.\n");
   return 1;
}

string perform_action_file(string action)
{
  return CLASS_D("gumu") + "/qinghu-jian/" + action;
}


void skill_improved(object me)
{
   int m_skill=me->query_skill("qinghu-jian",1);

   if(m_skill>200&&m_skill%10==0){
     tell_object(me,HIW"你对青狐剑法的领悟加深了，你的青狐剑法进入了一个新的境界！\n"NOR);
     if(random(me->query("kar"))<20){
        tell_object(me,HIW"然而你的心中居然产生了一种失落感！\n"NOR);
        return;
     }
     if(random(me->query("int"))<20){
       tell_object(me,HIW"然而你的心中升起一种惆怅的感觉，仿佛有一丝重要的东西没
有抓住。\n"NOR);
       return;
     }
     tell_object(me,HIW"你突然福至心灵，对青狐剑法领悟出了一招新的用法！\n"NOR
);
     tell_object(me,"请为这招取一个名字：");
     input_to( (: call_other, __FILE__, "name_skill", me:));
   }
   return;
}

void name_skill(object me, string arg)
{
   mapping* m_actions;
   mapping m_act=([]);
   int content;
   string msg;

   m_actions=me->query("skill_qinghu-jian");
   if(!pointerp(m_actions))m_actions=({});

   content=me->query("str")+2*me->query_skill("unarmed",1)/10;
   m_act+=(["damage":content]);
   content=-me->query("spi");
   m_act+=(["dodge" :content]);
   content=-me->query("cps");
   m_act+=(["parry" :content]);
   content=me->query("con")+me->query_skill("force",1)/10;
   m_act+=(["force" :content]);
   m_act+=(["damage_type":"刺伤"]);

   if(!arg||arg==" ")arg="青狐剑法必杀技"+chinese_number(sizeof(m_actions)+1);
   m_act+=(["name":arg]);
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_qinghu-jian",m_actions);
}
 

