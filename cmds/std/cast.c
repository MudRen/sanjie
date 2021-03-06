// cast.c
//Update By Aeddy
// modiy by bird for show skills
#include <ansi.h>
#include <skill.h>
#include "/cmds/std/valid_kill.h";

inherit F_CLEAN_UP;

// 加上显示武功种类的函数,add by bird
    int show_cast(string arg)
{
    mixed *files;
    string dir=SKILL_D(arg)->cast_spell_file(""); //获得skill的路径
    string pfms="";
   int i;

   if(!dir) return notify_fail("大大");	
    files=get_dir(dir+"*.c",-1);
    for(i=0;i<sizeof(files);i++)
      pfms+="『 "+files[i][0][0..<3]+" 』\n";
     write("你目前可以使用的法术有：\n");
    write(pfms);
     return 1;
}

void destruct_flag(object me);

int main(object me, string arg)
{
	string spells, spl, trg;
	object target;
      int show;
	
	seteuid(getuid());

        if((int)me->query_temp("no_cast")==1)
	        return notify_fail("你现在不能用魔法！\n");

	if( me->is_busy() )
		return notify_fail("( 你上一个动作还没有完成，不能念咒文。)\n");

	if( !wizardp(me) && environment(me)->query("no_magic") )
		return notify_fail("这里不准念咒文。\n");
		
    if( !arg )
   {
     show=1;
     arg=" ";
  }
	if( sscanf(arg, "%s on %s", spl, trg)==2 ) {
		target = present(trg, environment(me));
		if( !target ) target = present(trg, me);
		if( !target ) return notify_fail("这里没有 " + trg + "。\n");
		
		if(!valid_kill(me,target,0)) return 0;

//add by yudian for prevent pk

set_to_killer(me,target);
        if(me->query("combat_exp")<250000 && userp(target))
                return notify_fail("自己功夫没练好就想杀人？\n");

        if(me->query("daoxing")<200000 && userp(target))
                return notify_fail("自己功夫没练好就想杀人？\n");  

        if(userp(target) && target->query("age")<17)
                return notify_fail("本站暂时保护新手。\n");

/*
        if( userp(target) && target->query("ziyouchoose") == "nopk")
        	return notify_fail(HIR"对方选择了NOPK人生，你不能KILL！\n"NOR);

        if(me->query("ziyouchoose") == "nopk" && userp(target))
                return notify_fail(HIR"你选择了NOPK人生，还想杀人？\n"NOR);
*/
                
		if( userp(me) && userp(target) && 
		    target->query_temp("netdead") )
		   return notify_fail("对方正在断线中，不能对其施法。\n");
	} else {
		spl = arg;
		target = 0;
	}

	spl = replace_string( spl, " ", "_");

	if( stringp(spells = me->query_skill_mapped("spells")) ) {
	        int nocast;
		notify_fail("你所学的法术中没有这种功能。\n");
//add by bird
      if(show)
    {
     if(show_cast(spells))	return 1;
    else return notify_fail("你现在没有可以使用的法术。\n");}
		nocast=(int)SKILL_D(spells)->cast_spell(me, spl, target);
		//cast_spell should return an integer as the no_cast time.
		if (!nocast) 
		  nocast=(int)SKILL_D("spells")->cast_spell(me, spl, target);
                if (nocast) {
                  me->set_temp("no_cast", 1);
		  //each cast should return an integer which is
		  //the no_cast time fot this cast.
		  //also, in each cast, can set busy or no_move
		  //time individually.   --mon 8/24/97
		  call_out("destruct_flag", nocast, me);
		  return 1;
		}
		return 0;
		}
		
	return notify_fail("你请先用 enable 指令选择你要使用的咒文系。\n");
}

void destruct_flag(object me)
{
     if (me)
     	me->delete_temp("no_cast");
}

int help (object me)
{
        write(@HELP
指令格式：cast <咒文名称> [on <施咒对象>]
 
施法，你必需要指定<咒文名称>，<施咒对象>则可有可无。
在你使用某一个咒文之前，你必须先用 enable 指令来指定你要使用的咒文系。
 
注：如果你改变自己的咒文系，你原本蓄积的法力并不能直接转换过去，必须
    从 0 开始。
 
HELP
        );
        return 1;
}
