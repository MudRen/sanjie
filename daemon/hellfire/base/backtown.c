#include <ansi.h>

inherit F_DBASE;
inherit SSERVER;

#include <magic_power.h>

string get_name(){return "回城术";}//法术名称
string get_help()                  //法术说明,以后直接help,方便修改
{
        return "这个法术可以帮你回到客栈,需要一定的魔法点１";
}

int do_cast(object me,object target)
{
        string helltype;
        if(me->is_fight())
        {
                tell_object(me,"你在战斗中，正忙着呢！\n");
                return 1;
        }
        if(me->query("magic_pointed")<10)
        {
                tell_object(me,"你的魔法点太少了，恐怕用不了这个法术!\n");
                return 1;
        }
        helltype=me->query("hell_type");
        if(!helltype) helltype="野蛮人";
        if(!userp(me)) return 1;
        me->add("magic_pointed",-magic_power[helltype]/10);
        me->move("/d/city/kezhan");
        return 1;
}

