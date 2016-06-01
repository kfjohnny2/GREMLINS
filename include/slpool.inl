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
void SLPool::Free ( void * ){
    
}

float SLPool::getLength(size_type bytes){
    return std::ceil(static_cast<float>((bytes + sizeof(Header))/(Block::BlockSize)));
}