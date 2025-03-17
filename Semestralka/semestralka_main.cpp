#include <iostream>
#include "csv_parser.h"
#include "time_tools.h"
#include "filter_tools.h"


int main()
{
	vector<RoutingRecord> records = parseCSV("RT.csv");

	string testNextHop = "12.0.1.63";

	vector<RoutingRecord> filtered = filter(records.begin(), records.end(), [&](const RoutingRecord record) { return record.getNextHopAdd() == testNextHop;});

	for (RoutingRecord record : filtered)
	{
		record.print();
	}

	return 0;
    
}


