#include "routing_record.h"

RoutingRecord::RoutingRecord() {
	this->lifeTime = "";
	this->prefixAdd = "";
	this->prefixAddBits = 0; 
	this->prefixMask = 0;
	this->nextHopAdd = "";
}

RoutingRecord::RoutingRecord(std::string& lifeTime, std::string& prefixAdd, int prefixMask, std::string& nextHopAdd) {
	this->lifeTime = lifeTime;
	this->prefixAdd = prefixAdd;
	this->prefixAddBits = ipToUint32(prefixAdd);
	this->prefixMask = prefixMask;
	this->nextHopAdd = nextHopAdd;
}

std::string& RoutingRecord::getLifeTime() {
	return this->lifeTime;
}

std::string& RoutingRecord::getPrefixAdd() {
	return this->prefixAdd;
}

std::uint32_t& RoutingRecord::getPrefixAddBits() {
	return this->prefixAddBits; 
}

int& RoutingRecord::getPrefixMask() {
	return this->prefixMask;
}

std::string& RoutingRecord::getNextHopAdd() {
	return this->nextHopAdd;
}
const std::string& RoutingRecord::getLifeTime() const {
	return this->lifeTime;
}

const std::string& RoutingRecord::getPrefixAdd() const {
	return this->prefixAdd;
}

const std::uint32_t& RoutingRecord::getPrefixAddBits() const {
	return this->prefixAddBits;
}

const int& RoutingRecord::getPrefixMask() const {
	return this->prefixMask;
}

const std::string& RoutingRecord::getNextHopAdd() const {
	return this->nextHopAdd;
}


void RoutingRecord::print() {
	std::cout << "Lifetime: " << getLifeTime()
		<< " Prefix Address: " << getPrefixAdd()
		<< " Prefix Mask: " << getPrefixMask()
		<< " Next-hop Address: " << getNextHopAdd()
		<< '\n';
}