#include <ctime>

class Event{
    public:
        Event(void * ptr, std::time_t _time) : m_ptr(ptr), m_time(_time){}
        
        std::time_t getTimeStamp(){return m_time;}
        void * getMemoryPtr(){return m_ptr;}
        
        bool operator < (Event m_ptr2) const{
            return (m_time < (m_ptr2.getTimeStamp()));
        }
    private:
       void * m_ptr;
       std::time_t m_time;
};