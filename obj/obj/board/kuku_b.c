//  kuku_b.c 

inherit BULLETIN_BOARD;

void create()
{
        set_name("丝绒屏风", ({ "board" }) ); 
        set("location", "/u/kuku/workroom"); 
        set("board_id", "kuku_b");
        set("long", "一扇浅灰色的丝绒屏风，可以用来记录一些东西。\n" ); 
        setup();
        set("capacity", 300); 
        replace_program(BULLETIN_BOARD); 
}
