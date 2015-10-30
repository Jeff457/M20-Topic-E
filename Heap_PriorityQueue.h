/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic E Project						*
*												*
*			Heap_PriorityQueue.h		 		*
*			Status: Working              		*
************************************************/

#ifndef _HEAP_PRIORITY_QUEUE
#define _HEAP_PRIORITY_QUEUE

#include "ArrayMaxHeap.h"

template<class ItemType>
class Heap_PriorityQueue : private ArrayMaxHeap<ItemType>
{
private:
	const double MAX_CAPACITY = 1.0;
	vector<ItemType> boxBuffer;

	// Checks for 3 conditions:
	// 1) Node represents a box that can add the weight to its load
	// 2) Node cannot add weight because that would put it over its MAX_CAPACITY
	// 3) All boxes are too full to add weight
	bool ableToAdd(const double& newLoad);

public:
	Heap_PriorityQueue();
	bool isEmpty() const;
	bool add(const double& newLoad);
	bool remove();

	/** @pre The priority queue is not empty. */
	ItemType peek() const throw(PrecondViolatedExcep);
}; // end Heap_PriorityQueue

#include "Heap_PriorityQueue.cpp"
#endif