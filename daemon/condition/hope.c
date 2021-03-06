// Created by waiwai@2001/04/19

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

string *names = ({
	HIR"红色祥云"NOR,
	HIG"绿色祥云"NOR,
	HIY"金色祥云"NOR,
	HIB"蓝色祥云"NOR,
	HIM"粉色祥云"NOR,
	HIC"青色祥云"NOR,
	HIW"白色祥云"NOR
});

int update_condition(object me, int duration)
{
	string *colors = ({ HIW, HIR, HIY, HIC, HIM, HIG, HIB });

	if( !duration ) return 0;

       if( me->query("env/invisibility")>0 ) {
		tell_object(me, "你身上环绕着朵朵的"+names[random(sizeof(names))]+"，流转不停。。。\n" NOR );
	} else {
	tell_object(me, "你身上环绕着朵朵的"+names[random(sizeof(names))]+"，流转不停。。。\n" NOR );
	message("vision", me->name(1) + "身上环绕着朵朵的"+names[random(sizeof(names))]+"，流转不停。。。\n",
	environment(me), me);
	}

	if( (time() - me->query_condition("hope") ) <0 ) {
		me->clear_condition("hope");
		return 1;
	}

	if( me->query("kee")< me->query("max_kee") ) me->add("kee", 1);
	if( me->query("sen")< me->query("max_sen") ) me->add("sen", 1);
	
	me->apply_condition("hope", duration - 10);

	if( duration < 1 ) me->clean_condition("hope");

	return CND_CONTINUE;
}
