#include <string>
#include <sstream>

int convertToSecs(const std::string& timeStr) {
	int result = 0;
	if (timeStr.find(":") != std::string::npos) {
		std::stringstream ss(timeStr);
		std::string token;
		int factors[] = { 3600, 60, 1 };
		for (int i = 0; std::getline(ss, token, ':'); ++i) {
			result += std::stoi(token) * factors[i];
		}
	}
	else {
		std::string number;
		for (char c : timeStr) {
			if (std::isdigit(c)) {
				number += c;
			}
			else {
				if (c == 'h') result += std::stoi(number) * 3600;
				else if (c == 'd') result += std::stoi(number) * 86400;
				else if (c == 'w') result += std::stoi(number) * 604800;
				number.clear();
			}
		}
	}
	return result;
}

bool isTimeInRange(const std::string& timeStr, const std::string& startTime, const std::string& endTime) {
	int time = convertToSecs(timeStr);
	int start = convertToSecs(startTime);
	int end = convertToSecs(endTime);
	return time >= start && time <= end;
}
