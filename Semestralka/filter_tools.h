#include "routing_record.h"
#include <vector>

using namespace std;

class Filter {
public:
    template<typename inputIterator, typename predicate>
    static vector<RoutingRecord> filter(inputIterator begin, inputIterator end, predicate pred) {
        vector<RoutingRecord> result;
        for (inputIterator it = begin; it != end; ++it) {
            if (pred(*it)) {
                result.push_back(*it);
            }
        }
        return result;
    }
};
