#pragma once
#include <string>
#include <iostream>
#include <cstdint> 
#include "ip_tools.h" 
#include "time_tools.h"

class RoutingRecord {
private:
    std::string lifeTime;
    int lifeTimeSecs;
    std::string prefixAdd;
    std::uint32_t prefixAddBits;
    int prefixMask;
    std::string nextHopAdd;

public:
    RoutingRecord() {
        this->lifeTime = "";
        this->lifeTimeSecs = 0;
        this->prefixAdd = "";
        this->prefixAddBits = 0;
        this->prefixMask = 0;
        this->nextHopAdd = "";
    }

    RoutingRecord(std::string& lifeTime, std::string& prefixAdd, int prefixMask, std::string& nextHopAdd) {
        this->lifeTime = lifeTime;
        this->lifeTimeSecs = convertToSecs(lifeTime);
        this->prefixAdd = prefixAdd;
		this->prefixAddBits = ipToUint32(prefixAdd);
        this->prefixMask = prefixMask;
        this->nextHopAdd = nextHopAdd;
    }

    std::string& getLifeTime() {
        return this->lifeTime;
    }

    std::string& getPrefixAdd() {
        return this->prefixAdd;
    }

    std::uint32_t& getPrefixAddBits() {
        return this->prefixAddBits;
    }

    int getPrefixMask() {
        return this->prefixMask;
    }

    std::string& getNextHopAdd() {
        return this->nextHopAdd;
    }

    int getLifeTimeSecs() {
        return this->lifeTimeSecs;
    }

    const int getLifeTimeSecs() const {
        return this->lifeTimeSecs;
    }

    const std::string& getLifeTime() const {
        return this->lifeTime;
    }

    const std::string& getPrefixAdd() const {
        return this->prefixAdd;
    }

    const std::uint32_t& getPrefixAddBits() const {
        return this->prefixAddBits;
    }

    const int& getPrefixMask() const {
        return this->prefixMask;
    }

    const std::string& getNextHopAdd() const {
        return this->nextHopAdd;
    }

    void print() {
        std::cout << "Lifetime: " << getLifeTime()
            << " Prefix Address: " << getPrefixAdd()
            << " Prefix Mask: " << getPrefixMask()
            << " Next-hop Address: " << getNextHopAdd()
            << '\n';
    }

   void print() const {
        std::cout << "Lifetime: " << getLifeTime()
            << " Prefix Address: " << getPrefixAdd()
            << " Prefix Mask: " << getPrefixMask()
            << " Next-hop Address: " << getNextHopAdd()
            << '\n';
    }
};