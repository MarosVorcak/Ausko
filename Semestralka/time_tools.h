#ifndef TIME_TOOLS_H
#define TIME_TOOLS_H

#include <string>
#include <sstream>

using namespace std;
int convertToSecs(const string& timeStr);
bool isTimeInRange(const string& timeStr, const string& startTime, const string& endTime);

#endif 