#include <iostream>
#include "storagepool.hpp"

typedef size_t size_type;

class SLPool: public StoragePool {

public :

struct Header {
	size_type mui_Length;
	Header(): mui_Length(0u) { /* Empty */ };
};

struct Block : public Header {
	enum { BlockSize = 16 }; // Each block has 16 bytes .
	union {
		Block *mp_Next ;
		char mc_RawArea [ BlockSize - sizeof( Header ) ];
	};
   Block(): Header (), mp_Next ( nullptr ) { /* Empty */ };
};

private:
	size_type mui_NumberOfBlocks ;
	Block *mp_Pool ;
	// ! < Head of list .
	Block &mr_Sentinel ;
	// ! < End of the list .
public :
	explicit SLPool ( size_type );
	~SLPool ();
	void  *Allocate ( size_type );
	void Free ( void * );
	
struct Tag { 
    StoragePool * pool; 
};
 void * operator new ( size_type bytes , StoragePool & p ) {
     Tag* const tag = reinterpret_cast<Tag *>( p.Allocate(bytes + sizeof(Tag)));
     tag -> pool = &p;
     // skip sizeof tag to get the raw data - block .
     return ( reinterpret_cast< void *>( tag + 1U ) );
 }

 void * operator new ( size_type bytes ) { // Regular new
     Tag* const tag = reinterpret_cast<Tag *>(std::malloc(bytes + sizeof(Tag)));
     tag->pool = nullptr ;
     // skip sizeof tag to get the raw data - block .
     return (reinterpret_cast< void *>( tag + 1U ) );
 }

 void operator delete ( void * arg ) noexcept {
     // We need to subtract 1U (in fact , pointer arithmetics ) because arg
     // points to the raw data ( second block of information ).
     // The pool id (tag) is located `sizeof (Tag)' bytes before .
     Tag * const tag = reinterpret_cast<Tag *>( arg ) - 1U;
     if ( nullptr != tag -> pool ) // Memory block belongs to a particular GM.
         tag->pool->Release( tag );
     else
         std::free( tag ); // Memory block belongs to the operational system .
 }
};