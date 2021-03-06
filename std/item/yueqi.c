// Inheritable Object:/inherit/item/yueqi.c
// Written by jjgod@FYTX.

#include <ansi.h>
inherit ITEM;

string *start_msg=({
        "只见$N拿出$n，细细的调好了琴弦，对着大家深深一揖。\n",
        "只见$N抱起$n，抬起头来对着大家微微一笑。\n",
        "$N拿出$n，手指轻轻拨动了一下琴弦。\n",
        "$N面对大家，摆开$n，低头注视着$n。\n",
        "只见$N一挥双手，$n已经出现在$N手中。\n",
});

string *end_msg=({
        "只见$N对着大家深深一揖，收起$n。\n",
        "只见$N抱起$n，抬起头来对着大家微微一笑。\n",
        "$N收起$n，顺手轻轻拨动了一下琴弦。\n",
        "$N面对大家，收起$n，低头注视着$n。\n",
        "只见$N一挥双手，$n便已经消失了。\n",
});

string long()
{
        return query("long")+
                "\nplay：弹奏\n"+
                "stop：停止\n"+
                "list：列表\n";
}

void init()
{
        add_action("do_play", "play");
        add_action("do_halt", "stop");
        add_action("do_list", "list");
}

int do_halt()
{
        object me=this_player();

        if (find_call_out("play_stage") < 0) 
                return notify_fail("你并没有在演奏呀？\n");

        me->delete_temp("playing");
        message_vision(HIM"\n$N发现大家一脸痛苦的表情，尴尬地咳嗽了两声，停下了噪音。\n"NOR, me);
        remove_call_out("play_stage");
        return 1;
}

int do_play(string arg)
{
        object me=this_player();
        object ob=this_object();
        mapping song;
        string *context,*color;

        if (!arg) return notify_fail("你要表演什么？\n");

        if (!mapp(song=MUSIC_D->query_song(arg)))
                return notify_fail("你要表演的这首曲子在乐曲库里没有。\n");

        if (me->query_temp("playing"))
                return notify_fail("你不是正在演奏"+me->query_temp("playing")+"吗？\n");

        if (me->is_busy())
                return notify_fail("你正忙着呢，等会儿再表演吧。\n");

        else {
                message_vision(HIM+start_msg[random(sizeof(start_msg))]+NOR,me,ob);
                message_vision(HIG"然后，$N便演奏起"+song["author"]+"的《"+song["name"]+"》来。\n\n"NOR,me);

                context=explode(song["song"],"\n");
                color=song["color"];

                message_vision(color[random(sizeof(color))]+"\t   《"+song["name"]+"》——"+song["author"]+"\n\n"+NOR,me);
                call_out("play_stage",1,me,0,context,color);
                me->set_temp("playing",song["author"]+"的《"+song["name"]+"》");
                me->start_busy(1);
                return 1;
        }
}

void play_stage(object me,int i,string *context,string *color)
{
        if (i<sizeof(context)) {
                message_vision(color[random(sizeof(color))]+"\t"+context[i]+"\n"+NOR,me);
                call_out("play_stage",1,me,i+1,context,color);
                me->start_busy(1);
                return;
        }
        else {
                message_vision(HIG"\n$N终于演奏完了"+me->query_temp("playing")+"。\n"NOR,me);
                message_vision(HIM+end_msg[random(sizeof(end_msg))]+NOR,me,this_object());
                me->delete_temp("playing");
                return;
        }
}

int do_list(string arg)
{
        object me=this_player();
        mapping songs;
        string msg,*song;
        int i;

        if (me->is_busy())
                return notify_fail("你正忙着呢，等会儿再查阅吧。\n");

        else {
                songs=MUSIC_D->query_songs();
                song=keys(songs);
                song=sort_array(song,1);

                msg="──────────────────────────────\n";
                msg+=HBBLU+HIW+"\t\t     【"MUD_NAME"】音乐曲目表                   \n"NOR;
                msg+="──────────────────────────────\n";

                for (i=0;i<sizeof(songs);i++) {
                        msg+=sprintf(WHT"     %-20s"NOR":%-20s\n",song[i],
                                songs[song[i]]["author"]+"《"+songs[song[i]]["name"]+"》");
                }
                msg+="──────────────────────────────\n";
                msg+=sprintf(HBRED HIW"%59s \n"NOR,"目前共有 "+(i+1)+" 首乐曲可供演奏。");
                msg+="──────────────────────────────";
                me->start_more(msg);
                return 1;
        }
}
