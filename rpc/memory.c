
void __RPC_FAR * __RPC_USER midl_user_allocate ( size_t size )
{
    return( malloc( size ) );
}  /* end of midl_user_allocate */

void __RPC_USER midl_user_free ( void __RPC_FAR *buf )
{
    free( buf );
}  /* end of midl_user_free */