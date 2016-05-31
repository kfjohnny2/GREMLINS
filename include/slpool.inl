#include <iostream>
#include "allocate.hpp"
#include "slpool.hpp"

typedef std::size_t size_type;

explicit SLPool::SLPool ( size_type bytes) {
    this->mui_NumberOfBlocks = std:ceil(std::static_cast<float>((bytes + sizeof(Header))/(Block::BlockSize)))+1;
    mp_Pool = new Block[mui_NumberOfBlocks];
    mp_Pool->mui_Length = mui_NumberOfBlocks-1;
    mp_Pool->mp_Next = nullptr;
    mr_Sentinel(new mp_Pool[mui_NumberOfBlocks-1]); 
    mr_Sentinel->mp_Next = mp_Pool;
}

SLPool::~SLPool (){
    delete[] mp_Pool;
}

void * SLPool::Allocate ( std::size_type bytes){
    size_type length = std:ceil(std::static_cast<float>((bytes + sizeof(Header))/(Block::BlockSize)))+1;
    Block *work = (&this->mr_Sentinel)->mp_Next;
    Block *tail = &mr_Sentinel;
    
}
void SLPool::Free ( void * ){
    
}