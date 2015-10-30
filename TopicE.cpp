/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic E Project						*
*												*
*			TopicE.cpp					 		*
*			Status: Working              		*
************************************************/

#pragma warning ( disable: 4290 )

#include <fstream>
#include <string>

#include "TopicEData.h"
#include "Heap_PriorityQueue.h"

using namespace std;

void readFile(Heap_PriorityQueue<TopicEData>& boxPQ);
void full(const vector<TopicEData>& fullBoxes);
int inHeap(Heap_PriorityQueue<TopicEData>& boxPQ);

int main()
{
	Heap_PriorityQueue<TopicEData> boxPQ;

	readFile(boxPQ);

	cout << "\n\nProgram Over\n\n";
	cout << "Press Enter to end -->  ";
	cin.ignore();
}  // end main


/* 
	Reads data from valid file and gives it to Priority Queue
	Remove full boxes from Priority Queue and places in buffer
	Displays data read in from file
	Calls methods full and inHeap to display boxes that are full and that are still in the heap
*/
void readFile(Heap_PriorityQueue<TopicEData>& boxPQ)
{
	string fileName = "TopicEin.txt";
	ifstream inFile(fileName);

	vector<double> fileData;
	double dataBuffer;
	int totalDataItems = 0;

	vector<TopicEData> fullBoxes;

	while (!inFile)
	{
		cout << fileName << " cannot be opened.  Enter another file name -->  ";
		cin >> fileName;
		cin.ignore();
		inFile.clear();
		inFile.open(fileName);
	}

	// Gets data and puts in Priority Queue
	// Removes any full boxes from the Queue
	while (inFile >> dataBuffer)
	{
		fileData.push_back(dataBuffer);
		boxPQ.add(dataBuffer);
		if (boxPQ.peek() >= 0.99 && boxPQ.peek() <= 1.0)
		{
			fullBoxes.push_back(boxPQ.peek());
			boxPQ.remove();
		}
		totalDataItems++;  // counts the number of items in file
	}
	inFile.close();

	// Display the data from the file
	cout << "Valid data entered is:\n";
	for (auto weights : fileData)
		cout << weights << " ";
	cout << endl << totalDataItems << " is the total number of valid data items" << endl;

	// Display full boxes
	full(fullBoxes);

	// Display boxes still in heap
	int boxesInHeap = inHeap(boxPQ);

	cout << (boxesInHeap + fullBoxes.size()) << " is the total number of boxes\n";
	cout << totalDataItems << " is the total number of items";

	fileData.clear();
	fullBoxes.clear();
}  // end readFile

// Display boxes removed from Heap
void full(const vector<TopicEData>& fullBoxes)
{
	cout << "\nBoxes which are considered to be full:\n";
	for (auto weights : fullBoxes)
		cout << weights << endl;
	cout << "\nThere are " << fullBoxes.size() << " boxes considered to be full\n\n";
}  // end full

// Display boxes still in Heap
int inHeap(Heap_PriorityQueue<TopicEData>& boxPQ)
{
	vector<TopicEData> boxesInHeap;
	int nthBox = 0;
	int numInHeap;

	while (!boxPQ.isEmpty())
	{
		try
		{
			boxesInHeap.push_back(boxPQ.peek());
			boxPQ.remove();
		}
		catch (const std::exception&)
		{
			boxesInHeap.clear();
		}
	}

	numInHeap = boxesInHeap.size();
	cout << "Boxes still in heap:\n";
	for (auto weights : boxesInHeap)
	{
		cout << ++nthBox << ".  ";
		cout << weights << endl;
	}
	cout << "\nThere are " << numInHeap << " boxes in the heap\n\n";
	boxesInHeap.clear();
	return numInHeap;
}  // end inHeap