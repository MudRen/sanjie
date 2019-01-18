inherit ITEM;

#include <ansi.h>
void create()
{
        set_name(HIW"水晶球"NOR, ({"ball"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
         set("long", "这是一个水晶球。\n");
                set("unit", "个");
                set("value", 0);
        }
        setup();
}
void init()
{
        add_action("do_zhanbu", "zhanbu");
}

int do_zhanbu(string arg)
{
        object ob, zhanbu, *ob_list;
        object me = this_player();
        int i;
        if (!arg)
        return notify_fail("指令格式：zhanbu <人物>\n"); 
/*
        if( (int)me->query_skill("zhanbushu", 1) < 150 )
        return notify_fail("你的占卜术还不够高，无法使用水晶球这种高级货。\n");
*/

        message_vision(BLU"$N捏着手指，按照子、丑、寅、卯、辰、巳、午、未、申、酉、戌、亥的方位，仔细的掐算着。。。\n"NOR, me);
        ob = find_player(arg);
        if( !ob ) ob = find_living(arg);
        if( !ob || !me->visible(ob)) {
                arg = resolve_path(me->query("cwd"), arg);
                ob_list = children(arg);
                for(i=0; i<sizeof(ob_list); i++) {
                        if( !ob = environment(ob_list[i]) ) continue;
                        printf("%O\n", ob );
                }
                return 1;
        } 
        if (!ob) return notify_fail("现在没这个人.\n");
        zhanbu = environment(ob);
        if (!zhanbu) return notify_fail("这个人不知道在那里耶...\n");
        printf(HIW"你掐指算出%s(%s)现在好象在%s"NOR+HIW"一带活动。\n"NOR,
                (string)ob->name(),
                (string)ob->query("id"),
                (string)zhanbu->query("short"));
        if( random((int)ob->query("combat_exp", 1 ) / 2) < (int)me->query("combat_exp", 1)) {
        if(random(10) > 5 ) {
        tell_object(ob, HIY"冥冥中你觉得好象有人正在窥探你所在的方位。\n"NOR);
        }
        else {
        write("\n"); }
        }
        return 1;
        
}

