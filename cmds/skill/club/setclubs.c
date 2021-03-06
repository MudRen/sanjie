
//Edited by Wuyou@sk_sjsh 2003-4-8

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string id,club_name;
        object ob;
        int level;

        seteuid(getuid());

        if (! SECURITY_D->valid_grant(me, "(arch)")) return 0;

        if(!arg) 
                return notify_fail("指令格式 : setclub <某人> <某帮派>\n");
 
        if( sscanf(arg, "%s %s", id, club_name)!=2 ) 
                return notify_fail("指令格式 : setclub <某人> <某帮派>\n");

        ob = present(id, environment(me));
        if (!ob) ob = find_player(id);
        if (!ob) ob = find_living(id);
        if (!ob) return notify_fail("没有这个人喔。\n");
                
        ob->delete("club");
        ob->set("club", club_name);
        ob->set("club_level", 10);
        ob->set("club_master", 1);
              
        message_vision("$N将$n提升为"+club_name+"的创始人。\n",me,ob);
        ob->save();
        
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : setclub <某人> <某帮派>

将一名玩家提升为帮派头领。
HELP
    );
    return 1;
}





