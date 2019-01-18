// Created by waiwai@2002/12/05
// 相关文件：no_pk_time.c  killer.c 

#include <ansi.h>

int update_condition(object me, int duration)
{
	object ob1, ob2,  where;
	ob1=new("/u/waiwai/npc/ghost.c");
	ob2=new("/u/waiwai/npc/ghost.c");
	where =environment(me);

	if( wizardp(me) && !userp(me) ) return 0;

	// 只追杀在安全区的情况，安全区之外交给巡捕追杀
//	if( !where->query("no_fight") || !where->query("no_kill") || !where->query("no_magic") )  return 0;
	if( me->is_ghost() ) return 0;

	if( duration >= 15 ) {
	if( random(100) > 15 ) {
	tell_object(me,HIB"\n数道阴魂由地底窜起并朝着这边飞了过来！！！\n"NOR);
	if( !wizardp(me) )  {
	message("vision",HIB"\n数道阴魂由地底窜起并朝着这边的"+log_id(me)+"扑了过来！！！\n"NOR, environment(me), me);
	message("vision",CYN+
	me->name() + "阴魂缠身，好像做了什么亏心事，引来厉鬼报复。\n"NOR, environment(me), me);
	}
	ob1->move(where);
	ob1->kill_ob(me);
	ob1->set_leader(me);
	ob2->move(where);
	ob2->kill_ob(me);
	ob2->set_leader(me);
	}else{
	tell_object(me,HIB"\n你的后面好像有什么东西在跟着！！！\n"NOR);
	if( !wizardp(me) ) 
	message_vision(HIB"$N的后面好像有什么东西在跟着！！！\n"NOR,me);
	}
	}

	else if( duration >= 1 ) {
	if( random(100) > 15 ) {
	tell_object(me,HIB"\n一道阴魂由地底窜起并朝着这边飞了过来！！！\n"NOR);
	if( !wizardp(me) ) {
	message("vision",HIB"\n数道阴魂由地底窜起并朝着这边的"+log_id(me)+"扑了过来！！！\n"NOR, environment(me), me);
	message("vision",CYN+
	me->name() + "阴魂缠身，好像做了什么亏心事，引来厉鬼报复。\n"NOR, environment(me), me);
	}
	ob1->move(where);
	ob1->kill_ob(me);
	ob1->set_leader(me);
	}else{
	tell_object(me,HIB"\n你的后面好像有什么东西在跟着！！！\n"NOR);
	if( !wizardp(me) ) 
	message_vision(HIB"$N的后面好像有什么东西在跟着！！！\n"NOR,me);
	}
	}

//	if( !me->query_condition("no_pk_time") ) {
	if( !me->query_condition("killer") ) {
	me->clear_condition("ghost");
	return 1;
	}

	if( duration < 1 || me->query("no_poison")>0 ) return 0;
	return 1;
}

string query_type(object me) { return "ghost"; }

int no_clear_condition() { return 1; }
