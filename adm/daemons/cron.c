// cron.c
// by mudring

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <command.h>

inherit F_DBASE;
#define CRON_DIR "/d/quest/baoshi/"

string *families = ({
  "乌鸡国", "宝象国", "天竺国", "女儿国",
  "玉华县", "金平府", "五庄观", "祭赛国",
  "钦法国", "比丘国", "朱紫国", "车迟国",
  "高老庄", "江洲国",
});

static int LAST_HARD_DIS;
static int flag = 0;
int set_last_hard_dis();

void check_task();
void auto_clear();
void start_qujing();
void start_baoshi();

void create()
{
    seteuid( ROOT_UID );
    set("channel_id", "三界精灵");
    CHANNEL_D->do_channel( this_object(),
        "sys", "三界精灵已经启动。\n"NOR);
    set_heart_beat(30);
    set_last_hard_dis();
}

int clean_up() { return 1;}
int query_last_hard_dis() {   return LAST_HARD_DIS;  }
int set_last_hard_dis()
{
    LAST_HARD_DIS = time();
    return flag;
}

private void heart_beat()
{
    call_out("check_task", 1);
}

void check_task()
{
    mixed *local;
    object npc;

    local = localtime(time());
    if (!(local[1] % 10))
    {
        call_out("auto_clear",1);
        CRON_DIR "feizei.c"->choose_npc();
    }
    if (!(local[1] % 50))
    {
        CRON_DIR "choose.c"->choose_mpc();
    }
    if (!(local[1] % 79))
    {
        TASK_D->init_dynamic_quest();
        message("system",HIR"\n重新分布部分使命．．．．"
                + HIG" ．．．部分使命分布完毕\n" NOR, users());
    }
    if (flag == 1)
    {
        TASK_D->init_dynamic_quest(1);
        flag = 0; 
        set_last_hard_dis();
        message("system",HIR"\n重新分布所有使命．．．．"
                + HIG" ．．．使命分布完毕\n" NOR,users());
        if (random(4))
            start_qujing();
    }
    if (local[1]==55 || ((int)time()-(int)query_last_hard_dis()) > 4720)
    {
        flag=1;
        message_system( HIR "所有使命将在一分钟后重新分布！！！   "NOR); 
    }
    if (!(local[1] % 65) )
    {
        start_baoshi();
    }
    if (!(local[1] % 41))
      {
        rm("/log/dlog/money");
        "/adm/daemons/ran_moneyd"->move_money();
       }
}

void auto_clear()
{
    int mem;
    object *ob;

    CHANNEL_D->do_channel( this_object(), "sys",
        sprintf("系统自动清除 " + reclaim_objects() + " 个变数。"));

"/cmds/arch/cleanup.c"->main(this_object(), "/d/qujing/wuzhuang/obj/jinjizi.c");
"/cmds/arch/cleanup.c"->main(this_object(), "/d/qujing/wuzhuang/obj/danpan.c");
    ob = filter_array(objects(), (: clonep :));
    mem = sizeof(ob);
    while (mem--)
    if (!environment(ob[mem]) &&
        !interactive(ob[mem]) &&
        !ob[mem]->query_temp("body_ob") &&
        !ob[mem]->query("no_cron"))
    {
        reset_eval_cost();
//        printf("%O\n", ob[mem]);
        CHANNEL_D->do_channel(this_object(), "adm",
            sprintf("%O", ob[mem]));
        destruct(ob[mem]);
        ob -= ({ 0 });
        mem = sizeof(ob);
    }
}

void start_qujing()
{
    int k;
    object ts;

    k = random(sizeof(families));        
    ts = new(CRON_DIR "ts");
    ts->set("target", families[k]);
    ts->invocation(k);
    message_job(HIW"如来佛祖"HIG"：哈哈! 听说有唐三藏师徒已经来到"
                + families[k] + "了，相信不久就会到达灵山了。");
}

void start_baoshi() 
{ 
    object ob;
    object newob;
             
    newob = new(CRON_DIR "baoshi");
    ob = NPC_D->task_npc(); 

    if (newob->move(ob))
    { 
        CHANNEL_D->do_channel( this_object(), "sys", 
            "宝石落到了" + ob->query("name") + "(" + ob->query("id") + ")的身上。");  
        message_job(HIR"奇珍异宝："HIW"突然空中打了个炸雷，一个火球横空出世，拖着一道神光向"
                    + ob->query("place") + "的方向落去！"); 

        if (newob->query("b_lvl") > 14)
            message_job( HIR"奇珍异宝：" + newob->name() + "降临凡间！"); 

    } else
    {
        CHANNEL_D->do_channel( this_object(), "sys", "本次宝石发布失败"); 
    }            
}

