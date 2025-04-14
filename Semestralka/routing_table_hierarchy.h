#pragma once
#include <libds/amt/explicit_hierarchy.h>
#include "csv_parser.h"
#include <vector>
#include <string>

class RTNode {
private:
    int octetValue;
    std::vector<RoutingRecord*> pointerToRecords;
public:
    RTNode();
    RTNode(int octetValue);
    void setOctetValue(int octetValue);
    int getOctetValue();
    void addPointer(RoutingRecord* pointer);
    bool operator==(const RTNode& other) const;
    RTNode& operator=(const RTNode& other);
};

class RoutingTable {
private:
    ds::amt::MultiWayExplicitHierarchy<RTNode> hierarchy;
    std::vector<RoutingRecord> loadedRecords;
public:
    RoutingTable(const std::string& fileName);
    void initHierarchy(const std::vector<RoutingRecord>& loadedRecords);
    void addIP(const std::string& ip, RoutingRecord* pointerToRecord);
    void printSize();
};

RTNode::RTNode() {
    this->octetValue = 0;
}

RTNode::RTNode(int octetValue) {
    this->octetValue = octetValue;
}

void RTNode::setOctetValue(int octetValue) {
    this->octetValue = octetValue;
}

int RTNode::getOctetValue() {
    return this->octetValue;
}

void RTNode::addPointer(RoutingRecord* pointer) {
    this->pointerToRecords.push_back(pointer);
}

bool RTNode::operator==(const RTNode& other) const {
    return this->octetValue == other.octetValue;
}

RTNode& RTNode::operator=(const RTNode& other) {
    if (this == &other) {
        return *this;
    }
    this->octetValue = 0;
    this->pointerToRecords.clear();
    this->octetValue = other.octetValue;
    this->pointerToRecords = other.pointerToRecords;
    return *this;
}

RoutingTable::RoutingTable(const std::string& fileName) {
    this->loadedRecords = parseCSV(fileName);
    this->initHierarchy(loadedRecords);
}

void RoutingTable::initHierarchy(const std::vector<RoutingRecord>& loadedRecords) {
    this->hierarchy.emplaceRoot().data_ = RTNode();
    for (RoutingRecord record : loadedRecords) {
        this->addIP(record.getPrefixAdd(), &record);
    }
}

void RoutingTable::addIP(const std::string& ip, RoutingRecord* pointerToRecord) {
    std::stringstream ss(ip);
    std::string octet;
    std::vector<int> octets;

    while (std::getline(ss, octet, '.')) {
        octets.push_back(std::stoi(octet));
    }

    decltype(auto) currentNode = this->hierarchy.accessRoot();
    for (int currentOctet : octets) {
        bool found = false;

        for (decltype(auto) son : *currentNode->sons_) {
            if (son->data_.getOctetValue() == currentOctet) {
                currentNode = son;
                found = true;
                break;
            }
        }

        if (!found) {
            size_t index = currentNode->sons_->size();
            decltype(auto) newNode = this->hierarchy.emplaceSon(*currentNode, index);
            newNode.data_ = RTNode(currentOctet);
            currentNode = &newNode;
        }
    }
    currentNode->data_.addPointer(pointerToRecord);
}

void RoutingTable::printSize() {
    std::cout << "Current size is: " << this->hierarchy.size();
}