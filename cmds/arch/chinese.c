//Cracked by Roath
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
inherit F_CLEAN_UP;

int main(object me, string arg)
{
   string key, chinz;

        if (! SECURITY_D->valid_grant(me, "(arch)")) return 0;
   if( !arg || arg=="" )
     return notify_fail("ָ���ʽ��chinese <Ӣ��>==<����>\n");

   if( sscanf(arg, "%s==%s", key, chinz)==2 ) {
     CHINESE_D->add_translate(key, chinz);
     write( key + " == " + chinz + "\nOk.\n");
     return 1;
   }

   return 0;
}

int help()
{
   write ( @HELP
ָ���ʽ��chinese <Ӣ��>==<����>
HELP
   );
   return 1 ;
}