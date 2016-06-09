/**
 *  @file allocate.inl
 *  @brief GREMLINS Implementation
 *  @author Johnnylee Bryan Marques da Rocha e Pedro Arthur Medeiros Fernandes.
 *  @copyright Copyright &copy; 2016. All rights reserved.
 * 
 *  File with the implementations of new operators.
 */
 
#include "storagepool.hpp"

void * operator new ( size_type bytes , StoragePool & p ) {
 Tag* const tag = reinterpret_cast<Tag *>( p.Allocate(bytes + sizeof(Tag)));
 tag -> pool = &p;
 // skip sizeof tag to get the raw data - block .
 return ( reinterpret_cast< void *>( tag + 1U ));
}

void * operator new ( size_type bytes ) { // Regular new
 Tag* const tag = reinterpret_cast<Tag *>(std::malloc(bytes + sizeof(Tag)));
 tag->pool = nullptr ;
 // skip sizeof tag to get the raw data - block .
 return (reinterpret_cast< void *>( tag + 1U ));
}

void operator delete ( void * arg ) noexcept {
 Tag * const tag = reinterpret_cast<Tag *>( arg ) - 1U;
 if ( nullptr != tag -> pool ) // Memory block belongs to a particular GM.
     tag->pool->Free( tag );
 else
     std::free( tag ); // Memory block belongs to the operational system .
}