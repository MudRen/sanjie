//凌海心法
//linghai-force.c
//by dewbaby@sksj 12.2002


#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force",1) < 40)
            return notify_fail(WHT"你的基本内功还未学好，无法领悟凌海心法！\n"NOR);

    return 1;
}

int practice_skill(object me)
{
        return notify_fail(WHT"凌海心法只用从师傅那里学(learn)来增加熟练度。\n"NOR);
}
int stage(int level)
{
        if( level <60 ) return 1;
        else if ( level < 120 ) return 2;
        else if ( level < 180 ) return 3;
        else if ( level < 240 ) return 4;
        else if ( level < 300 ) return 5;
        else if ( level < 360 ) return 6;
        else if ( level < 420 ) return 7;
        else if ( level < 500 ) return 8;
        else return 9;
}

string level_description(int level)
{
        if ( stage(level) < 2 )
                return BLU "浅藏人海" NOR;
        else if ( stage(level) < 3 )
                return YEL "凝望沧海" NOR;
        else if ( stage(level) < 4 )
                return HIG "陨入草海" NOR;
        else if ( stage(level) < 5 )
                return HIY "荡漾心海" NOR;
        else if ( stage(level) < 6 )
                return HIC "沉浮欲海" NOR;
        else if ( stage(level) < 7 )
                return HIM "悠走福海" NOR;
        else if ( stage(level) < 8 )
                return MAG "静定冬海" NOR;
        else if ( stage(level) < 9 )
                return HIR "穿越死海" NOR;
        else
                return HIW "空绝无海" NOR;
}

string exert_function_file(string func)
{
       return CLASS_D("linghai") + "/linghai-force/" + func;
}

