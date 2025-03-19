#include <iostream>
#include "csv_parser.h"
#include "filter_tools.h"
#include "ip_tools.h"
#include "time_tools.h"

//64.71.137.241
void showMenu() {
	cout << "======Menu======" << endl;
	cout << "1. Filter by lifetime" << endl;
	cout << "2. Filter by nexthop address" << endl;
	cout << "3. Filter by matching with prefix address" << endl;
	cout << "4. Print filtered data structure" << endl;
	cout << "5. Exit the program" << endl;
	cout << "Enter your choice: ";
}

void printFiltered(vector<RoutingRecord>& filteredVector) {
	string confirmation;
	cout << "Do you want to print out the filtered data structure? (y/n): ";
	cin >> confirmation;

	if (confirmation == "y" || confirmation == "Y") {
		for (RoutingRecord& record : filteredVector) {
			record.print();
		}
	}
	else {
		cout << "Skipping print.\n";
	}
}

int main() {
	vector<RoutingRecord> records = parseCSV("RT.csv");
	int choice;
	while (true) {
		showMenu();
		cin >> choice;

		if (cin.fail()) {
			cin.clear(); 
			cin.ignore(10000, '\n'); 
			cout << "Invalid input. Please enter a number." << endl;
			continue;
		}

		string minimum;
		string maximum;
		string inputAdd;
		string exitChoice;
		vector<RoutingRecord> filtered;

		switch (choice) {
		case 1:
			cout << "Enter minimum life time (example >> 1w4d3h or 6:25:20): ";
			cin >> minimum;
			cout << "Enter minimum life time (example >> 1w4d3h or 6:25:20): ";
			cin >> maximum;
			filtered = filter(records.begin(), records.end(), [&](RoutingRecord& record) {return isTimeInRange(record.getLifeTime(), minimum, maximum);});
			printFiltered(filtered);
			break;
		case 2:
			cout << "Enter a nexthop address (example >> 192.168.1.10): ";
			cin >> inputAdd;
			filtered = filter(records.begin(), records.end(), [&](RoutingRecord& record) {return record.getNextHopAdd() == inputAdd;});
			printFiltered(filtered);
			break;
		case 3:
			cout << "Enter address you want to match (example >> 192.168.1.10): ";
			cin >> inputAdd;
			filtered = filter(records.begin(), records.end(), [&](RoutingRecord& record) {return doesIPMatch(record.getPrefixAdd(), 8, inputAdd); });
			printFiltered(filtered);
			break;
		case 4:
			cout << "Printing filtered data structure: " << endl;
			printFiltered(filtered);
			break;
		case 5:
			cout << "Are you sure you want to exit? (y/n): ";
			cin >> exitChoice;

			if (exitChoice == "y" || exitChoice == "Y") {
				cout << "Exiting...\n";
				return 0;
			}
			break;
			return 0;
		default:
			cout << "Invalid choice. Try again.\n";
		}

	}
}


