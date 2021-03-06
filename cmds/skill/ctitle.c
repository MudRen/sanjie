// ctitle.c
// by mudring Oct/23/2002.

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string tmp;
    object ob;

    if (!me->query("club_master") && !wizardp(me))
        return notify_fail("只有帮会领导人才可以设置帮会成员的title？\n");

    if (!arg)
        return notify_fail("Usage：ctitle <sb> <title>\n");

    if (sscanf(arg, "%s %s", tmp, arg) == 2)
        ob = present(tmp, environment(me));
    else 
        return notify_fail("Usage：ctitle <sb> <title>\n");

    if (!ob)
        return notify_fail("这里没有这个人。\n");

    if (ob == me && !wizardp(me))
        return notify_fail("你不能更改自己的帮会头衔。\n");

    if (!userp(ob) && !wizardp(me))
        return notify_fail("看清楚，那并不是人！\n");

/*
    if (metep(ob) && !wizardp(me))
        return notify_fail("看看无垠的蓝天，那是永恒的虚空。\n");
*/

    if (ob->query("club") != me->query("club") && !wizardp(me))
        if (arg != "-cancel")
        return notify_fail("你只对本帮会的玩家使用这条命令！\n");

    if (me->is_busy() || me->is_fighting())
        return notify_fail("你正忙着呢！\n");

    if (ob->is_busy() || ob->is_fighting())
        return notify_fail("对方正忙着呢！\n");

    if (arg == "-cancel")
    {
        if (ob->query("new_title"))
        {
            ob->delete("new_title");
            return notify_fail("头衔清楚完毕！\n");
        }
        else return notify_fail("想捣乱？！\n");
    }

    if (strlen(arg) > 20 || strlen(arg) < 4)
        return notify_fail("想刷屏幕？找风铃去！\n");

    arg = HIW "[" + ob->query("club") + "] " + trans_color(arg) + NOR;

    message_vision("$N将$n的帮会头衔改为" + arg + "。\n",
        me, ob);

    ob->set("new_title", arg);

    return 1;
}

