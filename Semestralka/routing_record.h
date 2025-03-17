#pragma once
#include "time_tools.h"
#include <string>
#include <iostream>
using namespace std;
class RoutingRecord
{

private:
	string lifeTime;
	string prefixAdd;
	string preffixMask;
	string nextHopAdd;
public:
	RoutingRecord();
	RoutingRecord(string lifeTime, string prefixAdd, string preffixMask, string nextHopAdd);
	string getLifeTime();
	string getPrefixAdd();
	string getPreffixMask();
	string getNextHopAdd() const;
	void print();
};

