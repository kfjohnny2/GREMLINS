/**
 *  @file drive_gremlins.cpp
 *  @brief GREMLINS Implementation
 *  @author Johnnylee Bryan Marques da Rocha e Pedro Arthur Medeiros Fernandes.
 *  @copyright Copyright &copy; 2016. All rights reserved.
 * 
 *  File with a tast to pruve that the class SLPool is working.
 */

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

	// The pool is fool.

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

    // The next and the previous areas are reserved
	std::cout << ">>> Desallocating 44 bytes or 3 blocks..." << std::endl;
	p.Free(ptr2);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

    // The previous area is reserved and the next is free.
	std::cout << ">>> Desallocating 88 bytes or 6 blocks..." << std::endl;
	p.Free(ptr1);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

    // The previous area is free and the next is reserved.
	std::cout << ">>> Desallocating 44 bytes or 3 blocks..." << std::endl;
	p.Free(ptr3);

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

	// Test best fit  with a free space with the same size of the one you want to alloc.
	std::cout << ">>> Allocating 40 bytes or 3 blocks...(bestfit ==)" << std::endl;
	ptr3 = p.Best_Allocate(40);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

	std::cout << ">>> Desallocating 40 bytes or 3 blocks..." << std::endl;
	p.Free(ptr3);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

	// Test best fit  with a free space with a bigest size than the one you want to alloc.
	std::cout << ">>> Allocating 30 bytes or 2 blocks...(bestfit <)" << std::endl;
	ptr3 = p.Best_Allocate(30);

	std::cout << "\n  Printing the actual memory..." << std::endl;
	p.view();

    return EXIT_SUCCESS;
}