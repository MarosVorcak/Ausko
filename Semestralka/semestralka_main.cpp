#include <iostream>
#include "filter_tools.h"
#include "time_tools.h"
#include "routing_table_hierarchy.h"
void showMenu() {
    std::cout << "======Menu======" << '\n';
    std::cout << "1. Filter by lifetime" << '\n';
    std::cout << "2. Filter by nexthop address" << '\n';
    std::cout << "3. Filter by matching with prefix address" << '\n';
    std::cout << "4. Exit the part" << '\n';
    std::cout << "Enter your choice: ";
}

void showParts() {
    std::cout << "======Parts======" << "\n";
    std::cout << "1. Part1 (simple vector)" << '\n';
    std::cout << "2. Part2 (explicit hierarchy)" << '\n';
    std::cout << "3. Exit the program" << '\n';
    std::cout << "Enter your choice: ";
}

void showMovementOptions() {
    std::cout << "Chose where to move" << "\n";
    std::cout << "1. To parent" << "\n";
    std::cout << "2. To son" << "\n";
    std::cout << "3. Start filtering" << "\n";
    std::cout << "Enter your choice: ";
}

void printFiltered(std::vector<RoutingRecord>& filteredVector) {
    for (RoutingRecord& record : filteredVector) {
        record.print();
    }
}

