// created 4/5/1997 by snowcat
#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit F_AUTOLOAD; 
inherit ITEM;

void create()
{
  set_name(HIG "������" NOR, ({ "biyu xiao","xiao"}));
  set_weight(100);
  set("long",HIG"����С���ñ������ĳ���������һͷ������һ�԰���ĺ�����\n" NOR );
  set("unit", "��");
  setup();
}

init ()
{
  add_action ("do_play", "chui");
}

int do_play (string arg)
{
  object me = this_player();
  object qin = this_object();
  string *msgs = ({
    HIY"$N�����ڴ������ᴵ��һ���������������������ƶ�ȥ��ԶԶ�ƺ������ں͵���
        ���������£�ӭ�继�뿪��
        ��ǽ��Ӱ������������������

\n" NOR ,
    HIR"$N�͵͵ش��˼�����ͻȻ���ͻ��ȴ��һ��������ˡ���

    ����������磬�����ĺ�����ʣ���һ��Ů�ڴ��ã��������ڶ��ҳ������ɽ���Ϊԧ��
    �������ӻ��ܣ���י��β��Ϊ��������ͨ��غ�г����ҹ��ӱ���˭��

\n" NOR ,
    HIM"$N�˳�����ָ������һ���������ϵ��ţ�һ������������ϻ��䣬�����ǣ�
        
        ������������������ü��
        �������ʪ����֪�ĺ�˭����

\n" NOR ,
    HIG"$N΢΢������ü����Թ������Զ����ȴ�Ǵ���һ����һ����

        ������ͭ�������ڰ����á�
        ��������Ů����Ū���¹⡣
        �������ȵ���������ױ��
        ױ�պ����������������㡭��

\n" NOR ,
    HIW"$N��������������΢΢һЦ�����������������

        һ������������ϼ��ಢ�� һ�Է۵���������ƫ��ã�
        һ��ԧ���ˮ�����ཻ���� һ�Ի�è����������˶���
        ���˶����飬 �������Ķ�Ӳ�� ������ƫ���Ϲ��㡭��

\n" NOR ,
  });

  if (arg != "xiao")
  {
    tell_object (me,"��ʲô�����أ�\n");
    return 1;
  }

  message_vision (msgs[random(sizeof(msgs))],me);
  return 1;
}

int query_autoload() { return 1; }