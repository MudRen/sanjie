// create by snowcat.c 12/8/1997

inherit ROOM;

void create ()
{
  set ("short", "��·");
  set ("long", @LONG

��ƮƮ����������һ�ۼ�Ŀ��ȥֻ��ũ������ģ�����С����
������ǵ�㡣�����Ǻ�ʵ������·���������﹡����ʱ����
����Ϫˮ�ڹ���������

LONG);

  set("exits", ([
        "northwest"   : __DIR__"cunlu8",
        "southeast"   : "/d/qujing/yuhua/xiaolu3",
      ]));
  set("outdoors", __DIR__);

  setup();
}


