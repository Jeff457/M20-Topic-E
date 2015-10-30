/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic E Project						*
*												*
*			ArrayMaxHeap.cpp			 		*
*			Status: Working              		*
************************************************/

#include "ArrayMaxHeap.h"

//==============================
//		Private Methods
//==============================

template<class ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
	return (2 * nodeIndex) + 1;
}  // end getLeftChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(const int nodeIndex) const
{
	return (2 * nodeIndex) + 2;
}  // end getRightChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(const int nodeIndex) const
{
	return (nodeIndex - 1) / 2;
}  // end getParentIndex

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(const int nodeIndex) const
{
	return ( (getLeftChildIndex(nodeIndex) > itemCount - 1) );
}  // end isLeaf

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(int subTreeRootIndex)
{
	if (!isLeaf(subTreeRootIndex))
	{
		int largerChildIndex = getLeftChildIndex(subTreeRootIndex);

		// Check if root has a right child
		if (getRightChildIndex(subTreeRootIndex) < itemCount)
		{
			int rightChildIndex = largerChildIndex + 1;
			if (items[rightChildIndex] > items[largerChildIndex])
				largerChildIndex = rightChildIndex;
		}

		if (items[subTreeRootIndex] < items[largerChildIndex])
		{
			ItemType swapBuffer = items[largerChildIndex];
			items[largerChildIndex] = items[subTreeRootIndex];
			items[subTreeRootIndex] = swapBuffer;
			heapRebuild(largerChildIndex);
		}
	}
}  // end heapRebuild

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
	for (int index = itemCount / 2; index >= 0; index--)
	{
		heapRebuild(index);
	}  // end for
}  // end heapCreate


//==============================
//		Public Methods
//==============================

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap()
{
	items = new ItemType[DEFAULT_CAPACITY];
	itemCount = 0;
	maxItems = DEFAULT_CAPACITY;
}  // end constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::
ArrayMaxHeap(const ItemType someArray[], const int arraySize) :
	itemCount(arraySize), maxItems(2 * arraySize)
{
	// Allocate the array
	items = new ItemType[2 * arraySize];

	// Copy given values into the array
	for (int i = 0; i < itemCount; i++)
		items[i] = someArray[i];

	// Reorganize the array into a heap
	heapCreate();
} // end constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{
	clear();
}  // end destructor

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const
{
	return ( itemCount == 0 );
}  // end isEmpty

template<class ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const
{
	return itemCount;
}  // end getNumberOfNodes

template<class ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const
{
	return static_cast<int>( ceil( log( itemCount + 1.0 ) / log( 2.0 ) ) );
}  // end getHeight

template<class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const throw(PrecondViolatedExcep)
{
	if ( isEmpty() )
		throw PrecondViolatedExcep("Attempted peek into an empty heap.");

	return items[0];
} // end peekTop

template<class ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType & newData)
{
	// Insert data into the bottom of the tree
	items[itemCount] = newData;

	//Trickle new item up to the appropriate spot in the tree
	int newDataIndex = itemCount;
	bool inPlace = false;
	
	while ( (newDataIndex >= 0) && !inPlace )
	{
		int parentIndex = getParentIndex(newDataIndex);
		if (items[newDataIndex] <= items[parentIndex])
			inPlace = true;
		else
		{
			ItemType swapBuffer = items[parentIndex];
			items[parentIndex] = items[newDataIndex];
			items[newDataIndex] = swapBuffer;
			newDataIndex = parentIndex;
		}
	}
	itemCount++;

	return inPlace;
}  // end add

template<class ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
	if ( isEmpty() )
		return false;
	else
	{
		// Special case, only 1 node
		if (itemCount == 1)
		{
			clear();
		}
		else
		{
			// Copy the item from the last node and place it into the root
			items[0] = items[itemCount - 1];
			// Remove the last node
			itemCount--;
			// Rebuild the heap
			heapRebuild(0);
		}

		return true;
	}
}  // end remove

template<class ItemType>
void ArrayMaxHeap<ItemType>::clear()
{
	itemCount = 0;
}  // end clear
