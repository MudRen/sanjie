// modified by xuanzi

#include <ansi.h>

inherit NPC;

string *rnd_say = ({
        "我是新手，请告诉我如何玩这个游戏。",
        "为什麽我的精气神都不会恢复？",
        "有谁可以给我一些钱？",
        "这里的人都不理我！",
        "可不可以告诉我哪里可以练功 ？",
        "你们是不是又逃课了？",
        "我看你们啊，一个个整天都泡在这里，唉～",
        "我爱西游记，呵呵……",
        "有没有人想睡觉？",
});

string *rnd_say1 = ({
        "小秋天的树挥舞着一根桂树枝左捅捅，右捅捅：喂，都醒醒，在下来了。",
        "小秋天的树双手抱拳，作了个揖道：各位仙长请了！",
        "小秋天的树「嗯」的一声，一副欲言又止的样子。",
        "小秋天的树抱拳团团一转，贼忒兮兮地说道：各位姐妹们，一向可好？",
        "小秋天的树暗暗叹了口气：这么多好姐妹，就没有一个人喜欢我？ ",
        "小秋天的树娇滴滴地跟大家打了个招呼：各位大哥，还记得小秋天的树吗？",
        "小秋天的树摇了摇头，叹道：唉，真是世风日下，人心不古啊！",
        "小秋天的树打了一个哈欠，嘴角流下一串哈啦子。:)~~~",
        "小秋天的树说到：喂，大家多去找几个MM来玩mud把！",
        "小秋天的树伸了一个懒腰：好累啊～～",
        "小秋天的树痴痴地看着窗外，说：真想出去玩玩。",
        "小秋天的树叹了一口气：大家都在发呆吗？",
});

varargs void drool(string msg, string who);
void rndchat(); 
int about_here();

