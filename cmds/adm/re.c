// reclaim.c

int main(object me, string arg)
{
    int mem;
    object *ob;

    if (!SECURITY_D->valid_grant(me, "(arch)"))
        return 0;

    write("整理结果，共清除 " + reclaim_objects() + " 个变数。\n");

    ob = filter_array(objects(), (: clonep :));
    mem = sizeof(ob);
    while (mem--)
    if (!environment(ob[mem]) &&
        !interactive(ob[mem]) &&
        !ob[mem]->query_temp("body_ob"))
    {
        reset_eval_cost();
        printf("%O\n", ob[mem]);
        destruct(ob[mem]);
        ob -= ({ 0 });
        mem = sizeof(ob);
    }

    return 1;
}

int help(object me)
{
write(@HELP
指令格式 : reclaim

用处 : 将存在于记忆体里无用的变数清除掉, 以减少记忆体的使用。
HELP
     );
     return 1;
}


