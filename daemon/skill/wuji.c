// wuji.c  【无极幻化】by cigar 2002.01

#include <ansi.h>

int valid_learn(object me) { return 1; }

int practice_skill(object me)
{
        return notify_fail("无极幻化只能向师父学，增加熟练度。\n");
}
string exert_function_file(string func)
{
        return __DIR__"wuji/" + func;
}

int stage(int level)
{
             if ( level < 100 ) return 1;
        else if ( level < 180 ) return 2;
        else if ( level < 260 ) return 3;
        else if ( level < 340 ) return 4;
        else if ( level < 420 ) return 5;
        else if ( level < 560 ) return 6;
        else if ( level < 680 ) return 7;
        else if ( level < 800 ) return 8;
        else return 9;
}

string level_description(int level)
{
        if ( stage(level) < 3 )
                return BLU "第"+chinese_number( stage(level) )+"段　" NOR;
        else if ( stage(level) < 5 )
                return HIB "第"+chinese_number( stage(level) )+"段　" NOR;
        else if ( stage(level) < 7 )
                return YEL "第"+chinese_number( stage(level) )+"段　" NOR;
        else if ( stage(level) < 9 )
                return CYN "第"+chinese_number( stage(level) )+"段　" NOR;
        else 
                return HIW "第"+chinese_number( stage(level) )+"段　" NOR;
}

void skill_improved(object me)
{
        int level = (int)me->query_skill("wuji", 1);
        if ( stage(level) == stage(level-1) + 1)
        {
        if( (int)me->query("wuji_bonus") < stage(level) )
        {
        me->set("wuji_bonus", stage(level));
        me->set("max_kee", (int)me->query("max_kee") + stage(level)*100 );
        me->set("max_sen", (int)me->query("max_sen") + stage(level)*100 );
        me->save();
        log_file("wuji-bonus", ctime( time() )+": "
                                +me->query("name")+"("+me->query("id")+")"
                                +" got neili "+(stage(level)*100)+".\n");
                        message_vision(HIY "$N突然觉得心中无盼，似无极幻化。原来是$N的无极幻化进入了第"+chinese_number(stage(level))+"段境界！\n" NOR, me);

                }
        }
                        
}
// passion addd
 string cast_spell_file(string spell) 
{
return CLASS_D("youning") + "/wuji/" + spell; 
}
