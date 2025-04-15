#include <iostream>
#include "filter_tools.h"
#include "time_tools.h"
#include "routing_table_hierarchy.h"
void showMenu() {
    std::cout << "======Menu======" << '\n';
    std::cout << "1. Filter by lifetime" << '\n';
    std::cout << "2. Filter by nexthop address" << '\n';
    std::cout << "3. Filter by matching with prefix address" << '\n';
    std::cout << "4. Print filtered data structure" << '\n';
    std::cout << "5. Exit the program" << '\n';
    std::cout << "Enter your choice: ";
}

void printFiltered(std::vector<RoutingRecord>& filteredVector) {
    for (RoutingRecord& record : filteredVector) {
        record.print();
    }
}

int main() {
    std::vector<RoutingRecord> records = parseCSV("RT.csv");
    RoutingTable rt(records);
    auto currentNode = RoutingTableIterator(&rt.getHierarchy(),rt.getHierarchy().accessRoot());
    auto end = RoutingTableIterator(&rt.getHierarchy(), nullptr);
    std::vector<RoutingRecord> filtered;
    int choice, inputMask, octetValue;
    std::string minimum, maximum, inputAdd, confirmation;
    auto isLeaf = [&](RTNode& node) {
           return node.getPointers().size() > 0;
        };

    auto matchWithLifetime = [&](RoutingRecord& record) {
        return isTimeInRange(record.getLifeTime(), minimum, maximum);
        };
    auto matchWithAdress = [&](RoutingRecord& record) {
        return doesIPMatch(record.getPrefixAddBits(), inputMask, ipToUint32(inputAdd));
        };
    auto matchWithNextHop = [&](RoutingRecord& record) {
        return record.getNextHopAdd() == inputAdd;
        };
    while (true) {
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
            filtered = Filter::filter(records.begin(), records.end(), matchWithLifetime);
            printFiltered(filtered);
            break;

        case 2: 
            std::cout << "Enter a nexthop address (example >> 192.168.1.10): ";
            std::cin >> inputAdd;
            filtered = Filter::filter(records.begin(), records.end(), matchWithNextHop);
            printFiltered(filtered);
            break;

        case 3: 
            std::cout << "Enter address you want to match (example >> 192.168.1.10): ";
            std::cin >> inputAdd;
            std::cout << "Enter max prefix you want to match (1-31): ";
            std::cin >> inputMask;
            filtered = Filter::filter(records.begin(), records.end(), matchWithAdress);
            printFiltered(filtered);
            break;

        case 4: 
            std::cout << "Current filtered results (" << filtered.size() << " records):" << '\n';
            printFiltered(filtered);
            break;

        case 5: 
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

        if (choice >= 1 && choice <= 3) {
            std::cout << "Filter applied. Current results: " << records.size() << " records." << '\n';
            std::cout << "Continue filtering? (y/n): ";
            std::cin >> confirmation;
            if (confirmation != "y" && confirmation != "Y") {
                records = records;
            }
        }
    }
}

