// vi.c
// modify by mudring

#include <ansi.h>
#include "/doc/help.h"

inherit F_CLEAN_UP;
inherit "/feature/vi";

int main(object me, string file)
{
        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! file)
                return notify_fail("指令格式：edit <档名>\n");

        if (in_edit(me))
                return notify_fail("你已经在使用编辑器了。\n");

        seteuid(geteuid(me));
        file = resolve_path(me->query("cwd"), file);

        if (!(int)SECURITY_D->valid_write(file,me,"write"))
                return notify_fail("你没有足够的读写权利。\n");

        foreach (object user in users())
        if (file == "/"+in_edit(user) )
                return notify_fail("共享冲突："+user->name(1)+"("+capitalize(user->query("id"))+")"+"正在编辑该文件("+file+")。\n");

        MONITOR_D->report_adm_object_msg(me,HIR" edit " + file + "!"NOR); 
        log_file("cmds/edit/"+geteuid(me), sprintf("Vi %s at %s from %s.\n",
                                        file, log_time(),
                                        query_ip_number(me)));

        printf("编辑文件：%s\n",file);
        me->set("cwf", file);
        SECURITY_D->backup_file(file);
        start_edit(file);

        return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : edit <档名>, edit here

利用此一指令可直接在线上编辑档案。
【 LPMud 全萤幕编辑器 】1.3 版 3/25/1998  by 谢崇祥(Kenny Hsieh), 版权所有.

a            在游标後面加字               d  Ctrl-D    删除整行
f  Ctrl-Z    更新画面                     g  Ctrl-G    跳到特定行去
h  Ctrl-J    游标往左移一字               i            在游标前面插字
j  Ctrl-K    游标往下移一行               k  Ctrl-O    游标往上移一行
l  Ctrl-L    游标往右移一字               m            定义新功能键
n  Ctrl-N    搜寻/替换下个符合字串        o            在游标底下加一新行
q  Ctrl-Q    离开编辑器                   r  Ctrl-R    字串替换
s  Ctrl-S    字串搜寻                     u            取消某功能键定义
w  Ctrl-W    储存档案                     x  Ctrl-X    删除游标上的字
A  Ctrl-A    将游标移到行首               B  Ctrl-B    往上卷一页（22 行）
E  Ctrl-E    将游标移到行尾               F  Ctrl-F    往下卷一页（22 行）
J  Ctrl-P    将下行文字接到此行後面       O            在游标上方加一新行
U  Ctrl-U    将游标移到档头               V  Ctrl-V    将游标移到档尾
.            重覆上个指令                 ?  Ctrl-Y    辅助画面（此画面）
~  Ctrl-T    在游标前面插入一个「!」字元

合法的定义键是可印字母和 ESC、F1～F12、BACKSPACE、TAB、ENTER、INSERT、DELETE、
HOME、END、PAGEUP、PAGEDOWN、UP、DOWN、LEFT、RIGHT、Ctrl-A～Ctrl-Z。

欢迎传播此编辑器，但请保留版权宣告，有任何问题和建议请联络我：
kenny@cindy.cis.nctu.edu.tw。
最好使用Netterm编辑文件。
HELP
    );
    return 1;
}

