// recovers.c
// modify by mudring

#include <ansi.h>
inherit F_CLEAN_UP;
int main(object me, string arg)
{
        string name, reason;
        string path, status;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        status = wizhood(me); 
        path = me->query("env/backup");

        if (wiz_level(me) < wiz_level(status))
                return notify_fail("你没有权力使用这个指令。\n");
        if (! path) return notify_fail("没有这个备份路径！\n");
        if (! arg) return notify_fail("没有这个用户！\n");

        if (sscanf(arg, "%s because %s", name, reason)!=2)
                return notify_fail("recovers <id> because <xxx>。\n");
        seteuid(getuid());
        if( file_size(path + "login/" + name[0..0] + "/" + name + ".o")<0 )
                return notify_fail("没有这位使用者。\n");
        if( file_size(DATA_DIR + "login/" + name[0..0] + "/" + name + ".o")>0 )
                return notify_fail("这个ID已经被重新注册了。\n如果一定要恢复，请先Purge！\n");
        cp( path + "login/" + name[0..0] + "/" + name + ".o", DATA_DIR + "login/" + name[0..0] + "/" + name + ".o" );
        cp( path + "user/" + name[0..0] + "/" + name + ".o", DATA_DIR + "user/" + name[0..0] + "/" + name + ".o" );

        write( "使用者 " + capitalize(name) + " 的档案恢复了。\n");
        log_file("static/recovers", sprintf("[%s] %s recovers %s because %s.\n",
                ctime(time())[0..15], geteuid(this_player(1)), name, reason));
        seteuid(getuid(me));
       return 1;
}
int help(object me)
{
write(@HELP
指令格式：recovers <使用者姓名> because <原因>
HELP
        );
    return 1;
}

