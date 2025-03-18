#include <iostream>
#include "csv_parser.h"
#include "time_tools.h"
#include "filter_tools.h"
#include "ip_tools.h"

int main() {
	vector<RoutingRecord> records = parseCSV("RT.csv");
	return 0;

}


