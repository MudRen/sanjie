//by dewbaby
//masterroom
  
#include <ansi.h> 
inherit ROOM; 
        
void create () 
       { 
         set ("short", HIW"环形石室"NOR); 
         set ("long", @LONG 
        
走入此环形石室，你只觉得一阵刺骨寒气从头顶传
渗进，传到全身。原来这里正是明湖冰穴的正下方。
要想从这里出去，似乎只能动手掘路(dig road)了。�
LONG); 
        
         
        set("exits", ([ /* sizeof==1  */
        "out":__DIR__"house1",        
        ])); 

        setup(); 
}
void init()
{
    add_action("do_dig","dig");

}
int do_dig(string arg)
{
    object me = this_player();
    if (!arg || arg !="road")
            return notify_fail("你要挖哪里?\n");
    if (me->is_busy() || me->is_fighting())
            return notify_fail("你正忙着其他事呢!\n");
     if ((int)me->query_skill("force",1) <200)
    return notify_fail("你的内功火侯还不够,这样恐怕会有伤原气!\n");
    if ((int)me->query("sen",1) < 400)
    return notify_fail("你的精神不够,无法挖地洞!\n");
         if( arg=="road"){ 
    if (random(me->query_str()) <= 20 )
    message_vision(me->name() + "运起内功，将精气传于双手，在地上挖了起来。\n",me); 
    tell_object(me,"你蹲下身，微微吸了一口气，伸手在地上挖了起来。\n"NOR);
    me->start_busy(5);
    remove_call_out("out1");
    call_out("out1", 6, me);
    return 1;
}
else {
     message("vision", me->name() +"蹲下身，微微运了一口气，伸手在地上挖了起来。\n",environment(me),({me}));
     tell_object(me,"你蹲下身，微微运了一口气，伸手在地上挖了起来。\n"NOR);
}
     tell_object(me,HIW"\n你眼前忽然一亮!\n\n原来你已经为自己掘出了生路!\n"NOR);
     me->move("/d/city/center");
     me->start_busy(3);
    message_vision(me->name() + "从地道里飞身跃了出来，把路人吓了一跳！\n",me); 
     return 1;
}
void out1(object me)
{          tell_object(me,"\n你觉得双手有点疼痛,但为了生还,只好继续挖。\n"NOR); 
     me->start_busy(5);
     remove_call_out("out");
     call_out("out",3,me); 
}
void out(object me)
{
     tell_object(me,"\n你觉得双手有点疼痛，但为了生还，只好继续挖。\n"NOR);
     me->move("/d/city/center");
    message_vision(me->name() + "从地道里飞身跃了出来，把路人吓了一跳！\n",me); 
}

    
