// finger.c
// modify by mudring

#include <ansi.h>
inherit F_CLEAN_UP;

int help(object);
void create()
{
        seteuid(getuid());
}

int main(object me, string arg)
{
    object *ob;

    if (!arg)
    {
        if (!wizardp(me))
            return help(me);     
        me->start_more( FINGER_D->finger_all() );
    } else
    if (arg == "-m")
    {
        if (!wizardp(me))
            return notify_fail("你无权使用 -m 参数。\n");
        ob = filter_array(users(), (: $1->name() != $1->name(1) :));
        me->start_more(FINGER_D->user_list(ob), 0);
    } else
    if (arg == "-z")
    {
        if (!wizardp(me))
            return notify_fail("你无权使用 -z 参数。\n");
        ob = filter_array(users(), (: metep($1) :));
        me->start_more(FINGER_D->user_list(ob), 0);
    } else
    if (arg == "-i")
    {
        if (!wizardp(me))
            return notify_fail("你无权使用 -i 参数。\n");
        ob = filter_array(users(), (: $1->query("env/invisibility") :));
        me->start_more(FINGER_D->user_list(ob), 0);
    } else
    if (arg == "-k")
    {
        if (!wizardp(me))
            return notify_fail("你无权使用 -k 参数。\n");
        ob = filter_array(users(), (: $1->query_condition("no_pk_time") :));
        me->start_more(FINGER_D->user_list(ob), 0);
    }
    else
    {
        arg = replace_string(arg, "#", " ");
        arg = replace_string(arg, ".", " ");

        if ((int)me->query("sen") < 15)
            return notify_fail("你的精神无法集中。\n");
        if (!wizardp(me))
            me->receive_damage("sen", 15);
        write(FINGER_D->finger_user(arg));
    }

    return 1;
}

int help(object me)
{
  write(@HELP
指令格式：
           finger [使用者英文代号]
           finger [使用者英文代号]@Mudname
 
 
这个指令可显示有关某个玩家的连线, 权限等资料.
如果是巫师，则可以不加任何参数来查看所有在线
玩家的资料。
see also : who, mudlist
HELP
    );
    return 1;
}
