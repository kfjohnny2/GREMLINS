#include "storagepool.hpp"
#ifndef _ALLOCATE_H_
#define _ALLOCATE_H_

struct Tag {
    StoragePool * pool;
};

void * operator new ( std::size_t , StoragePool & );

void * operator new ( std::size_t  ) ;

void operator delete ( void * arg ) ;

#include "allocate.inl"

#endif