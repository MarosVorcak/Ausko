#ifndef TIME_TOOLS_H
#define TIME_TOOLS_H

#include <string>
#include <sstream>

using namespace std;
int convertToSecs(const string& timeStr) {
	int result = 0;
	if (timeStr.find(":") != string::npos) {
		stringstream ss(timeStr);
		string token;
		int factors[] = { 3600, 60, 1 };
		for (int i = 0; getline(ss, token, ':'); ++i) {
			result += stoi(token) * factors[i];
		}
	}
	else {
		string number;
		for (char c : timeStr) {
			if (isdigit(c)) {
				number += c;
			}
			else {
				if (c == 'h') result += stoi(number) * 3600;
				else if (c == 'd') result += stoi(number) * 86400;
				else if (c == 'w') result += stoi(number) * 604800;
				number.clear();
			}
		}
	}
	return result;
}

bool isTimeInRange(const string& timeStr, const string& startTime, const string& endTime) {
	int time = convertToSecs(timeStr);
	int start = convertToSecs(startTime);
	int end = convertToSecs(endTime);
	return time >= start && time <= end;
}


#endif 