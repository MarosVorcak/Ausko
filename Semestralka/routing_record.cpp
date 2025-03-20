#include "routing_record.h"


RoutingRecord::RoutingRecord() {
	this->lifeTime = "";
	this->prefixAdd = "";
	this->preffixMask = 0;
	this->nextHopAdd = "";

}

RoutingRecord::RoutingRecord(string lifeTime, string prefixAdd, int preffixMask, string nextHopAdd) {
	this->lifeTime = lifeTime;
	this->prefixAdd = prefixAdd;
	this->preffixMask = preffixMask;
	this->nextHopAdd = nextHopAdd;

}

string RoutingRecord::getLifeTime() {
	return this->lifeTime;
}

string RoutingRecord::getPrefixAdd() {
	return this->prefixAdd;
}

int RoutingRecord::getPreffixMask() {
	return this->preffixMask;
}

string RoutingRecord::getNextHopAdd() {
	return this->nextHopAdd;
}

void RoutingRecord::print() {
	cout << this->getLifeTime() << " " << this->getPrefixAdd() << " " << this->getPreffixMask() << " " << this->getNextHopAdd() << endl;
}
