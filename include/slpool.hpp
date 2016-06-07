#include <iostream>
#include "storagepool.hpp"

#ifndef _SLPOOL_H_
#define _SLPOOL_H_

typedef std::size_t size_type;

class SLPool : public StoragePool {

public:
	struct Header {
		unsigned int mui_Length;
		Header(): mui_Length(0u) { /* Empty */ };
	};
	
	struct Block : public Header {
		enum { BlockSize = 16 }; // Each block has 16 bytes .
		union {
			Block *mp_Next;
			char mc_RawArea [ BlockSize - sizeof(Header) ];
		};
	   Block(): Header (), mp_Next(nullptr) { /* Empty */ };
	};

private:
	unsigned int mui_NumberOfBlocks;
	Block *mp_Pool;//!< Head of list .
	Block &mr_Sentinel;//!< End of the list .
public:
	explicit SLPool (size_type);
	~SLPool ();
	
	/**
	 * @brief This method reserve blocks in the pool according to the amount of bytes required.
	 *
	 * @param bytes The amount of bytes to reserve in the pool.
	 */
	void  *Allocate (size_type);
	
	void  *Best_Allocate (size_type);
	
	/**
	 * @brief This method frees the space on the pool.
	 *
	 * @param ptReserved A pointer to the space that what to free.
	 */
	void Free (void *);
	
	/**
	 * @brief Calculate the number of blocks needed to a given amount of bytes.
	 *
	 * @param  Bytes number of bytes to be allocated
	 * @return The amount of blocks needed.
	 */
	unsigned int getLength(size_type);
	
	/**
	 * @brief Print the corrent state of the pool using "[#]" to full space and "[ ]" to free space.
	 */
	void view();
};

#include "slpool.inl"

#endif