// mudlist.c
// Modify By Mudring@SanJie

#include <ansi.h>
#include <net/daemons.h>
#include <net/macros.h>
#include <mudlib.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    mapping mud_list;
    mapping mud_svc;
    mixed   *muds;
    string  output;
    string  name;
    string  mudn;
    string  vis_mudn;
    string  local_mudlib;
    int     loop, size, total, count;

    if( !find_object(DNS_MASTER) )
        return notify_fail("网路精灵并没有被载入。\n");

    //  Obtain mapping containing mud data
    mud_list = (mapping)DNS_MASTER->query_muds();

    // so we recognise ourselves as a DNS mud
    mud_svc = DNS_MASTER->query_svc() + ([ Mud_name() : 0 ]);

    if(!mud_list)
        return notify_fail( MUD_NAME + "目前并没有跟网路上其他 Mud 取得联系。\n");

    //  Get list of all mud names within name server
    muds = keys( mud_list ) - ({ "DEFAULT" });

    if (!arg)
    {
        // filter for release sub sites & me
        local_mudlib = MUDLIB_NAME;
        muds = filter_array(muds, (: $(mud_list)[$1]["MUDLIB"] == $(local_mudlib) :));
    }
    else if (arg != "all")
        // filter for muds matched argument
        muds = filter_array(muds, (: sscanf($1, $(arg) + "%*s") :));

    if (! sizeof(muds))
        return notify_fail("目前本站并没有和这个 MUD 取得任何联系。\n");

    // Place mudlist into alphabetical format
    muds = sort_array(muds, 1);

    output = BRED HIG+"Mud        中文名称                国际网路位址     端口  人数\n"+NOR;
    output += repeat_string("─", 32) + "\n";

    //      Count for users
    count = 0;

    for (loop = 0, size = sizeof(muds); loop < size; loop++)
    {
        mudn = muds[loop];
        if (undefinedp(mud_list[mudn]["USERS"]))
            continue;

        if (! stringp(name = mud_list[mudn]["MUDNAME"]))
            name = "未知名称";

        // filter some ... strange ansi
        name = replace_string(name, ESC "[0;37;0m", "");
        name = replace_string(name, ESC "[2;17m", "");
        name = filter_color(name);

        // 修正长度
        vis_mudn = filter_color(mudn);
        if (strlen(vis_mudn) > 12) vis_mudn = vis_mudn[0..11];
        if (strlen(name) > 20) name = name[0..19];

        if (htonn(upper_case(mudn)) == htonn(upper_case(INTERMUD_MUD_NAME)))
        {
            mud_list[mudn]["HOSTADDRESS"] = LOCALHOST;
            output +=  BBLU+HIY;
        }
        else if (mud_list[mudn]["VERSION"] == MUDLIB_VERSION)
            output +=  GRN;
        else
            output += NOR;

        if (stringp(mud_list[mudn]["ZONE"]))
            name += "(" + mud_list[mudn]["ZONE"] + ")";

        output +=  sprintf("%-10s %-23s %-15s  %4s", 
                upper_case(vis_mudn), name,
                mud_list[mudn]["HOSTADDRESS"],
                mud_list[mudn]["PORT"]);

        if (!undefinedp(mud_list[muds[loop]]["USERS"]))
        {
            output+=sprintf("  %-4s", mud_list[mudn]["USERS"] );
            count += atoi(mud_list[mudn]["USERS"]);
        }
        else
            output+=sprintf("  ----", mud_list[mudn]["USERS"] );

        output +=NOR"\n";
        total ++;
    }

    //  Display dumped mudlist output through user's more pager
    output += repeat_string("─", 32) + "\n";

    if (! arg)
        output += "「三界神话」共有" + chinese_number(count) +
                  "位玩家在" + chinese_number(total) + "处站点连线中。\n";

    if (objectp(me))
        me->start_more(output);
    else
        write(output + "\n");

    return 1;
}

int help()
{
    write("\n指令格式：mudlist        列出连线中的"MUD_NAME"站点。\n"
        "      mudlist <MudName>  列出指定 Mud 的信息。\n"
        "      mudlist all        列出目前所有连线中的 Mud。\n\n"
    );
    return 1;
}


