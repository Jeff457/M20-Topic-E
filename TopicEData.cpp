/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic E Project						*
*												*
*			TopicEData.cpp				 		*
*			Status: Working              		*
************************************************/

#include "TopicEData.h"

int TopicEData::seqInc = 1;

TopicEData::TopicEData(const double& load)
{
	seqNum = ++seqInc;
	loads.push_back(load);
	totLoad = load;
}  // end constructor

bool TopicEData::addLoad(const double& load)
{
	// Box can only hold up to 1.0 units
	if ( (this->totLoad + load) > 1 )
		return false;
	else
	{
		loads.push_back(load);
		totLoad += load;
		return true;
	}
}  // end addLoad

TopicEData TopicEData::operator=(const TopicEData& right)
{
	this->loads.clear();
	this->totLoad = 0;

	this->totLoad += right.totLoad;
	this->seqNum = ++seqInc;

	for (unsigned int i = 0; i < right.loads.size(); i++)
		this->loads.push_back(right.loads[i]);

	return *this;
}  // end overloaded = operator

double TopicEData::operator+=(const double& right)
{
	if ( (this->totLoad + right) > 1 )
		return 0.0;
	else
	{
		this->loads.push_back(right);
		return this->totLoad += right;
	}
}  // end overloaded += operator

ostream &operator<<(ostream& out, const TopicEData& box)
{
	out << "For box "			<< box.seqNum
		<< ", Total Items: "	<< box.loads.size()
		<< ", Total Load: "		<< box.getTotalLoad()
		<< ", consisting of ";
	
	for (auto weights : box.loads)
		out << weights << "  ";

	return out;
}  // end overloaded << operator
