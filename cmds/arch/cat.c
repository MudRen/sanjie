// cat.c
// modify by mudring.

int main(object me, string arg)
{
    string file;

    seteuid(geteuid(me));


    if (!SECURITY_D->valid_grant(me, "(admin)"))
        return 0;

    if (!arg) return notify_fail("指令格式 :cat <档案名>\n");

    file = resolve_path(me->query("cwd"), arg);

    if (file_size(file) < 0)
        return notify_fail("没有这个档案。\n");

    if (!SECURITY_D->valid_read(file, me, "cat"))
        return notify_fail("没有这个档案。\n");

    if (file_size(file) > 32000 && !is_root(me) )
        write("文件太长，请用 more 指令查看。\n");
    else
        me->start_more(color_filter(read_file(file)));

    log_file("cmds/file/"+geteuid(me), 
        sprintf("cat %s [%s] from %s \n",
            file, log_time(), query_ip_number(me)));

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 :cat <档案名>

这个指令让你可以查阅一个文件的内容。

see also: more
HELP );
    return 1;
}


