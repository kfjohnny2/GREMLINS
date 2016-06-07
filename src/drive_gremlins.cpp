#include <iostream>
#include "slpool.hpp"

int main(int argc, char const *argv[]){
    std::cout << ">>>Starting..." << std::endl;
    SLPool p( 220 ); // Instanciando um GM derivado de StoragePool .
    p.view();
    void *ptr = p.Allocate ( 50 ); // Alocar 50 bytes de memoria .
    p.view();
    void *ptr1 = p.Allocate ( 25 ); // Alocar 25 bytes de memoria .
    p.view();
    p.Free( ptr );
    p.view();
    
    std::cout << ">>>Exiting..." << std::endl;
    return EXIT_SUCCESS;
}