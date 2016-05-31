#ifndef _STORAGEPOOL_H_
#define _STORAGEPOOL_H_

typedef size_t size_type;

class StoragePool{

public:

	virtual ~StoragePool ();

	virtual void *Allocate ( std::size_t ) = 0;

	virtual void Free( void * ) = 0;
};

#endif