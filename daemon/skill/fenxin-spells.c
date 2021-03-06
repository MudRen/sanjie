//焚心术
//fenxin-spells.c
//by dewbaby@sksj 12.2002


#include <ansi.h>
inherit SKILL;

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
        if( (int)me->query_skill("spells") <= (int)me->query_skill("fenxin-spells") )
             return notify_fail(WHT"你的基本法术修为还不够，无法领悟焚心术！\n"NOR);
        if( (int)me->query("str") < 20 )
             write(WHT"你还需要加强锻练身体!身体可是革命的本钱!\n"NOR,me);
        if( (int)me->query("bellicosity") > 270 )
             return notify_fail(HIR"你的杀气太高，无法学焚心术。\n"NOR);
    return 1;
}
int practice_skill(object me)
{
        return notify_fail(WHT"焚心术只能向师父学(learn)来增加熟练度。\n"NOR);
}

int stage(int level)
{
             if ( level <  80 ) return 1;
        else if ( level < 150 ) return 2;
        else if ( level < 230 ) return 3;
        else if ( level < 310 ) return 4;
        else if ( level < 390 ) return 5;
        else if ( level < 470 ) return 6;
        else if ( level < 550 ) return 7;
        else if ( level < 630 ) return 8;
        else return 9;
}

string level_description(int level)
{
        if ( stage(level) < 1 )
                return BLU "仁心" NOR;
        else if ( stage(level) < 2 )
                return YEL "锦心" NOR;
        else if ( stage(level) < 3 )
                return HIG "琴心" NOR;
        else if ( stage(level) < 4 )
                return CYN "悠心" NOR;
        else if ( stage(level) < 5 )
                return HIM "紫心" NOR;
        else if ( stage(level) < 6 )
                return MAG "残心" NOR;
        else if ( stage(level) < 7 )
                return HIR "焚心" NOR;
        else
                return HIW "无心" NOR;
}

string cast_spell_file(string spell)
{
        return CLASS_D("linghai") + "/fenxin-spells/" + spell;
}

string type() 
{
        return "magic";
}


