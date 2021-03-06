// huanyang.c
// 还阳丹
// modify by mudring
// 按照死亡损失计算.

#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
    if (!wizardp(this_player()))
    {
        set("no_get", "嘿嘿，做梦吧! \n");
        set("no_drop","这么宝贵的还阳丹，哪能乱扔! \n");
    }
                                             
    add_action("do_eat", "eat");
}

void create()
{
    set_name(HIG "还阳丹" NOR, ({"huanyang dan", "dan"}));
    set_weight(20);
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("unit", "粒");
        set("long", "一粒还阳丹，据说有起死回生之效。\n");
        set("value", 100000);
    }

    set("is_monitored", 1);
    setup();
}

int do_eat(string arg)
{
    int i, j, k;
    object victim = this_player();
    string wizard = this_object()->query("clone_by_wizard");

    if (!id(arg))
        return notify_fail("你要吃什么？\n");

    if (!stringp(wizard))
        return notify_fail("哪儿偷的？？\n");

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
    victim->set("die_reason", "已经由" + wizard +"用还阳丹恢复");
    victim->save();

    if (userp(victim))
        log_file("static/EATHYD", sprintf("%s(%s) Got recovered by %s on %s.\n",
                 victim->name(1), geteuid(victim), wizard, log_time()));

    message_vision(HIG "\n$N吃下一粒还阳丹，硬是从白无常那里逃脱，捡回了一条小命。\n\n" NOR, 
                   victim);

    call_out("dest", 0);
    return 1;
}

void dest()
{
    if (this_object())
        destruct(this_object());
}
