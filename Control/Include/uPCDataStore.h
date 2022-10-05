#pragma once

#ifdef UPC_DLL_EXPORTS
#define UPC_Export __declspec(dllexport)
#else
#define UPC_Export __declspec(dllimport)
#endif


class UPC_Export uPCDataStore
{
public:
	uPCDataStore(void);
	uPCDataStore( unsigned int bufsize_ ) ;
	uPCDataStore( unsigned int bufsize_ , const  char* in_buf );
	uPCDataStore( const uPCDataStore& rhs );

	~uPCDataStore(void);


	int						allocate_size( size_t nBufSize );
	char*					get_buffer  ( );
	void					destory();
	char*					get();
	void					reset(char* pBuffer);
	char*					get_buffer  ( ) const ;
	int						copy_buffer ( char* dest_buffer ) ;
	void					copy_buffer  ( const  char* buffer , unsigned int bufsize );
	void					set_buffer  ( const  char* buffer , unsigned int bufsize );
	void					buffer_size(const unsigned int size);
	void					swell_buffer (  char*	buffer,unsigned int bufsize);
	size_t					buffer_size ( );
	int						copy_buffer ( uPCDataStore& out_buffer , unsigned int offset , unsigned int size );
	int						partial_copy( const uPCDataStore& in_buf , unsigned int offset , unsigned int size );
	int						partial_copy( const char* buf,unsigned int offset,unsigned int size);

public:
	char*				buffer_	; //!<	실제 데이터를 저장하는 버퍼
	unsigned int		bufsize_; //!<  bufsize
};

