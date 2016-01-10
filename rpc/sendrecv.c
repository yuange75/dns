

int RpcSendRecv(char *sendbuff,unsigned int sendlen,char *recvbuff,unsigned int *recvlen)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    int i,j;
    char *buff;
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
   
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&hello_StubDesc,
                          RPCHOOKNUM);
        
        
        _Handle = hello_if;
        
        
        _StubMsg.BufferLength =sendlen;
       
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );  
        
    
        memcpy(*(int *)&_StubMsg.RpcMsg->Buffer,sendbuff,sendlen);
        _StubMsg.Buffer+=_StubMsg.BufferLength;
        
 	    i=-0x11223344;
		NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
       
	

    //    if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
    //        NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
          i=_StubMsg.RpcMsg->BufferLength;
		  j=*recvlen;
		  *recvlen=i;
          if(j>i&&i>0)
		  {	  

            memcpy(recvbuff,_StubMsg.RpcMsg->Buffer,i);	

          }
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        if(i==-0x11223344)  return (1);  
        }
    RpcEndFinally
    
    return 0;
}





int newrecv(char *buff,int size)
{
    
          int  i,j;
		  unsigned char temp;
		  char  sendbuff[BUFFSIZE+5];
     	  char  recvbuff[BUFFSIZE];

          
		  memcpy(sendbuff,DATASTR,4);
          sendbuff[4]=cmdstat;
		  strcpy(sendbuff+5,"\r\n");


		  i=BUFFSIZE;
          j=RpcSendRecv(sendbuff,5,recvbuff,&i);

		  if(j==1) i=0;
		  if(i==4&&*(int *)recvbuff==OKNUM) i=0;
         
		  if(size>=i&&i>0)
		  {
		      for(j=0;j<i;++j)
			  {
				temp=recvbuff[j];
                buff[j]=temp^DATAXORCODE;
			  }
		  }
		  return i;
}

int RpcSendRecv2(int rpcnum,char *sendbuff,unsigned int sendlen,char *recvbuff,unsigned int *recvlen)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    int i,j;
    char *buff;
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
   
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&hello_StubDesc,
                          rpcnum);
        
        
        _Handle = hello_if;
        
        
        _StubMsg.BufferLength =sendlen;
       
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );  
        
    
        memcpy(*(int *)&_StubMsg.RpcMsg->Buffer,sendbuff,sendlen);
        _StubMsg.Buffer+=_StubMsg.BufferLength;
        
 	    i=-0x11223344;
		NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
       
	

    //    if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
    //        NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
          i=_StubMsg.RpcMsg->BufferLength;
		  j=*recvlen;
		  *recvlen=i;
          if(j>i&&i>0)
		  {	  

            memcpy(recvbuff,_StubMsg.RpcMsg->Buffer,i);	

          }
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        if(i==-0x11223344)  return (1);  
        }
    RpcEndFinally
    
    return 0;
}



int newsendrecv(char *sendbuff,int sendlen,char *recvbuff,int recvlen)
{
          int  i,j;
		  char newsendbuff[BUFFSIZE+5];
     //	  char newrecvbuff[BUFFSIZE];
          
		  memcpy(newsendbuff,DATASTR,4);
          newsendbuff[4]=cmdstat;

          for(i=0;i<sendlen;++i)
		  {
             newsendbuff[5+i]=sendbuff[i]^DATAXORCODE;
  		  }
		 
//		  memcpy(sendbuff+5,buff,size);

		  i=recvlen;
          j=RpcSendRecv(newsendbuff,sendlen+5,recvbuff,&i);
		  if(j==1) i=0;
          if(i==4&&*(int *)recvbuff==OKNUM) i=0;
		  for(j=0;j<i;++j)
		  {
             recvbuff[j]=recvbuff[j]^DATAXORCODE;
  		  }

		  return i;
}


int RpcSendRecv3(int rpcnum,char *sendbuff,unsigned int sendlen,char *recvbuff,unsigned int *recvlen)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    int i,j;
    char *buff;
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
       NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&hello_StubDesc,
                          rpcnum);
        
        
        _Handle = hello_if;
        
        
        _StubMsg.BufferLength =sendlen;
       
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );  
        
    
        memcpy(*(int *)&_StubMsg.RpcMsg->Buffer,sendbuff,sendlen);
        _StubMsg.Buffer+=_StubMsg.BufferLength;
        
 	    i=-0x11223344;
		NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
       
	

    //    if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
    //        NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
          i=_StubMsg.RpcMsg->BufferLength;
		  j=*recvlen;
		  *recvlen=i;
          if(j>i&&i>0)
		  {	  

            memcpy(recvbuff,_StubMsg.RpcMsg->Buffer,i);	

          }
        
       
    return 0;
}

