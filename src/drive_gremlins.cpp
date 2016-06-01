#include <iostream>
#include "slpool.hpp"

int main(int argc, char const *argv[]){
    SLPool p( 220 ); // Instanciando um GM derivado de StoragePool .
    p.view();
    void *ptr = p.Allocate ( 100 ); // Alocar 100 bytes de memoria .
    p.view();
    std::cout << ptr << std::endl;
    p.Free( ptr );
    p.view();
    return EXIT_SUCCESS;
}