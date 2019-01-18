

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        mapping skl, lls;
        string *sname, *mapped, str,id;
        int i,j;
        str = "";

        seteuid(getuid());

        if(!arg)
                ob = me;
        else{

                ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("你要察看谁的武器？\n");
        }
        if( ob!=me && !wizardp(me) )
                return notify_fail("你不是巫师？\n");

        id=ob->query("id");
        if (!ob->query("new_weapons"))
          {
          write( (ob==me ? "你" : ob->name()) + "目前并没有任何新宝石武器。\n");
          return 1;
          }
        skl =WSAVE_D->query_my_weapon(id);
        j = (int)sizeof(keys(skl));
        if(!sizeof(skl)) {
                write( (ob==me ? "你" : ob->name()) + "目前并没有任何新宝石武器。\n");
                return 1;
        }
        write( (ob==me ? HIR"你" : ob->name()) + "目前新宝石武器有：\n"NOR);

        str = "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
        sname  =  keys(skl);

       

        for(i=0; i<sizeof(sname); i++) {
        lls=skl[sname[i]];
        
        
                str = sprintf("%s%s%s%-10s" NOR " : %-10s %-10s\n", str,
                        (WSAVE_D->check_weapon(id,sname[i])==1) ? HIM : "",
                        (sname[i]==ob->query("new_weapons/main")) ? "  ": HIR"★"NOR,
                        sname[i],
                        skl[sname[i]]["name"],
                        skl[sname[i]]["id"],
                );
        }
         str += "\n━━━━━━━━━━━━━━━━━━━━━  "HIG"SHEKOU.STATION"NOR"  ━━━━━━━\n";
        this_player()->start_more(str);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : weapons|weapons [<某人>]

这个指令可以让你查询新宝石武器。



HELP
    );
    return 1;
}