int main() {
    initHeapMonitor();
    std::vector<RoutingRecord> records = parseCSV("RT.csv");
    RoutingTable rt(records);
    auto currentNode = RoutingTableIterator(&rt.getHierarchy(), rt.getHierarchy().accessRoot());
    auto end = RoutingTableIterator(&rt.getHierarchy(), nullptr);
    std::vector<RoutingRecord> filtered;
    int choice, inputMask, octetValue, part;
    std::string minimum, maximum, inputAdd, confirmation;
    auto matchWithLifetimeByReference = [&](RoutingRecord& record) {
        return isTimeInRange(record.getLifeTime(), minimum, maximum);
        };
    auto matchWithAdressByReference = [&](RoutingRecord& record) {
        return doesIPMatch(record.getPrefixAddBits(), inputMask, ipToUint32(inputAdd));
        };
    auto matchWithNextHopByReference = [&](RoutingRecord& record) {
        return record.getNextHopAdd() == inputAdd;
        };
    auto matchWithLifetimeByPointer = [&](RoutingRecord* record) {
        return isTimeInRange(record->getLifeTime(), minimum, maximum);
        };
    auto matchWithAdressByPointer = [&](RoutingRecord* record) {
        return doesIPMatch(record->getPrefixAddBits(), inputMask, ipToUint32(inputAdd));
        };
    auto matchWithNextHopByPointer = [&](RoutingRecord* record) {
        return record->getNextHopAdd() == inputAdd;
        };
    auto insertToFiltered = [&](RoutingRecord& record) {
        filtered.push_back(record);
        };
    auto insertPointerToFiltered = [&](RoutingRecord* record) {
        filtered.push_back(*record);
        };
    auto processRecordsWithLifetime = [&](RTNode& node) {
        Filter::filter(node.getPointers().begin(), node.getPointers().end(), matchWithLifetimeByPointer, insertPointerToFiltered);
        };
    auto processRecordsWithNextHop = [&](RTNode& node) {
        Filter::filter(node.getPointers().begin(), node.getPointers().end(), matchWithNextHopByPointer, insertPointerToFiltered);
        };
    auto processRecordsWithAddress = [&](RTNode& node) {
        Filter::filter(node.getPointers().begin(), node.getPointers().end(), matchWithAdressByPointer, insertPointerToFiltered);
        };

    auto isLeaf = [&](RTNode& node) {
        return node.getPointers().size() > 0;
        };
    while (true) {
        bool filtering = true;
        bool navigating = true;
        showParts();
        std::cin >> part;
        switch (part) {
        case 1:
            filtered.clear();
            while (filtering) {
                showMenu();
                std::cin >> choice;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid input. Please enter a number." << '\n';
                    continue;
                }

                switch (choice) {
                case 1:
                    std::cout << "Enter minimum life time (example >> 1w4d3h or 6:25:20): ";
                    std::cin >> minimum;
                    std::cout << "Enter maximum life time (example >> 1w4d3h or 6:25:20): ";
                    std::cin >> maximum;
                    Filter::filter(records.begin(), records.end(), matchWithLifetimeByReference, insertToFiltered);
                    printFiltered(filtered);
                    break;

                case 2:
                    std::cout << "Enter a nexthop address (example >> 192.168.1.10): ";
                    std::cin >> inputAdd;
                    Filter::filter(records.begin(), records.end(), matchWithNextHopByReference, insertToFiltered);
                    printFiltered(filtered);
                    break;

                case 3:
                    std::cout << "Enter address you want to match (example >> 192.168.1.10): ";
                    std::cin >> inputAdd;
                    std::cout << "Enter max prefix you want to match (1-31): ";
                    std::cin >> inputMask;
                    Filter::filter(records.begin(), records.end(), matchWithAdressByReference, insertToFiltered);
                    printFiltered(filtered);
                    break;
                case 4:
                    std::cout << "Are you sure you want to exit? (y/n): ";
                    std::cin >> confirmation;
                    if (confirmation == "y" || confirmation == "Y") {
                        filtering = false;
                        std::cout << "Exiting...\n";
                    }
                    break;

                default:
                    std::cout << "Invalid choice. Try again.\n";
                }

                if (choice >= 1 && choice <= 3) {
                    std::cout << "Filter applied. Current results: " << filtered.size() << " records." << '\n';
                    filtered.clear();
                }
            }
            break;
        case 2:
            filtered.clear();
            while (navigating) {
                showMovementOptions();
                std::cin >> choice;
                switch (choice) {
                case 1:
                    currentNode.toParent();
                    break;
                case 2:
                    std::cout << "Enter octet value: ";
                    std::cin >> octetValue;
                    currentNode.toSon(octetValue);
                    break;
                case 3:
                    navigating = false;
                    break;
                default:
                    std::cout << "Invalid choice. Try again.\n";
                }
            }
            while (filtering) {
                showMenu();
                std::cin >> choice;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid input. Please enter a number." << '\n';
                    continue;
                }

                switch (choice) {
                case 1:
                    std::cout << "Enter minimum life time (example >> 1w4d3h or 6:25:20): ";
                    std::cin >> minimum;
                    std::cout << "Enter maximum life time (example >> 1w4d3h or 6:25:20): ";
                    std::cin >> maximum;
                    Filter::filter(currentNode, end, isLeaf, processRecordsWithLifetime);
                    printFiltered(filtered);
                    break;

                case 2:
                    std::cout << "Enter a nexthop address (example >> 192.168.1.10): ";
                    std::cin >> inputAdd;
                    Filter::filter(currentNode, end, isLeaf, processRecordsWithNextHop);
                    printFiltered(filtered);
                    break;

                case 3:
                    std::cout << "Enter address you want to match (example >> 192.168.1.10): ";
                    std::cin >> inputAdd;
                    std::cout << "Enter max prefix you want to match (1-31): ";
                    std::cin >> inputMask;
                    Filter::filter(currentNode, end, isLeaf, processRecordsWithAddress);
                    printFiltered(filtered);
                    break;
                case 4:
                    std::cout << "Are you sure you want to exit? (y/n): ";
                    std::cin >> confirmation;
                    if (confirmation == "y" || confirmation == "Y") {
                        filtering = false;
                        std::cout << "Exiting...\n";
                    }
                    break;

                default:
                    std::cout << "Invalid choice. Try again.\n";
                }

                if (choice >= 1 && choice <= 3) {
                    std::cout << "Filter applied. Current results: " << filtered.size() << " records." << '\n';
                    filtered.clear();
                }
            }
            break;
        case 3:
            std::cout << "Are you sure you want to exit? (y/n): ";
            std::cin >> confirmation;
            if (confirmation == "y" || confirmation == "Y") {
                std::cout << "Exiting...\n";
                return 0;
            }
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }

}
