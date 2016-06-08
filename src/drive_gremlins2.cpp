#include <iostream>

#include "allocate.hpp"
#include "slpool.hpp"

int main(int argc, char const *argv[]){
	std::cout << ">>> Creating a pool of 190 bytes or 12 blocks..." << std::endl;
	SLPool p(190);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

	std::cout << ">>> Allocating 88 bytes or 6 blocks..." << std::endl;
	void * ptr1 = p.Allocate(88);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

	std::cout << ">>> Allocating 44 bytes or 3 blocks..." << std::endl;
	void * ptr2 = p.Allocate(44);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

	std::cout << ">>> Allocating 44 bytes or 3 blocks..." << std::endl;
	void * ptr3 = p.Allocate(44);

	// /\ completa

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

	//A área imediatamente anterior é livre e a posterior é reservada
	std::cout << ">>> **Desallocating 44 bytes or 3 blocks..." << std::endl;
	p.Free(ptr3);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();
	//========================
	//As áreas imediatamente anterior e posterior são reservadas
	std::cout << ">>> Desallocating 44 bytes or 3 blocks..." << std::endl;
	p.Free(ptr2);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

	//A área imediatamente anterior é reservada e a posterior é livre
	std::cout << ">>> Desallocating 88 bytes or 6 blocks..." << std::endl;
	p.Free(ptr1);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();


	std::cout << ">>> Allocating 88 bytes or 6 blocks..." << std::endl;
	ptr1 = p.Allocate(88);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

	std::cout << ">>> Allocating 44 bytes or 3 blocks..." << std::endl;
	ptr2 = p.Allocate(44);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

	std::cout << ">>> Desallocating 88 bytes or 6 blocks..." << std::endl;
	p.Free(ptr1);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

	//test best fit tamanho >
	std::cout << ">>> Allocating 30 bytes or 2 blocks...(bestfit<)" << std::endl;
	ptr3 = p.Best_Allocate(30);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

	std::cout << ">>> Desallocating 30 bytes or 2 blocks..." << std::endl;
	p.Free(ptr3);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

	//test best fit tamanho ==
	std::cout << ">>> Allocating 40 bytes or 3 blocks...(bestfit==)" << std::endl;
	ptr3 = p.Best_Allocate(40);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

    return EXIT_SUCCESS;
}