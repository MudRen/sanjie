
// recover.c
// 恢复死亡
// by mudring
// 按照死亡损失计算.
// 只能恢复一次死亡损失，重复使用无效

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    int i, j, k;
    object victim;
    string reason;

    if (!SECURITY_D->valid_grant(me, "(arch)"))
        return 0;

    if (!arg)
        return notify_fail("你要干什么？\n");

    if (sscanf(arg, "%s because %s", arg, reason) != 2)
        return notify_fail("recovers <id> because <xxx>。\n");

    seteuid(getuid());

    if (!objectp(victim = present(arg, environment(me))) || !userp(victim))
        return notify_fail("你只能恢复使用者的损失。\n");

    i = victim->query("death/combat_exp_loss");
    j = victim->query("death/dx_loss");
    k = victim->query("death/skill_loss");

    victim->add("combat_exp", i);
    victim->add("daoxing", j);

    while (k--)
    {
        victim->skill_death_recover();
    }

    if ((int)victim->query("potential") > (int)victim->query("learned_points"))
        victim->add("potential",
                    ((int)victim->query("potential") 
                     - (int)victim->query("learned_points") ) * 4 / 5);

    victim->set("death/combat_exp_loss", 0);
    victim->set("death/dx_loss", 0);
    victim->set("death/skill_loss", 0);
    victim->set("die_reason", "已经由" + me->query("name") + getuid(me) +"恢复");
    victim->save();

    message_vision(HIY "\n$N手指轻轻一弹，四下顿时增色，"
                   "天空降下一道七彩光华笼罩了$n。\n\n" NOR,
                   me, victim);

    message_vision(HIM"突然从天空传来一声大喝: 何人竟敢随意修改玩家数据？\n"NOR,
                   me, victim);

    message_vision(HIR "\n$N说到：$n非正常死亡，恢复损失，并且已经记录在案！\n\n" NOR,
                   me, victim);

    write(CYN"使用者"HIR + victim->name(1) + NOR CYN"上次死亡损失恢复了。\n"NOR);
    tell_object(victim,
        CYN"巫师"HIR + me->name(1) + NOR CYN"恢复了你上次的死亡损失。\n"NOR);

    if (userp(victim) && !wizardp(victim))
        log_file("static/RECOVER", sprintf("%s Got recovered by %s because %s at %s.\n",
                 getuid(victim), getuid(me), reason, log_time()));

    seteuid(getuid(me));
    return 1;
}
int help(object me)
{
write(@HELP
指令格式：recover <使用者姓名> because <原因>
HELP
        );
    return 1;
}

