//make.c

#include <ansi.h>

void done(object me);
int main(object me, string arg)
{
      object ob,ob1,ob2; 
        int lv;
        lv=me->query_skill("medical",1);

        seteuid(getuid());

        if( me->is_busy() )
        return notify_fail("你正忙着呢。\n");

        if( !arg )
        return notify_fail("你要制什么药？\n");

        if( me->is_fighting() )
        return notify_fail("你正在战斗，制什么药啊？\n");
        if( me->is_busy() || me->query_temp("pending/exercising"))
        return notify_fail("你正忙着呢，没时间制药。\n");
/*
        if( lv < 1 )
        return notify_fail("你的医术不能制药。\n");
*/
     switch (arg)
      {
      case "jinchuang":
         if( ! present("niu huang", me) || ! present("ren shen", me) )
        return notify_fail("你的药材不齐全。\n");
          ob1 = present("niu huang",this_player());
          ob2 = present("ren shen",this_player());
        ob=new("/obj/jineng/medical/jinchuang.c");
        ob->move(me);
        me->start_busy(3);
        destruct(ob1); 
        destruct(ob2); 
done(me);
        break;
case "解毒丸1":
if( ! present("san qi", me) || ! present("ren shen", me) )
return notify_fail("你的药材不齐全。\n");
ob1 = present("san qi",this_player());
ob2 = present("ren shen",this_player());
ob=new("/obj/jineng/medical/jinchuang.c");
ob->move(me);
me->start_busy(3);
destruct(ob1); 
destruct(ob2); 
done(me);
break;

case "解毒丸2":
if( ! present("san qi", me) || ! present("gouji zi", me) )
return notify_fail("你的药材不齐全。\n");
done(me);
ob1 = present("san qi",this_player());
ob2 = present("gouji zi",this_player());
ob=new("/obj/jineng/medical/jinchuang.c");
ob->move(me);
me->start_busy(3);
destruct(ob1); 
destruct(ob2); 
done(me);
break;
case "解毒丸3":
if( ! present("san qi", me) || ! present("niu huang", me) )
return notify_fail("你的药材不齐全。\n");
ob1 = present("san qi",this_player());
ob2 = present("niu huang",this_player());
ob=new("/obj/jineng/medical/jinchuang.c");
ob->move(me);
me->start_busy(3);
destruct(ob1); 
destruct(ob2);
done(me);
break;
case "解毒丸4":
if( ! present("gouji zi", me) || ! present("niu huang", me) )
return notify_fail("你的药材不齐全。\n");
ob1 = present("gouji zi",this_player());
ob2 = present("niu huang",this_player());
ob=new("/obj/jineng/medical/jinchuang.c");
ob->move(me);
me->start_busy(3);
destruct(ob1); 
destruct(ob2); 
done(me);
break;
case "解毒丸5":
if( ! present("gouji zi", me) || ! present("ren shen", me) )
return notify_fail("你的药材不齐全。\n");
ob1 = present("gouji zi",this_player());
ob2 = present("ren shen",this_player());
ob=new("/obj/jineng/medical/jinchuang.c");
ob->move(me);
me->start_busy(3);
destruct(ob1); 
destruct(ob2); 
done(me);
break;
        default:   notify_fail("你没有能力制这种药。\n");
        
        }

        return 1;
}


void done(object me)
{
        int i;
        object *inv; 
               inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++) {
                        if (inv[i]->query("done"))
                        destruct(inv[i]);
                }
message_vision( HIC "只见$N驱真气于药材之上，不多会药材便消失了。\n" NOR,me);
                me->start_busy(6);
return;
}

