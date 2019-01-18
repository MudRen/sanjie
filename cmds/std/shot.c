// shot.c,jjf烧符咒专用
// created 7-4-97 pickle
// modified by vikee 2000.10
// modified by bird 2004.06.23

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    string targetname, fabaoname;
    object obj, *inv, target, obj2,old_env, fabao;
    int i, amount;
    mixed no_get;

    if( !wizardp(me) && environment(me)->query("no_magic") )
     return notify_fail("这里禁止祭符咒。\n");
     if( !arg ) return notify_fail("你要祭哪样符咒？\n");

    // Check if correct format is followed
    if( sscanf(arg, "%s on %s", fabaoname, targetname)>2 )
      return notify_fail("指令格式 : shot <符咒名称> [on <目标>]\n");

    // Check if both a fabao and a target is specified.
    // if so, then check 1. whether the player own's the fabao,
    // and 2. check whether the target is in the same environment.
    if( sscanf(arg, "%s on %s", fabaoname, targetname)==2 )
    {
	fabao=present(fabaoname, me);
     if(!fabao) return notify_fail("你没有 "+fabaoname+" 这样符咒。\n");
	target = present(targetname, environment(me));
	if (me->is_busy() && !fabao->query("no_busy"))
        return notify_fail("你上一个动作还没有完成，无暇分身祭符咒。\n");
	if(!target) return notify_fail("这里没有 " + targetname + "。\n");
// 去掉对如来怪的使用限制
    //if(target->query("taskguai")) 
    // return notify_fail("你张开嘴，结结吧吧地念了几声咒语。\n");
	if(target==me)
     return notify_fail("对自己祭符咒？\n");
	
	// forbid to kill a player whose mudage <16 .here is added by vikee :P
	if(me->query("combat_exp")<50000 && userp(target))
		return notify_fail("自己功夫没练好，就想杀人？\n"); //here is modified by vikee
   
	if(me->query("daoxing")<10000 && userp(target))
  		return notify_fail("自己功夫没练好，就想杀人？\n");//here is modified by vikee

      return fabao->shot(targetname);
	
}
    fabao=present(arg, me);
     if(!fabao) return notify_fail("你没有" + arg +"这样符咒。\n");
    if (me->is_busy() && !fabao->query("no_busy"))
     return notify_fail("你上一个动作还没有完成，无暇分身祭符咒。\n");

     return fabao->shot();
}
int help(object me)
{
    write(@HELP
指令格式 : shot <符咒名称> [on <目标>]

这个指令可以让你祭一项符咒，将军府弟子专用。

HELP
			);
		     return 1;
		 }
