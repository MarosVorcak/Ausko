#ifndef CSV_PARSER_H
#define CSV_PARSER_H


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
		string prefixMask;
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
				prefixMask = cell;
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
		RoutingRecord record(lifeTime, prefixAdd, prefixMask, nextHopAdd);
		records.push_back(record);
	}
	return records;
}




#endif
