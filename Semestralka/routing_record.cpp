#include "routing_record.h"


RoutingRecord::RoutingRecord() {
	this->lifeTime = "";
	this->prefixAdd = "";
	this->prefixMask = 0;
	this->nextHopAdd = "";

}

RoutingRecord::RoutingRecord(string lifeTime, string prefixAdd, int preffixMask, string nextHopAdd) {
	this->lifeTime = lifeTime;
	this->prefixAdd = prefixAdd;
	this->prefixMask = preffixMask;
	this->nextHopAdd = nextHopAdd;

}

string RoutingRecord::getLifeTime() {
	return this->lifeTime;
}

string RoutingRecord::getPrefixAdd() {
	return this->prefixAdd;
}

int RoutingRecord::getPrefixMask() {
	return this->prefixMask;
}

string RoutingRecord::getNextHopAdd() {
	return this->nextHopAdd;
}

void RoutingRecord::print() {
	std::cout << "Lifetime: " << getLifeTime()
		<< " Prefix Address: " << getPrefixAdd()
		<< " Prefix Mask: " << getPrefixMask()
		<< " Next-hop Address: " << getNextHopAdd()
		<< '\n';  
}
