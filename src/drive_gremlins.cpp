#include <iostream>
#include "slpool.hpp"

int main(int argc, char const *argv[]){
    SLPool p( 250 ); // Instanciando um GM derivado de StoragePool .
    void *ptr = p.Allocate ( 100 ); // Alocar 100 bytes de memoria .
    std::cout << ptr << std::endl;
    // p.Free( ptr );

    return EXIT_SUCCESS;
}