/**
 *  @file slpool.inl
 *  @brief GREMLINS Implementation
 *  @author Johnnylee Bryan Marques da Rocha e Pedro Arthur Medeiros Fernandes.
 *  @copyright Copyright &copy; 2016. All rights reserved.
 * 
 *  File with the implementatio of the  class SLPool used to modfy the memory.
 */
 
#include <iostream>
#include <cmath>
#include <new>

#include "allocate.hpp"
#include "storagepool.hpp"

typedef std::size_t size_type;

SLPool::SLPool (size_type bytes) : mui_NumberOfBlocks(getLength(bytes)), mp_Pool(new Block[mui_NumberOfBlocks+1])
, mr_Sentinel( mp_Pool[mui_NumberOfBlocks]){
    mp_Pool[0].mui_Length = mui_NumberOfBlocks;
    mp_Pool[0].mp_Next = nullptr;
    mr_Sentinel.mp_Next = mp_Pool;
}

SLPool::~SLPool (){
    delete[] mp_Pool;
}

void * SLPool::Allocate (size_type bytes){
    bool blockFound = true;
    Block *work = (&mr_Sentinel)->mp_Next;
    Block *tail = &mr_Sentinel;
    size_type length = getLength(bytes);

    while(work != nullptr and blockFound){// Run the whole SLPool.
        if(work->mui_Length >= length){
            if(work->mui_Length == length){
                tail->mp_Next = work->mp_Next;
            }
            else{
                tail->mp_Next = work+length;
                tail->mp_Next->mp_Next = work->mp_Next;
                tail->mp_Next->mui_Length = work->mui_Length-length;
                work->mui_Length = length;
            }

            blockFound=false;
            if(mr_Sentinel.mp_Next == work)//Tail = actual block then skip one node
                mr_Sentinel.mp_Next = work->mp_Next;
            break;

        } else{
            tail = tail->mp_Next; // skip one node on last item
            work = work->mp_Next; // skip one node on the actual node
        }

        if(blockFound)
            throw (std::bad_alloc());
    }

    return reinterpret_cast<void *>(reinterpret_cast<Header *>(work)+1U);
}

void  * SLPool::Best_Allocate (size_type bytes){
    bool blockAllocted = false;//!< Control if the allocation was already done.
    Block *work = (&mr_Sentinel)->mp_Next;
    Block *best = nullptr;// get the best free space for the allocation
    Block *tail = &mr_Sentinel;
    Block *tailaux = nullptr;
    size_type length = getLength(bytes);

    while(work != nullptr){// Run the whole SLPool.
        std::cout << &best << std::endl;
        if(work->mui_Length == length){// if the freespace is the sabe, allocate and finish.
            blockAllocted = true;
            tail->mp_Next = work->mp_Next;
            break;
        }
        else if(best == nullptr){
            if(work->mui_Length > length){
                best = work;
                tailaux = tail;
            }
        }
        //look for the best option
        else if(work->mui_Length > length and work->mui_Length < best->mui_Length)
                best = work;
                tailaux = tail;

        tail = tail->mp_Next; // skip one node on last item
        work = work->mp_Next; // skip one node on the actual node
    }
    if(!blockAllocted){
        if( best == nullptr) //If it don't found any possible position: erro bad_alloc
            throw (std::bad_alloc());
        else{ // allocate in the best option
            tailaux->mp_Next = best+length;
            tailaux->mp_Next->mp_Next = best->mp_Next;
            tailaux->mp_Next->mui_Length = best->mui_Length-length;
            best->mui_Length = length;
        }
    }
    return reinterpret_cast<void *>(reinterpret_cast<Header *>(best)+1U);
}

void SLPool::Free(void * ptReserved) {
    Block* ptPostReserved = mr_Sentinel.mp_Next;
    Block* ptPrevReserved = &mr_Sentinel;
    Block* reserveBlock = reinterpret_cast <Block*>(reinterpret_cast <int*>(ptReserved)-1U);;

    while(ptPostReserved != nullptr){
        if(ptPostReserved > reserveBlock){
            if(((ptPrevReserved+ptPrevReserved->mui_Length) == reserveBlock ) && ((reserveBlock+reserveBlock->mui_Length) == ptPostReserved)){
                ptPrevReserved->mp_Next = ptPostReserved->mp_Next; // Prev areas freed
                ptPrevReserved->mui_Length += reserveBlock->mui_Length+ptPostReserved->mui_Length; // Combine all 3 areas in one node
                reserveBlock->mui_Length = 0; // reset reserve pointer
                ptPostReserved->mui_Length = 0; // reset post pointer
            } else if ((ptPrevReserved+ptPrevReserved->mui_Length) == reserveBlock){ // sum of the areas is the same of the reserved block that will be liberated
                //TODO: Combine the reserved area with the prev; reset prev area; point the reserved area to the prev.
                ptPrevReserved->mp_Next = ptPostReserved->mp_Next; // Prev areas freed
                ptPrevReserved->mui_Length += reserveBlock->mui_Length;
                reserveBlock->mui_Length = 0; // reset reserve pointer
            } else if ((reserveBlock+reserveBlock->mui_Length) == ptPostReserved){ // sum of the reserved block are the same of the post pointer
                //TODO:
                reserveBlock->mp_Next = ptPostReserved->mp_Next; // Prev areas freed
                ptPrevReserved->mp_Next=reserveBlock;
                reserveBlock->mui_Length += ptPostReserved->mui_Length;
                ptPostReserved->mui_Length = 0; // reset reserve pointer
            } else{
                //TODO: The prev area must be freed and the post is reserved. Free the are and sum with the prev.
                ptPrevReserved->mp_Next = reserveBlock;
                reserveBlock->mp_Next = ptPostReserved;
            }
            reserveBlock = nullptr;
            break;
        }else{
            ptPrevReserved=ptPrevReserved->mp_Next;
        }
        ptPostReserved=ptPostReserved->mp_Next;
    }

    if(ptPostReserved == nullptr){
        reserveBlock->mp_Next=ptPostReserved;
        ptPrevReserved->mp_Next=reserveBlock;
        reserveBlock->mp_Next = nullptr;

    }
}

unsigned int SLPool::getLength(size_type bytes){
    int tst = std::ceil(static_cast<float>(bytes)/Block::BlockSize); 
    return tst;
}

void SLPool::view(){
      int total_length = mui_NumberOfBlocks; //!< Gets the number of block in the Pool
    int length; //!< Used to get the number of blocks occupied by the free/full space
    int free_length = 0;
    int full_length = 0;
    Block* next_free = (&mr_Sentinel)->mp_Next; //!< A pointer to the next free space in the pool

    std::cout << "| ";
    for (auto i = 0; i < total_length; i += length) {
        length = mp_Pool[i].mui_Length;
        if(&mp_Pool[i] == next_free){ // If is a free space and print [#] to each block
            for (auto e = 0; e < length; e++) {
                    std::cout << "[ ]";
            }
            std::cout << " | ";
            free_length += length;
            next_free = mp_Pool[i].mp_Next;
        }
        else {// Else, if is the space is full and print [#] to each block
            for (auto e = 0; e < length; e++) {
                std::cout << "[#]";
            }
            std::cout << " | ";
            full_length += length;
        }
    }
     std::cout << "\n\n\t>>> Number of free blocks: " << free_length << std::endl;
     std::cout << "\t>>> Number of allocated blocks: " << full_length << "\n" << std::endl;
}
