//NPC  /d/city/npc/kaoguan.c
//Created by waiwai@2000/08/20

#include <command.h>
inherit NPC;
#include <ts.h>
#include <localtime.h>
int give_quest(object ob);
int now_time();

void create()
{
	set_name("范举人",({"fan juren","fan","juren","fanjuren"}));
	set("age",56);
	set("str",23);
	set("ts_ok",1);
	set("degree",WHT"举人"NOR);

	set("inquiry",([
		"here":"这里是童生考场，想考试的话，最好看看墙上的告示(gaoshi).\n",
		"考试":"看墙上的告示吧。\n",
	]));
	setup();
}

void init()
{
	::init();
	add_action("do_exam","exam");
	add_action("do_answer","answer");
}

int do_exam()
{
	object ob;
	int level;
	string rank;

	ob=this_player();
	if (!ob||environment(ob)!=environment()) return 0;

	if (ob->query_skill("literate",1)<10) 
		return notify_fail("主考官摇头道：等你读书写字进步些再来吧.\n");

	if ((int)ob->query("ts_ok")>1) 
		return notify_fail("主考官瞄了你一眼道：你已经考过了！！\n");

	if ((int)ob->query("office_number")>1) 
		return notify_fail("主考官瞄了你一眼道：你已经考过了！！\n");

	level=ob->query("office_number");

	if (level)  {
	       rank=ob->query("degree");
       	if (level>query("ts_ok"))
		       return notify_fail(HIG"主考官惊讶道："+rank+HIG"大人，不要开玩笑了！！\n"NOR);
	       return notify_fail(HIY"主考官惊讶道：你已是"+rank+HIY"，还考什么童生呢?\n"NOR);
        }

	if (now_time()==ob->query("ts/last_check")) 
		return notify_fail("主考官瞄了你一眼道：明天再来吧！！\n");

	if (ob->query_temp("ts/answer"))
		return notify_fail("主考官指着你道：问题还没回答吧!\n");

	message_vision("$N向$n恭敬地施礼：请主考大人出题!\n",ob,this_object());

	give_quest(ob);
	return 1;
}

int give_quest(object ob)
{ 
	mapping quest;
	string *text,word,pass;
	int i;
	quest=exam[random(sizeof(exam))];
	text=quest["text"];
	i=random(sizeof(text));

	if (random(2)==1) {
		if (i!=0) {  word=text[i-1]; pass="前一句";}
		      else {word=quest["author"];pass="作者";}
      } else { 
	if (i!=(sizeof(text)-1)) { word=text[i+1]; pass="后一句"; }
        else { word=quest["title"]; pass="题目"; }
      }
	ob->set_temp("ts/answer",word);
	command("say ["+text[i]+"... ...],请问"+pass+"是？\n");
	return 1;
}

int do_answer(string arg)
{
	object ob=this_player();

	if ((int)ob->query("office_number")>1) 
		return notify_fail("主考官说道：一边玩去！\n");

	if(!ob->query_temp("ts/answer") && !wizardp(ob) ) 
		return notify_fail("主考官笑道：我可还没出题，你胡说些什么?\n");

	message_vision("$N沉思良久，道：此题答案可是["+arg+"]?\n",ob);

	if( arg ==ob->query_temp("ts/answer") ) {
		command("nod");
	message("shout",
	HIY"\n┋"HIR"童生及第"HIY"┋"HIR"范举人：恭喜"+log_id(ob)+"顺利考取童生。\n"NOR,users());

		ob->set("ts_ok",2);
		ob->set("degree","童生");
		ob->add("office_number",1);
		ob->delete_temp("ts");
		ob->delete("ts/last_check");
	log_file("ts.rc",
	HIR+log_id(ob)+NOR WHT" 于["+BJTIME_CMD->chinese_time(1, ctime(time()))+NOR WHT"] "HIY"考取童生。\n"NOR);
	return 1;
	}

	command("shake");
	command("say 不要灰心，明天再来。\n");
	ob->delete_temp("ts");
	if( !wizardp(ob) )
	ob->set("ts/last_check",now_time());
	return 1;
}

int now_time()
{
	int i;
	object ob=this_player();
	mixed *local;
	local = localtime(time()*60);
	i=local[LT_MDAY] + (local[LT_HOUR]>23? 1 : 0);
	return i;
}
  
