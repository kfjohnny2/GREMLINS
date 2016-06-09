/**
 *  @file slpool.hpp
 *  @brief GREMLINS Implementation
 *  @author Johnnylee Bryan Marques da Rocha e Pedro Arthur Medeiros Fernandes.
 *  @copyright Copyright &copy; 2016. All rights reserved.
 * 
 *  File with the declaration of the class StoregePool that have the main functions.
 */

#ifndef _STORAGEPOOL_H_
#define _STORAGEPOOL_H_

typedef size_t size_type;

class StoragePool{

public:

	virtual ~StoragePool (){};

	virtual void *Allocate ( std::size_t ) = 0;

	virtual void Free( void * ) = 0;
	virtual void view() = 0;
};

#endif