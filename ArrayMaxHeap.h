/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic E Project						*
*												*
*			ArrayMaxHeap.h				 		*
*			Status: Working              		*
************************************************/

#ifndef _ARRAY_MAX_HEAP
#define _ARRAY_MAX_HEAP

#include "HeapInterface.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class ArrayMaxHeap : public HeapInterface<ItemType>
{
private:
	static const int ROOT_INDEX = 0;        // Helps with readability
	static const int DEFAULT_CAPACITY = 150;
	ItemType* items;                        // Array of heap items
	int itemCount;                          // Current count of heap items
	int maxItems;                           // Maximum capacity of the heap

	// ---------------------------------------------------------------------
	// Most of the private utility methods use an array index as a parameter
	// and in calculations. This should be safe, even though the array is an
	// implementation detail, since the methods are private.
	// ---------------------------------------------------------------------

	// Returns the array index of the left child (if it exists).
	int getLeftChildIndex(const int nodeIndex) const;

	// Returns the array index of the right child (if it exists).
	int getRightChildIndex(const int nodeIndex) const;

	// Returns the array index of the parent node.
	int getParentIndex(const int nodeIndex) const;

	// Tests whether this node is a leaf.
	bool isLeaf(const int nodeIndex) const;

	// Converts a semiheap to a heap.
	void heapRebuild(int subTreeRootIndex);

	// Creates a heap from an unordered array.
	void heapCreate();

public:
	ArrayMaxHeap();
	ArrayMaxHeap(const ItemType someArray[], const int arraySize);
	virtual ~ArrayMaxHeap();

	// HeapInterface Public Methods:
	bool isEmpty() const;
	int getNumberOfNodes() const;
	int getHeight() const;
	ItemType peekTop() const throw(PrecondViolatedExcep);
	bool add(const ItemType& newData);
	bool remove();
	void clear();
}; // end ArrayMaxHeap

#include "ArrayMaxHeap.cpp"
#endif