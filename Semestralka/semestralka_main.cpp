#include <iostream>
#include "csv_parser.h"
#include "filter_tools.h"
#include "ip_tools.h"
#include "time_tools.h"

void showMenu() {
    cout << "======Menu======" << endl;
    cout << "1. Filter by lifetime" << endl;
    cout << "2. Filter by nexthop address" << endl;
    cout << "3. Filter by matching with prefix address" << endl;
    cout << "4. Print filtered data structure" << endl;
    cout << "5. Reset all filters" << endl;
    cout << "6. Exit the program" << endl;
    cout << "Enter your choice: ";
}

void printFiltered(vector<RoutingRecord>& filteredVector) {
    for (RoutingRecord& record : filteredVector) {
        record.print();
    }
}

int main() {
    vector<RoutingRecord> records = parseCSV("RT.csv");
    vector<RoutingRecord> workingSet = records;
    vector<RoutingRecord> filtered;
    int choice;
    string minimum, maximum, inputAdd, confirmation;

    while (true) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(10000, '\n'); 
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter minimum life time (example >> 1w4d3h or 6:25:20): ";
            cin >> minimum;
            cout << "Enter maximum life time (example >> 1w4d3h or 6:25:20): ";
            cin >> maximum;
            filtered = Filter::filter(workingSet.begin(), workingSet.end(), 
                [&](RoutingRecord& record) {
                    return isTimeInRange(record.getLifeTime(), minimum, maximum);
                });
            workingSet = filtered;
            printFiltered(workingSet);
            break;

        case 2: 
            cout << "Enter a nexthop address (example >> 192.168.1.10): ";
            cin >> inputAdd;
            filtered = Filter::filter(workingSet.begin(), workingSet.end(), 
                [&](RoutingRecord& record) {
                    return record.getNextHopAdd() == inputAdd;
                });
            workingSet = filtered;
            printFiltered(workingSet);
            break;

        case 3: 
            cout << "Enter address you want to match (example >> 192.168.1.10): ";
            cin >> inputAdd;
            filtered = Filter::filter(workingSet.begin(), workingSet.end(), 
                [&](RoutingRecord& record) {
                    return doesIPMatch(record.getPrefixAdd(), 8, inputAdd);
                });
            workingSet = filtered;
            printFiltered(workingSet);
            break;

        case 4: 
            cout << "Current filtered results (" << workingSet.size() << " records):" << endl;
            printFiltered(workingSet);
            break;

        case 5:
            workingSet = records;
            cout << "All filters reset. Working with full dataset (" << workingSet.size() << " records)." << endl;
            break;

        case 6: 
            cout << "Are you sure you want to exit? (y/n): ";
            cin >> confirmation;
            if (confirmation == "y" || confirmation == "Y") {
                cout << "Exiting...\n";
                return 0;
            }
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

        if (choice >= 1 && choice <= 3) {
            cout << "Filter applied. Current results: " << workingSet.size() << " records." << endl;
            cout << "Continue filtering? (y/n): ";
            cin >> confirmation;
            if (confirmation != "y" && confirmation != "Y") {
                workingSet = records;
            }
        }
    }
}