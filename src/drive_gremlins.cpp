#include <iostream>
#include "slpool.hpp"

int main{
    
    SomePool p; // Instanciando um GM derivado de StoragePool .
    void *ptr = p.Allocate ( 100 ); // Alocar 100 bytes de memoria .
    // Usar a memoria .
    p.Free( ptr );
    
    return EXIT_SUCCESS;
}