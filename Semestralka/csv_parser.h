#ifndef CSV_PARSER_H
#define CSV_PARSER_H


#include "routing_record.h"
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void stripWord(string& str, const string& word);
vector<RoutingRecord> parseCSV(const string& filename);



#endif
