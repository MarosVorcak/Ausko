#pragma once
#include <libds/adt/table.h>
#include <libds/adt/list.h>
#include <libds/heap_monitor.h>
#include "routing_record.h"
using listType = ds::adt::SinglyLinkedList<const RoutingRecord*>*;
using tableType = ds::adt::Treap<std::string, listType>;
class RoutingTable {	
private:
	tableType table;
public:
	RoutingTable(const std::vector<RoutingRecord>& records);
	void initTable(const std::vector<RoutingRecord>& records);
	void addRecord(const RoutingRecord* record);
	void printKeys();
	tableType& getTable();
	~RoutingTable();
};

RoutingTable::RoutingTable(const std::vector<RoutingRecord>& records) {
	initTable(records);
}

inline void RoutingTable::initTable(const std::vector<RoutingRecord>& records) {
	for (const RoutingRecord& record : records) {
		addRecord(&record);
	}
}

inline void RoutingTable::addRecord(const RoutingRecord* record) {
	listType* data = nullptr;
	if (this->table.tryFind(record->getNextHopAdd(), data)) {
		(*data)->insertFirst(record);
	}
	else {
		auto data = new ds::adt::SinglyLinkedList<const RoutingRecord*>;
		data->insertFirst(record);
		this->table.insert(record->getNextHopAdd(), data);
	}
}

void RoutingTable::printKeys() {
	for (auto& item : this->table) {
		std::cout << item.key_ << "\n";
	}
}

inline tableType& RoutingTable::getTable() {
	return this->table;
}

inline RoutingTable::~RoutingTable() {
	for (auto& list : this->table) {
		delete list.data_;
		list.data_ = nullptr;
	}
}
