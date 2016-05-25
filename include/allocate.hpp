
#ifdef _ALLOCATE_H_
#define _ALLOCATE_H_

struct Tag {
    StoragePool * pool;
};

void * operator new ( size_type bytes , StoragePool & p );

void * operator new ( size_type bytes ) ;

void operator delete ( void * arg ) ;

#include "allocate.inl"

#endif