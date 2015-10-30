/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic E Project						*
*												*
*			Heap_PriorityQueue.cpp		 		*
*			Status: Working              		*
************************************************/

#include "Heap_PriorityQueue.h"

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::ableToAdd(const double& newLoad)
{
	ItemType rootBox;

	try 
	{
		rootBox = ArrayMaxHeap<ItemType>::peekTop();
	}
	catch (exception emptyHeap)
	{
		// Heap is empty; No boxes can support the new load
		// Put boxes back on the heap
		for (unsigned int i = 0; i < boxBuffer.size(); i++)
			ArrayMaxHeap<ItemType>::add(boxBuffer[i]);

		boxBuffer.clear();
		return false;
	}

	// Weight can be added to the box
	if ( (rootBox + newLoad) <= MAX_CAPACITY)
	{
		remove();  // Remove root
		rootBox += newLoad;  // Add new weight to box
		ArrayMaxHeap<ItemType>::add(rootBox);  // Add box to queue
		
		// Put back any boxes taken off heap
		for (unsigned int i = 0; i < boxBuffer.size(); i++)
			ArrayMaxHeap<ItemType>::add(boxBuffer[i]);

		boxBuffer.clear();
		return true;
	}
	else
	{
		// Add root to buffer, remove it from the heap, try the next box
		boxBuffer.push_back(rootBox);
		remove();
		return ableToAdd(newLoad);
	}
}  // end ableToAdd



template<class ItemType>
Heap_PriorityQueue<ItemType>::Heap_PriorityQueue()
{
	ArrayMaxHeap<ItemType>();
}  // end constructor

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::isEmpty() const
{
	return ArrayMaxHeap<ItemType>::isEmpty();
}  // end isEmpty

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::add(const double& newLoad)
{
	if (ableToAdd(newLoad))
		return true;
	else
	{
		// All boxes are too full to add the new weight
		ItemType newBox;
		newBox += newLoad;
		return ArrayMaxHeap<ItemType>::add(newBox);
	}
}  // end add

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::remove()
{
	return ArrayMaxHeap<ItemType>::remove();
}  // end remove

template<class ItemType>
ItemType Heap_PriorityQueue<ItemType>::peek() const throw(PrecondViolatedExcep)
{
	try
	{
		return ArrayMaxHeap<ItemType>::peekTop();
	}
	catch (PrecondViolatedExcep e)
	{
		throw PrecondViolatedExcep("Attempted peek into an empty priority queue.");
	}  // end try/catch
}  // end peek