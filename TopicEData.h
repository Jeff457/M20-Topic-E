/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic E Project						*
*												*
*			TopicEData.h				 		*
*			Status: Working              		*
************************************************/

#ifndef _TOPIC_E_DATA
#define _TOPIC_E_DATA

#include <iostream>
#include <vector>
using namespace std;

class TopicEData
{
	friend std::ostream &operator<< (std::ostream& out, const TopicEData& box);

private:
	static int seqInc;  // Keeps track of the number of boxes

	double totLoad;  // Sum of all weight in the box
	int seqNum;  // nth box
	vector<double> loads;  // Holds the individual weights in the box

public:
	TopicEData() : totLoad(0), seqNum(seqInc), loads(0) { ++seqInc; }
	TopicEData(const double& load);
	
	double getTotalLoad() const { return this->totLoad; }

	bool isBoxFull() const { return (this->totLoad >= 0.99); }
	bool addLoad(const double& load);


	TopicEData operator= (const TopicEData& right);
	double operator+=(const double& right);
	double operator+ (const double& right) { return (this->totLoad + right); }

	bool operator!=(const TopicEData& right) const	{ return (this->totLoad != right.totLoad); }
	bool operator==(const TopicEData& right) const	{ return (this->totLoad == right.totLoad); }
	bool operator>=(const TopicEData& right) const	{ return (this->totLoad >= right.totLoad); }
	bool operator<=(const TopicEData& right) const	{ return (this->totLoad <= right.totLoad); }
	bool operator> (const TopicEData& right) const	{ return (this->totLoad >  right.totLoad); }
	bool operator< (const TopicEData& right) const	{ return (this->totLoad <  right.totLoad); }
};

#endif