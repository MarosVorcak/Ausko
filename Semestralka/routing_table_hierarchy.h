#pragma once
#include <libds/amt/explicit_hierarchy.h>
#include "csv_parser.h"
#include <vector>
#include <string>


class RTNode {
private:
    int octetValue;
    std::vector<RoutingRecord*> pointersToRecords;
public:
    RTNode();
    RTNode(int octetValue);
    void setOctetValue(int octetValue);
    int getOctetValue();
    void printRecords();
    std::vector< RoutingRecord*>& getPointers();
    void addPointer(RoutingRecord* pointer);
    bool operator==(const RTNode& other) const;
    RTNode& operator=(const RTNode& other);
};

class RoutingTable {
private:
    ds::amt::MultiWayExplicitHierarchy<RTNode> hierarchy;
public:
    RoutingTable(const std::vector<RoutingRecord>& loadedRecrods);
    void initHierarchy(const std::vector<RoutingRecord>& loadedRecords);
    void addIP(const std::string& ip, const RoutingRecord* pointerToRecord);
    ds::amt::MultiWayExplicitHierarchy<RTNode>& getHierarchy();
    void printSize();
};

class RoutingTableIterator : public ds::amt::MultiWayExplicitHierarchy<RTNode>::PreOrderHierarchyIterator {
    public:
        RoutingTableIterator(ds::amt::MultiWayExplicitHierarchy<RTNode>* hierarchy, ds::amt::MultiWayExplicitHierarchyBlock<RTNode>* position);
        void toParent();
        void toSon(int nodeValue);
};

RoutingTableIterator::RoutingTableIterator(ds::amt::MultiWayExplicitHierarchy<RTNode>* hierarchy, ds::amt::MultiWayExplicitHierarchyBlock<RTNode>* position):
    ds::amt::MultiWayExplicitHierarchy<RTNode>::PreOrderHierarchyIterator(hierarchy, position) {

}

void RoutingTableIterator::toParent() {
    if (this->currentPosition_->currentNode_ == this->hierarchy_->accessRoot()) {
        std::cout << "You are root" << "\n";
        return;
    }
    auto parent = this->hierarchy_->accessParent(*this->currentPosition_->currentNode_);
    this->currentPosition_->currentNode_ = parent;
}

void RoutingTableIterator::toSon(int nodeValue) {
    if (this->hierarchy_->isLeaf(*this->currentPosition_->currentNode_)) {
        std::cout << "There is no sons" << "\n";
        return;
    }
    auto sons = *this->currentPosition_->currentNode_->sons_;
    for (decltype(auto) son : sons) {
        if (son->data_.getOctetValue() == nodeValue) {
            this->currentPosition_->currentNode_ = son;
            return;
        }
    }
    std::cout << "There is no son with this value" << "\n";
}



RTNode::RTNode() {
    this->octetValue = 0;
}

RTNode::RTNode(int octetValue) {
    this->octetValue = octetValue;
}

void RTNode::setOctetValue(int octetValue) {
    this->octetValue = octetValue;
}

std::vector<RoutingRecord*>& RTNode::getPointers() {
    return this->pointersToRecords;
}

void RTNode::printRecords() {
    if (this->pointersToRecords.size() > 0) {
        for (const RoutingRecord* pointer : pointersToRecords) {
            pointer->print();
        }
    };
}


int RTNode::getOctetValue() {
    return this->octetValue;
}

void RTNode::addPointer(RoutingRecord* pointer) {
    this->pointersToRecords.push_back(pointer);
}

bool RTNode::operator==(const RTNode& other) const {
    return this->octetValue == other.octetValue;
}

RTNode& RTNode::operator=(const RTNode& other) {
    if (this == &other) {
        return *this;
    }
    this->octetValue = 0;
    this->pointersToRecords.clear();
    this->octetValue = other.octetValue;
    this->pointersToRecords = other.pointersToRecords;
    return *this;
}

RoutingTable::RoutingTable(const std::vector<RoutingRecord>& loadedRecords) {
    this->initHierarchy(loadedRecords);
}

void RoutingTable::initHierarchy(const std::vector<RoutingRecord>& loadedRecords) {
    this->hierarchy.emplaceRoot().data_ = RTNode();
    for (const RoutingRecord& record : loadedRecords) {
        this->addIP(record.getPrefixAdd(), &record);
    }
}

ds::amt::MultiWayExplicitHierarchy<RTNode>& RoutingTable::getHierarchy() {
    return this->hierarchy;
}

void RoutingTable::addIP(const std::string& ip, const RoutingRecord* pointerToRecord) {
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
    currentNode->data_.addPointer(const_cast<RoutingRecord*>(pointerToRecord));
}

void RoutingTable::printSize() {
    std::cout << "Current size is: " << this->hierarchy.size() << "\n";
}