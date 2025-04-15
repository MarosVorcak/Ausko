#pragma once
#include "routing_record.h"
#include <vector>

class Filter {
public:
    template<typename inputIterator, typename predicate, typename operation>
    static void filter(inputIterator begin, inputIterator end, predicate pred, operation oper) {
        for (inputIterator it = begin; it != end; ++it) {
            if (pred(*it)) {
                oper(*it);
            }
        }
    }
};
