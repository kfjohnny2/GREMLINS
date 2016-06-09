/**
 *  @file drive_gremlins.cpp
 *  @brief GREMLINS Implementation
 *  @author Johnnylee Bryan Marques da Rocha e Pedro Arthur Medeiros Fernandes.
 *  @copyright Copyright &copy; 2016. All rights reserved.
 * 
 *  File with a tast comparing the GREMLINS implementation with the OS.
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <chrono>
#include <cstdlib>

#include "allocate.hpp"
#include "slpool.hpp"
#include "event.hpp"

/**
 * @brief Setup random numbers generator for memory size , say [100, 2000] bytes.
 *
 * @return A random number in the range [100, 2000].
 */
std::time_t getRandomTimeInterval(){
    return 1 + (rand() % 100 - 1);
}
/**
 * @brief Setup random numbers generator for time intervals , say [1, 100] units.
 *
 * @return A random number in the range [1, 100].
 */
int getRandomForSize(){
	return 100 + (rand() % 2000 - 100);
}

/**
 * @brief test the alocation of memory using the StoragePool
 *
 * @param _pool The SLPool criated where the thins will be allocated.
 * @param _timeLimit The Max time a block can be allocated;
 */
void StoragePoolTest (StoragePool & _pool , std::time_t _timeLimit){
    std::priority_queue<Event> pq;
    
    for( std::time_t t (0); t < _timeLimit; ++t ){
    	while(!pq.empty()) { // Run while we have events pending or time to run .
    		Event ev = pq.top(); // Access the event with the smallest time - stamp .
    		if(ev.getTimeStamp() > t) break ; // Still some time left ....
    		
    		// When we got here , the top event has run out of time .
    		pq.pop(); // Remove event from priority queue .
    		_pool.Free(ev.getMemoryPtr()); // Calling free operator .
        }
    auto memSize = getRandomForSize ();
    void * const add = _pool.Allocate(memSize);
    auto elapsedTime = getRandomTimeInterval();
    std::time_t releaseTime = t+elapsedTime ; // Set time stamp some time from now .
    pq.push(Event(add, releaseTime)); // Creating a new simulation event .
    }
}

/**
 * @brief Test the alocation of memory using the OS methods.
 *
 * @param _timeLimit The limit time a block can be allocated.
 */
void SOMemoryTest (std::time_t _timeLimit){
    std::priority_queue<Event> pq;
    
    for( std::time_t t (0); t < _timeLimit; ++t ){
    	while(!pq.empty()) { // Run while we have events pending or time to run .
    		Event ev = pq.top(); // Access the event with the smallest time - stamp .
    		if(ev.getTimeStamp() > t) break ; // Still some time left ....
    		
    		// When we got here , the top event has run out of time .
    		pq.pop(); // Remove event from priority queue .
    		std::free(ev.getMemoryPtr()); // Calling free operator .
        }
    auto memSize = getRandomForSize ();
    void * const add = std::malloc(memSize);
    auto elapsedTime = getRandomTimeInterval();
    std::time_t releaseTime = t+elapsedTime ; // Set time stamp some time from now .
    pq.push(Event (add, releaseTime)); // Creating a new simulation event .
    }
}

int main(int argc, char const *argv[]){
    
    SLPool p((1024*1024)); // Instanciando um GM derivado de StoragePool .

    std::cout << ">>> STARTING computation that needs timing (using GREMLINS) <<<\n";
    auto start = std::chrono::steady_clock::now();
    //================================================================================
    StoragePoolTest(p, 200);
    //================================================================================
    auto end = std::chrono::steady_clock::now();
    std::cout << ">>> ENDING computation that needs timing <<<\n";

    //Store the time difference between start and end
    auto diff = end - start;

    // Nanoseconds (10^-9)
    std::cout << "\t\t>>> " << std::chrono::duration <double, std::nano> (diff).count() << " ns\n" << std::endl;

      //////////////
     // using OS //
    //////////////
    std::cout << ">>> STARTING computation that needs timing (using OS)<<<\n";
    start = std::chrono::steady_clock::now();
    //================================================================================
	SOMemoryTest(200);
    //================================================================================
    end = std::chrono::steady_clock::now();
    std::cout << ">>> ENDING computation that needs timing <<<\n";

    //Store the time difference between start and end
    diff = end - start;

    // Nanoseconds (10^-9)
    std::cout << "\t\t>>> " << std::chrono::duration <double, std::nano> (diff).count() << " ns" << std::endl;
    return EXIT_SUCCESS;
}