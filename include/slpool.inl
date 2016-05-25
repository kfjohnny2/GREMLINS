#include <iostream>
#include "allocate.hpp"
#include "slpool.hpp"

typedef std::size_t size_type;

explicit SLPool::SLPool ( size_type bytes) {
    this->mui_NumberOfBlocks = ((bytes + sizeof(Header))/sizeof(Block));
    mp_Pool = new Block[mui_NumberOfBlocks];
    mp_Pool->mui_Length = mui_NumberOfBlocks-1;
    mp_Pool->mp_Next = nullptr;
    mr_Sentinel = mp_Pool[mui_NumberOfBlocks-1]; 
    mr_Sentinel->mp_Next = mp_Pool;
}
SLPool::~SLPool (){
    delete mp_Pool;
    delete mr_Sentinel;
}
void * SLPool::Allocate ( std::size_type bytes){
    SLPool *work = new SLPool(bytes);
    SLPool *tail = mr_Sentinel;
    
}
void SLPool::Free ( void * ){
    
}