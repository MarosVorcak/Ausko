#ifndef IP_TOOLS_H
#define IP_TOOLS_H

#include <string>
#include <sstream>
#include <bitset>
#include <vector>
using namespace std;

vector<int> decToBinIP(const string& ip) {
	vector<int> result;
	stringstream ss(ip);
	string octet;
	while (getline(ss, octet, '.')) {
		bitset<8> octetBin(stoi(octet));
		for (int i = 7; i >= 0; i--) { 
			result.push_back(octetBin[i] ? 1 : 0);
		}
	}
	return result;
}

//string decToBinIP(const string& ip) {
//	string result;
//	stringstream ss(ip);
//	string octet;
//	int count = 0;
//	while (getline(ss, octet, '.')) {
//		bitset<8> octetBin(stoi(octet));
//		result += octetBin.to_string();
//
//		if (count < 3) {
//			result += ".";
//		}
//		count++;
//	}
//	return result;
//}


bool doesIPMatch(const string& prefixAdd, int prefixMask, const string& comparedAdd) {
	auto prefixAddBin = decToBinIP(prefixAdd);
	auto comparedAddBin = decToBinIP(comparedAdd);
	for (int i = 0; i < prefixMask; i++) {
		if (prefixAddBin[i] != comparedAddBin[i]) {
			return false;
		}
	}
	return true;
}
#endif 