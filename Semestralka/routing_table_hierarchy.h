#pragma once
#include <libds/amt/explicit_hierarchy.h>
#include "csv_parser.h"
#include <vector>
#include <string>

class RTNode {
	private:
		int octetValue;
	public:
		RTNode();
		RTNode(int octetValue);
		void setOctetValue(int octetValue);
		int getOctetValue();
};

class FinalRTNode : public RTNode {
	private:
		std::vector<RoutingRecord*> recordPointers;
	public:
		void addPointer(RoutingRecord* pointer);
};

class RoutingTable {
	private:
		ds::amt::MultiWayExplicitHierarchy<RTNode> hierarchy;
		std::vector<RoutingRecord> loadedRecords;
	public:
		RoutingTable(const std::string& fileName);
		void initHierarchy(const std::vector<RoutingRecord>& loadedRecords);
		void addIP(const std::string& ip, RoutingRecord* pointerToRecord);
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

void FinalRTNode::addPointer(RoutingRecord* pointer) {
	this->recordPointers.push_back(pointer);
};

RoutingTable::RoutingTable(const std::string& fileName) {
	this->loadedRecords = parseCSV(fileName);
	this->initHierarchy(loadedRecords);
}

void RoutingTable::initHierarchy(const std::vector<RoutingRecord>& loadedRecords) {
	this->hierarchy.emplaceRoot();
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

	if (octets.size() != 4) {
		throw std::invalid_argument("Invalid IP format");
	}
	auto currentNode = this->hierarchy.accessRoot();
	for (int i = 0; i < 4; ++i) {
		if (currentNode->sons_->size() == 0) {
			for (int j = 0; j < 4; ++j) {
				int octetValue = octets[i];

				if (j == 3) {
					auto newNode = this->hierarchy.emplaceSon(*currentNode,currentNode->sons_->size()+1);
					currentNode = &newNode;
					FinalRTNode* finalNode = dynamic_cast<FinalRTNode*>(*currentNode);
					if (finalNode) {
						finalNode->addPointer(pointerToRecord);
					}

				}

			}

			return;
		}
		int currentOctet = octets[i];
		bool found;
	}
}

