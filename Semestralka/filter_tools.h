#include "routing_record.h"
#include <vector>

class Filter {
public:
    template<typename inputIterator, typename predicate>
    static std::vector<RoutingRecord> filter(inputIterator begin, inputIterator end, predicate pred) {
        std::vector<RoutingRecord> result;
        for (inputIterator it = begin; it != end; ++it) {
            if (pred(*it)) {
                result.push_back(*it);
            }
        }
        return result;
    }
};
