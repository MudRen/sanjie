// ��������

inherit ROOM;
void create ()
{
        set ("short", "����");
        set ("long", @LONG
����һƬ�ż�������,������һƬ����,�ƺ�û�������Ĵ��ڡ�
LONG);

        set("exits", 
        ([ //sizeof() == 4
       "down" : "/d/milin/qy/sc7",    
       "up" : "/d/milin/qy/sc5",    
        ]));

        set("objects", 
        ([ //sizeof() == 1
          "/d/milin/npc/ss6" : 1,
        ]));

        set("no_clean_up", 0);
        set("no_time", 1);
        set("no_quit", 1);
        set("chat_room", 1);
        set("no_upgrade_age", 1);
        set("valid_startroom", 1);
        setup();
        replace_program(ROOM);
}