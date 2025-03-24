#include "routing_record.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void stripWord(std::string& str, const std::string& word) {
	size_t pos = str.find(word);
	if (pos != std::string::npos) {
		str.erase(pos, word.length());
	}

	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

vector<RoutingRecord> parseCSV(const string& filename) {
	vector<RoutingRecord> records;
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Error opening file" << endl;
		return records;
	}

	string line;
	bool firstLine = true;
	while (getline(file, line)) {
		if (firstLine) {
			firstLine = false;
			continue;
		}

		stringstream ss(line);
		string cell;
		int collumIndex = 0;

		string lifeTime;
		string prefixAdd;
		int prefixMask = 0;
		string nextHopAdd;

		while (getline(ss, cell, ';')) {
			switch (collumIndex) {
			case 0:
				break;
			case 1:
				lifeTime = cell;
				break;
			case 2:
				prefixAdd = cell;
				break;
			case 3:
				if (!cell.empty()) {
					prefixMask = stoi(cell);
				}
				else {		
					cout << "Warning: Empty prefix mask in CSV file" << endl;
				}
				break;
			case 4:
				break;
			case 5:
				nextHopAdd = cell;
				stripWord(nextHopAdd, "via");
				break;
			default:
				break;
			}
			collumIndex++;
		}
		records.emplace_back(lifeTime, prefixAdd, prefixMask, nextHopAdd);
	}
	return records;
}




