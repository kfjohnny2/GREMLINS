/**
 *  @file event.hpp
 *  @brief GREMLINS Implementation
 *  @author Johnnylee Bryan Marques da Rocha e Pedro Arthur Medeiros Fernandes.
 *  @copyright Copyright &copy; 2016. All rights reserved.
 * 
 *  File with the declaration of the class Event.
 */
 

#include <ctime>
/**
 * @brief A class that creates a pair address/time-stamp.
 */
class Event{
    public:
        /**
         * @brief Constructor that creates a pair address/time-stamp.
         *
         * @param ptr A pointer to the space allocated
         * @param _time A caunter to the time spent by this allocation.
         */
        Event(void * ptr, std::time_t _time) : m_ptr(ptr), m_time(_time){}

        /**
         * @brief Return the time spent.
         *
         * @return m_time the time spent.
         */
        std::time_t getTimeStamp(){return m_time;}

        /**
         * @brief Return the pointer of the Event.
         * @return m_ptr the pointer of the Event.
         */
        void * getMemoryPtr(){return m_ptr;}
        
        bool operator < (Event m_ptr2) const{
            return (m_time < (m_ptr2.getTimeStamp()));
        }
    private:
       void * m_ptr;//!< A pointer to the space allocated.
       std::time_t m_time;//!< A caunter to the time spent by this allocation.
};