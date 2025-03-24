#pragma once
#include <string>
#include <iostream>
using namespace std;
class RoutingRecord
{
private:
	string lifeTime;
	string prefixAdd;
	int prefixMask;
	string nextHopAdd;
	
public:
	RoutingRecord();
	RoutingRecord(string lifeTime, string prefixAdd, int preffixMask, string nextHopAdd);
	string getLifeTime();
	string getPrefixAdd();
	int getPrefixMask();
	string getNextHopAdd();
	void print();
};

