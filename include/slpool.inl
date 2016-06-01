#include <iostream>
#include <cmath>
#include "allocate.hpp"
#include "storagepool.hpp"

typedef std::size_t size_type;

SLPool::SLPool ( size_type bytes) : mui_NumberOfBlocks(getLength(bytes)), mp_Pool(new Block[mui_NumberOfBlocks+1])
, mr_Sentinel( mp_Pool[mui_NumberOfBlocks]){ 
   // mui_NumberOfBlocks = getLength(bytes);
    //mp_Pool(new Block[mui_NumberOfBlocks+1]);
    mp_Pool[0].mui_Length = mui_NumberOfBlocks;
    mp_Pool[0].mp_Next = nullptr;
    //mr_Sentinel( mp_Pool[mui_NumberOfBlocks]); 
    mr_Sentinel.mp_Next = mp_Pool;
}

SLPool::~SLPool (){
    delete[] mp_Pool;
}

void * SLPool::Allocate ( size_type bytes){
    bool blockFound = true;  //***
    Block *work = (&mr_Sentinel)->mp_Next;
    Block *tail = &mr_Sentinel;
    size_type length = getLength(bytes);
    
    while(work!=nullptr && blockFound){
        if(work->mui_Length >= length){
            if(work->mui_Length == length){
                tail->mp_Next = work->mp_Next;
            } else{
                tail->mp_Next = work+length;
                tail->mp_Next->mp_Next = work->mp_Next;
                tail->mp_Next->mui_Length = work->mui_Length-length;
                work->mui_Length=length;
            }
            
            blockFound=false;
            if(mr_Sentinel.mp_Next==work)//Tail = actual block then skip one node
                mr_Sentinel.mp_Next = work->mp_Next;
            break;
            
        } else{
            tail = tail->mp_Next; // skip one node on last item
            work = work->mp_Next; // skip one node on the actual node
        }
        
        if(blockFound) 
            throw (std::bad_alloc());
    }
    
    return reinterpret_cast<void *>(reinterpret_cast<Header *>(work)+1);
}
void SLPool::Free ( void * ptReserved){
    Block* ptPostReserved = mr_Sentinel.mp_Next;
    Block* ptPrevReserved = &mr_Sentinel;
    Block* reserveBlock = reinterpret_cast <Block*>(reinterpret_cast <int*>(ptReserved)-1U);;
    
    while(ptPostReserved != nullptr ){
        if(ptPostReserved>reserveBlock){
            if(((ptPrevReserved+ptPrevReserved->mui_Length) == reserveBlock ) && ((reserveBlock+reserveBlock->mui_Length) == ptPostReserved)){
                ptPrevReserved->mp_Next=ptPostReserved->mp_Next; // Prev areas freed
                ptPrevReserved->mui_Length+=reserveBlock->mui_Length+ptPostReserved->mui_Length; // Combine all 3 areas in one node
                reserveBlock->mui_Length = 0; // reset reserve pointer
                ptPostReserved->mui_Length = 0; // reset post pointer
            } else if ((ptPrevReserved+ptPrevReserved->mui_Length) == reserveBlock){ // sum of the areas is the same of the reserved block that will be liberated
                //TODO: Combine the reserved area with the prev; reset prev area; point the reserved area to the prev.
                ptPrevReserved->mp_Next=ptPostReserved->mp_Next; // Prev areas freed
                ptPrevReserved->mui_Length+=reserveBlock->mui_Length;
                reserveBlock->mui_Length = 0; // reset reserve pointer
            } else if ((reserveBlock+reserveBlock->mui_Length) == ptPostReserved){ // sum of the reserved block are the same of the post pointer
                //TODO: 
                reserveBlock->mp_Next=ptPostReserved->mp_Next; // Prev areas freed
                reserveBlock->mui_Length+=ptPostReserved->mui_Length;
                reserveBlock->mui_Length = 0; // reset reserve pointer
            } else{  
                //TODO: The prev area must be freed and the post is reserved. Free the are and sum with the prev.
                ptPrevReserved->mp_Next = reserveBlock;
                reserveBlock->mp_Next = ptPostReserved;
            }
            reserveBlock = nullptr;
            return;
        }
        ptPrevReserved = ptPostReserved;
        ptPrevReserved = ptPostReserved->mp_Next;
    }
    
    if(ptPostReserved == nullptr){
        mr_Sentinel.mp_Next = reserveBlock;
        reserveBlock->mp_Next = nullptr;
    }
}

unsigned int SLPool::getLength(size_type bytes){
    int tst = std::ceil(static_cast<float>(bytes)/Block::BlockSize); // std::ceil(static_cast<float>((bytes + sizeof(Header))/(Block::BlockSize)));
    return tst;
}