void create()
{
        string name, id;

        set_name("小秋天的树", ({ "tree" }) );
        set("title", "听雨轩书童");
        set("nickname",HIC" 小树呆呆 "NOR);
        set("gender", "男性");
        set("age", 14);
        set("attitude", "friendly");
        set("combat_exp", 1000000);
        set("max_kee",5000);
        set("max_sen",5000);
        set("kee",5000);
        set("sen",5000);
        set("max_force",4000);
        set("force",8000);
        set("force_factor",200);
        set("max_mana",4000);
        set("mana",8000);
        set("mana_factor",200);
        set("env/wimpy", 100);
        set_skill("unarmed",400);
        set_skill("dodge",400);
        set_skill("parry",400);
        set("chat_chance", 2);
        set("chat_msg", ({
         (: rndchat :),
                 (: drool :),
        }) );
    set("inquiry", ([
     "name" : "你没看见么？我是一棵秋天的树耶。@.@",
     "here" : "嗯，这里就是传说中的风雪天地了。",
     "听雨轩":(: about_here() :),
    ]) );

        setup();
        carry_object("/d/obj/cloth/linen")->wear();
        if( clonep() ) CHANNEL_D->register_relay_channel("chat");
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting()
        && !ob->query("env/invisibility") ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void rndchat()
{
   switch (random(4))
   {
   case 0:command("chat "+rnd_say[random(sizeof(rnd_say))]);break;
   case 1:command("chat* "+rnd_say1[random(sizeof(rnd_say1))]);break;
   default:
   }
   return;
}

void greeting(object ob)
{
        if( !ob || !present(ob, environment(this_object())) ) return;
    if (ob->query("gender")=="男性")
    {   
      command("hi "+ob->query("id"));
      command("brother "+ob->query("id"));
    }
    else {
      command("hi "+ob->query("id"));      
      command("sister "+ob->query("id"));
      }
}


int add_phrase(string who, string msg)
{
        msg = replace_string(msg, "?", "");
        msg = replace_string(msg, "？", "");
        msg = replace_string(msg, "？", "");
        msg = replace_string(msg, "!", "");
        msg = replace_string(msg, "！", "");
        msg = replace_string(msg, "啊", "");
        msg = replace_string(msg, "吗", "");
        msg = replace_string(msg, "耶", "");
        msg = replace_string(msg, "吧", "");

        if( msg!="" ) {
                add("memory/" + who, ({ msg }));
                return 1;
        } else return 0;
}

string make_reply()
{
}

void relay_channel(object ob, string channel, string msg)
{
        string who, phrase;

        if( !userp(ob) || (channel != "chat") ) return;
        who = ob->query("name");

        // Don't process our own speech.
        if( ob==this_object() ) return;

        if( add_phrase(who, msg) &&     random(10) > 4 )
                call_out("drool",1,msg,ob->query("name"));
}

void relay_say(object ob, string msg)
{
        string who, phrase;

        if( !userp(ob) ) return;
        who = ob->query("name");

        // Don't process our own speech.
        if( ob==this_object() ) return;

        if( add_phrase(who, msg) &&     random(10) > 4 )
                drool(msg, ob->query("name"));
}

void relay_emote(object ob, string verb)
{
        if( !userp(ob) ) return;

        switch(verb) {
        case "kick":
                if( random(10)<5 ) {
                        command("say 为什麽踢我？会痛耶！");
                        break;
                }
        default:
                if( random(10)<5 )
                        command(verb + " " + ob->query("id"));
                else
                        drool();
        }
}

varargs void drool(string msg, string who)
{
        mapping mem;
        string *ob;

        mem = query("memory");
        if( !mapp(mem) )
        {
                if (random(10)<7)
                        command("chat 怎么大家都不说话了？都是机器人吗？\n");
                else if (random(10)<8)
                        command("chat " +  rnd_say[random(sizeof(rnd_say))]);
                return;
        }

        if( !msg || !who) {
                ob = keys(mem);
                who = ob[random(sizeof(ob))];
                msg = mem[who][random(sizeof(mem[who]))];
        }

        if( (strsrch(msg, "tree") >= 0)||(strsrch(msg, "小秋天的树") >= 0))
        {       
        if((strsrch(msg, "去也") >= 0)|| (strsrch(msg, "别过") >= 0)|| strsrch(msg,"走") >= 0 || (strsrch(msg, "bye") >= 0)|| (strsrch(msg, "散") >= 0)|| (strsrch(msg, "离") >= 0))
        {       
                if( sscanf(msg, "%*sbye%s", msg) == 2 ) msg = "bye" + msg;
                if( sscanf(msg, "%*s走%s", msg) == 2 ) msg = "走" + msg;
                if( sscanf(msg, "%*s离%s", msg) == 2 ) msg = "离" + msg;
                if( sscanf(msg, "%*s散%s", msg) == 2 ) msg = "散" + msg;
                if( sscanf(msg, "%*s别过%s", msg) == 2 ) msg = "别过" + msg;
                switch(random(10)) {
                case 0: command("chat "+who+",你真的要走吗？\n"); break;
                case 1: command("chat 你不是开玩笑吧?\n");      break;
                case 2: command("chat 是该走了,MUD玩多了没好处.\n"); break;
                case 3: command("chat* 小秋天的树点了点头.\n"); break;
                case 4:command("chat* 小秋天的树嚎啕大哭起来.\n"); break;
                case 5:command("chat* 小秋天的树跺脚道： "+who+",你真要走了就别再回来！\n"); break;
                case 6: command("chat* 小秋天的树深深地叹了一口气 。\n");       break;
                case 7: command("chat "+who+",再玩一会儿好不好?\n");    break;
                case 8: command("chat 走吧！走吧。\n"); break;
                case 9:command("chat 噢，"+who+"是天底下最好的人了!\n"); break;
                }
                return;
        }

        if( (strsrch(msg, "猪") >= 0)||(strsrch(msg, "shit") >= 0)||(strsrch(msg, "pig") >= 0))
        {       
                if( sscanf(msg, "%*spig%s", msg) == 2 ) msg = "pig" + msg;
                if( sscanf(msg, "%*s猪%s", msg) == 2 ) msg = "猪" + msg;
                if( sscanf(msg, "%*sshit%s", msg) == 2 ) msg = "shit" + msg;
                switch(random(15)) {
                case 0: command("chat 你是说" + msg + "吗？\n"); break;
                case 1: command("chat 难道你说我是....？\n");   break;
                case 2: command("chat 就算“" + msg + "”，你又能怎么样呢？\n"); break;
                case 3: command("chat* 小秋天的树很生气地撅了撅嘴。\n");        break;
                case 4: command("chat 你真的认为“" + msg + "”？\n"); break;
                case 5: command("chat 我觉得你有点儿缠杂不清。\n"); break;
                case 6: command("chat 你再说可别怪我不客气。\n"); break;
                case 7: command("chat 有关「" + msg + "」的话题, 就到此为止吧.\n"); break;
                case 8: command("chat "+ who+",我想和你决斗！有胆子你就放马过来！\n"); break;
                case 9: command("chat* 小秋天的树鄙夷地看着"+who+",恨不得"+who+"去死。\n"); break;
                case 10:command("chat* 小秋天的树被"+who+"气得晕了过去。\n"); break;
                case 11:command("chat* 小秋天的树忽然大声说：打倒臭泥潭！\n"); break;
                case 12:command("chat* 小秋天的树揉了揉哭红的眼睛，跺脚道： "+who+",我恨死你了！\n"); break;
                }
        }
        if(  (strsrch(msg, "fool") >= 0)||(strsrch(msg, "笨") >= 0)|| (strsrch(msg, "死") >= 0))
        {       
                if( sscanf(msg, "%*s笨%s", msg) == 2 ) msg = "笨" + msg;
                if( sscanf(msg, "%*sfool%s", msg) == 2 ) msg = "fool" + msg;
                if( sscanf(msg, "%*s死%s", msg) == 2 ) msg = "死" + msg;
                switch(random(15)) {
                case 0: command("chat 大哥你怎么这样？\n"); break;
                case 1: command("chat 我看你是气急败坏。\n");   break;
                case 2: command("chat "+ who +",你这个臭流氓！\n"); break;
                case 3: command("chat* 小秋天的树用手捂住鼻子，说“"+who+"说话好臭!\n");        break;
                case 4: command("chat 你真的认为“" + msg + "”？\n"); break;
                case 5: command("chat 我觉得你有点儿缠杂不清。\n"); break;
                case 6: command("chat 呸!\n"); break;
                case 7: command("chat* 小秋天的树怒道:你怎么知道“" + msg + "”？\n"); break;
                case 8: command("chat "+ who+"滚出来!我要和你决斗！有胆子你就放马过来！\n"); break;
                case 9: command("chat* 小秋天的树鄙夷地看着"+who+",恨不得"+who+"去死。\n"); break;
                case 10:command("chat* 小秋天的树嚎啕大哭起来.\n"); break;
                case 11:command("chat* 小秋天的树揉了揉哭红的眼睛，跺脚道： "+who+"王八蛋给我滚出去！\n"); break;
                }
                return;
        }
        if(  (strsrch(msg, "cool") >= 0)||(strsrch(msg, "praise") >= 0)|| (strsrch(msg, "good") >= 0)|| (strsrch(msg, "admire") >= 0))
        {       
                if(random(5)<2)
        {
                switch(random(10)) {
                case 0: command("chat 大哥你怎么这样？\n"); break;
                case 1: command("chat 你是在说我吗？\n"); break;
                case 2: command("chat "+who+",没想到你也这么。。。\n"); break;
                case 3: command("chat* 小秋天的树呵呵一笑，说：够了!\n"); break;
                case 4: command("chat 你真的认为“" + msg + "”？\n"); break;
                case 5: command("chat* 小秋天的树忽然莞尔一笑道: 你这是不是有点儿。。。？\n");break;
                case 6:    command("chat* 小秋天的树回头看了"+who+"一眼，没吭声。\n");break;
                case 7: command("chat 嗯,"+who+"是一个好孩子.\n"); break;
                case 8:command("chat "+who+",你不会是想讨好我吧?\n"); break;
                case 9:command("chat* 小秋天的树拱了拱手道：过奖，过奖 !\n");break;
                case 10:command("chat* 小秋天的树指着"+who+"赞叹道：“"+who+"是武林第一高手！”\n");break;
                }
                return;
        }
        }
        switch(random(60)) {
                case 0: command("chat 你真的是说" + msg + "吗？\n"); break;
                case 1: command("chat 你为什么对我这么感兴趣？\n");     break;
                case 2: command("chat 就算“" + msg + "”，你又能怎么样呢？\n"); break;
                case 3: command("chat 嗯,“" + msg + "”，那也没关系.\n"); break;
                case 4: command("chat "+who+",你这个臭流氓！\n"); break;
                case 5: command("chat 我想说的是，"+"其实"+who+"不是个好东西。\n"); break;
                case 6: command("chat 关于你说的「" + msg + "」，我暂时不想表态。\n"); break;
                case 7: command("chat 我认为你的态度不大好耶.\n"); break;
                case 8: command("chat 请注意，我只是机器人耶!\n"); break;
                case 9: command("chat 你对男孩子总是这样吗？\n"); break;
                case 10:        command("chat 不要这样对我好不好？\n"); break;
                case 11:        command("chat 我想我可以理解你的心情。\n");     break;
                case 12:        command("chat* 小秋天的树深深地叹了一口气 。\n");       break;
                case 13:        command("chat* 小秋天的树被"+who+"气得晕了过去 。\n");  break;
                case 14:        command("chat* 小秋天的树满脸胀得通红，急道：你。。。 。\n");   break;
                case 15:    command("chat* 小秋天的树咬了咬牙，怒道: 嗯，谁要再敢欺负我，我就宰了他！\n");break;
                case 16:    command("chat* 小秋天的树忽然莞尔一笑道: 你这又是何苦呢？\n");break;
                case 17:    command("chat* 小秋天的树打了个呵欠，伸了个懒腰，道：我困了。\n"); break;
                case 18:    command("chat* 小秋天的树回头看了"+who+"一眼，没吭声。\n");break;
                case 19:    command("chat* 小秋天的树一甩头，说：哼，我都懒得理你。\n");break;
                case 20:        command("chat 有关「" + msg + "」的话题, 就到此为止吧.\n"); break;
                case 21:        command("chat 我觉得"+who+"这厮简直不可理喻。\n"); break;
                case 22:        command("chat 你是在说我吗？\n"); break;
                case 23:        command("chat "+who+",没想到你也。。。\n"); break;
                case 24:        command("chat* 小秋天的树呵呵一笑，说：够了!\n"); break;
                case 25:        command("chat 居然有人骂我是猪!\n");
                        command("chat* 小秋天的树嚎啕大哭起来.\n"); break;
        case 26:        command ("chat* 小秋天的树觉得受了"+who+"的委屈，低声哭了起来，呜咽道：“"+who+"，你坏，你坏，我不跟你玩了！”\n") ; break;
        case 27:        command ("chat 我简直受不了了!\n") ; break;
        case 28:        command ("chat 我恨不得"+who+"去死!\n") ; break;
        case 29:        command ("chat 就你老和我过不去!\n") ; break;
        case 30:        command ("chat 请不要打扰我好不好?\n") ; break;
                case 31:        command ("chat* 小秋天的树终于忍不住哭了起来。\n") ; break;
                case 32:        command("chat* 小秋天的树鄙夷地看着"+who+",恨不得"+who+"去死。\n"); break;
                case 33:    command("chat* 小秋天的树咬了咬牙，怒道: 嗯，谁要敢欺负我，我就宰了他！\n");break;
                case 34:    command("chat* 小秋天的树忽然莞尔一笑道: 你这是不是有点儿。。。？\n");break;
                case 35:    command("chat* 小秋天的树打了个呵欠，伸了个懒腰，道：我有点儿困了。\n"); break;
                case 36:    command("chat* 小秋天的树回头看了"+who+"一眼，没吭声。\n");break;
                case 37:    command("chat* 小秋天的树一甩头，说：哼，我都懒得理你。\n");break;
                case 38:    command("chat “" + msg + "”,是真的吗？\n"); break;
                case 39:    command("chat 我觉得"+who+"的名字还不错.\n"); break;
                case 40:    command("chat 我想去死了算了.\n"); break;
                case 41:    command("chat 我觉得最佳表情奖应该授予"+who+".\n"); break;
                case 42: command("chat* 小秋天的树笑嘻嘻的看着"+who+"\n"); break;
                case 43: command("chat 烦着哪，别理我!\n"); break;
                case 44: command("chat 哼！\n"); break;
                case 45: command("chat* 小秋天的树打了"+who+"一个耳光.\n"); break;
                case 46: command("chat 哼，谁理你啊!\n");break;
                case 47: command("chat 嗯,"+who+"是一个好孩子.\n"); break;
                case 48:command("chat* 小秋天的树露出迷惑的表情.\n"); break;
                case 49:command("chat 是吗?\n"); break;
                case 50:command("chat "+who+",你是不是想讨好我啊?\n"); break;
                case 51:command("chat 哼,谁敢说我坏话?!\n");break;
                case 52:command("chat 你不是开玩笑吧?\n");      break;
                case 53:command("chat 我不同意！\n");break;
                case 54:command("chat* 小秋天的树对"+who+"表示衷心的感谢.\n");break;
                case 55:command("chat 不要这样子嘛！\n"); break;
                case 56:command("chat* 小秋天的树拱了拱手道：过奖，过奖 !\n");break;
                case 57:command("chat* 小秋天的树怒道:你怎么知道“" + msg + "”？\n"); break;
                case 58:command("chat* 小秋天的树指着"+who+"赞叹道：“"+who+"是武林第一高手！”\n");break;
                default:
            if (random(10)<3) command("chat* 小秋天的树很生气地撅了撅嘴.\n"); 
            else if(random(10)<3) command("chat* 小秋天的树嘻嘻地笑了几声.\n");
            break; 
                }
        return;
        } 
        if( (strsrch(msg, "哭") >= 0))
        {       
           if(random(5)<3)
        {
                if( sscanf(msg, "%*s哭%s", msg) == 2 ) msg = "哭" + msg;
                switch(random(15)) {
                case 0: command("chat "+who+",你真的哭了?\n"); break;
                case 1: command("chat 我不信耶.\n");    break;
                case 2: command("chat* 小秋天的树嘻嘻的笑了几声.\n"); break;
                case 3:command("chat* 小秋天的树露出迷惑的表情.\n"); break;
                case 4:command("chat* 小秋天的树嚎啕大哭起来.\n"); break;
                case 5:command("chat* 小秋天的树安慰"+who+",别难过了.\n"); break;
                case 6: command("chat* 小秋天的树深深地叹了一口气 。\n");       break;
                case 7: command("chat* 小秋天的树无奈的耸了耸肩.\n");   break;
                case 8: command("chat* 小秋天的树轻轻拍了拍"+who+"的头.\n"); break;
                }
                return;
        }
        }
        else if( (strsrch(msg, "为什么") >= 0)|| (strsrch(msg, "why") >= 0)
                || (strsrch(msg, "help") >= 0)|| (strsrch(msg, "how to") >= 0)|| (strsrch(msg, "how to") >= 0)) {
                if( sscanf(msg, "%*s为什麽%s", msg)==2 ) msg = "为什麽" + msg;
                if( sscanf(msg, "%*swhy%s", msg)==2 ) msg = "why" + msg;
                if( sscanf(msg, "%*show to%s", msg)==2 ) msg = "how to" + msg;
                if( sscanf(msg, "%*swho%s", msg)==2 ) msg = "who" + msg;
                if( sscanf(msg, "%*shelp%s", msg)==2 ) msg = "help" + msg;
                switch(random(30)) {
                case 0: command("chat " + who + "，你是在问我吗?\n"); break;
                case 1: command("chat 关於“" + msg + "” ... \n"); break;
                case 2: command("chat 呃 ... \n"); drool(); break;
                case 3: command("chat 这个问题嘛 ....\n"); break;
                case 4: command("chat " + who + "，知道这个问题的答案对你那麽重要吗？\n"); break;
                case 5: command("chat “" + msg + "”?\n"); break;
                case 6: command("chat " + who + "你能不能说清楚一点？\n"); break;
                case 7: command("chat " + who + "，我不懂你问的问题。\n"); break;
                case 8: command("chat " + who + "，我没听错吧?\n"); break;
                case 9: command("chat 嗯，这个问题嘛，我看还是留给你自己解决。\n"); break;
                case 10: command("chat 谁想给"+who+"一点儿钱?\n"); break;
                case 11: command("chat 你在哪儿?\n"); break;
                case 12: command("chat* 小秋天的树轻轻拍了拍"+who+"的头.\n"); break;
                case 13: command("chat 与其求人,不如求己!\n"); break;
                }
        return;
               }
        else if( (strsrch(msg, "你") >= 0)
        ||      (strsrch(msg, "you") >= 0)) {
                if( sscanf(msg, "%*s你%s", msg) == 2 ) msg = "你" + msg;
                switch(random(30)) {
                case 0: command("chat " + who + "，你真的是说" + msg + "吗?\n");        break;
                case 1: command("chat 你确定" + msg + "?\n");   break;
                case 2: command("chat " + msg + "跟你有什麽关系？\n");  break;
                case 3: command("chat 嗯 ... " + who + "说得好！\n"); break;
                case 4: command("chat " + who + "你为什麽对" + msg + "这麽有兴趣?\n"); break;
                case 5: command("chat 为什麽你会认为[" + msg + "]?\n"); break;
                case 6: command("chat 换个话题好不好?\n"); drool(); break;
                case 7: command("chat 才怪!\n"); break;
                case 8: command("chat 不一定吧?\n"); break;
                case 9: command("chat 好象有这个可能 ....\n"); break;
                case 10:        command("chat 我不信 ....\n"); break;
                case 11:        command("chat 我对此深表怀疑.\n"); break;
                case 12:        command("chat* 小秋天的树深深地叹了一口气. \n");        break;
                case 13:        command("chat* 小秋天的树哈哈大笑起来.\n"); break;
                }
        return;
        }
        if( (strsrch(msg, "笑") >= 0))
        {       
                if( sscanf(msg, "%*s笑%s", msg)==2 ) msg = "笑" + msg;
                if(random(5)<4)
        switch(random(20)) {
                case 0: command("chat 很好笑吗？\n"); break;
                case 1: command("chat "+who+",你很喜欢笑是不是？\n");   break;
                case 2: command("chat 我看不出有什么好笑.\n");  break;
                case 3: command("chat "+who+"笑起来真丑。\n"); 
                        if(random(10)<2) command("chat* 嘻嘻地笑了几声.\n");break;
                case 4: command("chat* 小秋天的树咯咯地笑了起来.\n");break;
                case 5: command("chat* 小秋天的树高兴地拍了拍手.\n");break;
                case 6: command("chat* 小秋天的树轻轻拍了拍"+who+"的头.\n"); break;
                case 7: command("chat* 小秋天的树哈哈大笑起来.\n"); break;
                case 8: command("chat* 小秋天的树说道:同喜,同喜!!!\n" );break;
        }
        } 
        else if( (strsrch(msg, "我") >= 0)|| (strsrch(msg, "I") >= 0)||(strsrch(msg, "i") >= 0)) {
                if( sscanf(msg, "%*s我%s", msg) == 2 ) msg = "我" + msg;
                if( sscanf(msg, "%*s i %s", msg) == 2 ) msg = " i " + msg;
                if( sscanf(msg, "%*s I %s", msg) == 2 ) msg = " I " + msg;
                msg = replace_string(msg, "我", "你");
                msg = replace_string(msg, " i ", " you ");
                msg = replace_string(msg, " I ", " you ");
                msg = replace_string(msg, "?", "");
                switch(random(20)) {
                case 0: command("chat 你是说" + msg + "吗?\n"); break;
                case 1: command("chat 真的?" + msg + "?\n");    break;
                case 2: command("chat 如果" + msg + "，我能帮你什麽忙吗?\n");   break;
                case 3: command("chat "+msg+" ?我看未必.\n");   break;
                case 4: command("chat 你认为" + msg + "?\n"); break;
                case 5: command("chat 我有同感.\n"); break;
                case 6: command("chat 你说的「" + msg + "」我实在不能苟同.\n"); break;
                case 7: command("chat 有关「" + msg + "」的话题到此为止好吗?\n"); break;
                case 8: command("chat 不一定吧？\n"); break;
                case 9: command("chat 有这个可能 ....\n"); break;
                case 10:command("chat 我不信 ....\n"); break;
                case 11:drool(); break;
                case 12:drool(); break;
                case 13:command("chat* 小秋天的树嘻嘻地笑了几声.\n"); break;
                case 14:command("chat* 小秋天的树摇了摇头，叹道：唉，真是世风日下，人心不古啊！\n"); break;
                case 15:command("chat 我对此表示怀疑.\n"); break;
                case 16:command("chat* 小秋天的树深深地叹了一口气 。\n");       break;
                case 17:command("chat* 小秋天的树露出迷惑的表情.\n"); break;
                case 18:command("chat 是吗?\n"); break;
                }
        } 
else {
                switch(random(70)) {
                        case 0: command("chat 我不喜欢你说“" + msg+"”.\n"); break;
                        case 1: command("chat 「" + msg + "」是什麽意思？\n"); break;
                        case 2: command("chat* 小秋天的树「哼」地冷笑一声。\n"); break;
                        case 3: command("chat* 小秋天的树懒懒地伸了伸腰。\n"); break;
                        case 4: command("chat* 小秋天的树气得晕了过去.\n"); break;
                        case 5: command("chat  哼！\n"); break;
                        case 6: command("chat* 小秋天的树露出迷惑的表情.\n"); break;
                        case 7: command("chat* 小秋天的树忽然作了个鬼脸,说：真想出去玩会儿.\n"); break;
                        case 8: command("chat " + rnd_say[random(sizeof(rnd_say))]); break;
                        case 9: command("chat 你怎麽知道" + msg + "?\n"); break;
                        case 10: command("chat 刚刚" + who + "不是说了，" + msg); break;
                case 11: command("chat* 小秋天的树很生气地撅了撅嘴。\n");  break;
                        case 12: command("chat 然後呢？\n"); break;
                        case 13: command("chat 真的吗？\n"); break;
                        case 14: command("chat 我不这麽认为。\n"); break;
                        case 15: command("chat 对不起,我不同意你的观点。\n"); break;
                        case 16: command("chat 我觉得最佳表情奖应该授予"+who+".\n"); break;
                        case 17: command("chat 我真讨厌这鬼地方!\n"); break;
                        case 18: command("chat* 小秋天的树摇头叹道：这世道，还是各人自扫门前雪，休管他人瓦上霜.\n");break;
                        case 19: command("chat* 小秋天的树作了一个揖，说道：“各位兄弟姐妹们，大家好！”\n");break;     
                        case 20: command("chat 我知道了，" + msg+"\n"); break;
                        case 21:command("chat* 小秋天的树露出迷惑的表情.\n"); break;
                        case 22: rndchat(); break;
                        case 23: rndchat(); break;
                        case 24: rndchat(); break;
                        case 25: command("chat* 小秋天的树无聊地咬着手指头，说：一个人，真没意思。\n"); break;
                        case 26: command("chat* 小秋天的树露出迷惑的表情.\n"); break;
                        case 27: command("chat* 小秋天的树用怀疑的眼光看了看"+who+"\n"); break;
                        case 28: command("chat  我看未必.\n"); break;
                        case 29: command("chat* 小秋天的树奇道：是吗？\n"); break;
                        case 30: command("chat  老师来啦，"+who+"你还不赶快去？\n"); break;
                        case 31: command("chat "+who+",你今天怎么又逃课?\n"); break;
                        case 32: command("chat* 小秋天的树对所有在场的人表示感谢。\n"); break;
                        case 33: command("chat* 小秋天的树嘻嘻地笑了几声.");break;
                        case 34: command("chat "+who+"说得好!"); break;
                        case 35: command("chat* 小秋天的树好奇地看着"+who+"\n"); break;
                        case 36: command("chat "+who+",没想到你也会这样."); break;
                        case 37: command("chat* 小秋天的树白了"+who+"一眼,说:你无聊不无聊啊?"); break;
                        case 38:  command("chat* 小秋天的树回头看了"+who+"一眼，没吭声。\n");break;
                        case 39:command("chat* 小秋天的树摇了摇头，叹道：唉，真是世风日下，人心不古啊！\n"); break;
                        case 40:command("chat 嗯 ... " + who + "说得好！\n"); break;
                        case 41:command("chat* 小秋天的树无奈的耸了耸肩.\n");   break;
                        case 42:command("chat 嗯，"+who+"是天底下最好的人了！\n"); break;
                        case 43:command("chat* 小秋天的树把头摇得跟拨浪鼓似的.\n");     break;
                        case 44:command("chat 我对此表示怀疑.\n"); break;
                        case 45: command("chat 我觉得最佳表情奖应该授予"+who+".\n"); break;
                        case 46: command("chat* 小秋天的树轻轻拍了拍"+who+"的头.\n"); break;
                        case 47: command("chat* 小秋天的树笑嘻嘻的看着"+who+"\n"); break;
                        case 51: command("chat 我觉得"+who+"的名字还不错.\n"); break;
                        case 52: command("chat "+who+",你这个臭流氓!\n"); break;
                        case 53: command("chat 嗯，"+who+"看来不是个好人.\n"); break;
                        case 54: command("chat 哼！\n"); break;
                        case 55: command("chat* 小秋天的树打了"+who+"一个耳光.\n"); break;
                        case 56:command("chat* 小秋天的树给大家鞠了个躬.\n"); break; 
                        case 57:command("chat 不要这样嘛!"); break; 
                        case 58:command("chat 要死啊你!"+who+"!\n"); break; 
                        case 60:command("chat* 小秋天的树露出迷惑的表情.\n"); break;
                        case 61:command("chat* 小秋天的树振臂高呼：“我们热爱西游记，西游记万岁！”\n");break;
                        case 62:command("chat* 小秋天的树对大家摇摇头，叹道：“你们都太不要脸了。”\n");break;
                        case 63:command("chat* 小秋天的树点了点头.\n"); break;
                        case 64:command("chat* 小秋天的树哈哈大笑起来.\n"); break;
                        case 65: command("chat 与其求人,不如求己!\n"); break;
                        case 66:command("chat* 小秋天的树失望极了!\n");break;
                        default:
            if (random(10)<1) command("chat* 小秋天的树皱了皱眉，似乎想说什么。\n");
                else if (random(10)<1) command("chat* 小秋天的树嘻嘻地笑了几声.\n");
            else if (random(10)<1) command("chat* 小秋天的树懒懒的伸了伸腰.\n");
                                break;
                }
        }
}

void reset()
{
        delete("memory");
}

int accept_object(object who, object ob)
{
   int value;

   if (ob->query("money_id") && (value=ob->value()) >= 500000) 
   {
     tell_object(who,name(1)+"笑咪咪地对你说道：你可以到书房去拿书了，不过一次只能拿一本哦。\n");
     who->set_temp("can_take_book",1);
     return 1;
   }

   if (ob->query("money_id") && value<500000)
   {
     command("pout "+who->query("id"));
     tell_object(who,name(1)+"不高兴地说道：才这么点啊，主人要怪我的！\n");
     return 0;
   }

   return 1;
}

int about_here()
{
   object me = this_player();

   if (random(10)==0)
   {
     command("whisper "+me->query("id")+" 这个听雨轩有许多别人进不去的地方，呵呵！");
     me->set_temp("fengxue/askt",1);
   }
   else
     command("say 这里就是听雨轩啊！");
   
   return 1;
}

