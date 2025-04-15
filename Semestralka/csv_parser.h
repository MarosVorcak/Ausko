#pragma once
#include "routing_record.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

void stripWord(std::string& str, const std::string& word) {
	size_t pos = str.find(word);
	if (pos != std::string::npos) {
		str.erase(pos, word.length());
	}

	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

std::vector<RoutingRecord> parseCSV(const std::string& filename) {
	std::vector<RoutingRecord> records;
	records.reserve(10000);
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "Error opening file" << std::endl;
		return records;
	}

	std::string line;
	bool firstLine = true;
	while (std::getline(file, line)) {
		if (firstLine) {
			firstLine = false;
			continue;
		}

		std::stringstream ss(line);
		std::string cell;
		int collumIndex = 0;

		std::string lifeTime;
		std::string prefixAdd;
		int prefixMask = 0;
		std::string nextHopAdd;

		while (std::getline(ss, cell, ';')) {
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
					prefixMask = std::stoi(cell);
				}
				else {		
					std::cout << "Warning: Empty prefix mask in CSV file" << std::endl;
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
