// eating-force.c  by angell
inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) 
{ 
        if( ((int)me->query("food") - (int)me->max_food_capacity()) < (int)me->query_skill("eating-force", 1) )
                return notify_fail("大食神功，就是要吃的饱！更饱！再饱！！去，吃完了再来学。\n");

        return 1; 
        if( ((int)me->query("water") - (int)me->max_water_capacity()) < (int)me->query_skill("eating-force", 1) )
                return notify_fail("吃饱还要喝足。去，喝够了再来学。\n");
       return 1; 
}

int practice_skill(object me)
{
        return notify_fail("大食神功只能用学的，或是从运用(exert)中增加熟练度。\n");
}
string exert_function_file(string func)
{
        return CLASS_D("tianpeng") + "/eating-force/" + func;
}
