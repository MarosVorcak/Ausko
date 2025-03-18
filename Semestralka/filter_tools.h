#ifndef FILTER_H  
#define FILTER_H
#include "routing_record.h"
#include <vector>

using namespace std;
template<typename inputIterator, typename predicate>
vector<RoutingRecord> filter(inputIterator begin, inputIterator end, predicate pred) {
	vector<RoutingRecord> result;
	for (inputIterator it = begin; it != end; ++it) {
		if (pred(*it)) {
			result.push_back(*it);
		}
	}
	return result;
}
#endif 