// nancheng_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("门派均衡讨论区", ({ "board" }) );
        set("location", "/d/wiz/tanake");
        set("board_id", "junheng");
	set("long",	"这是一个供人留言记事的留言板。\n" );
	setup();
        set("capacity", 500);
	replace_program(BULLETIN_BOARD);
}
