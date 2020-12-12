#ifndef DERANGED_ALGORITHM_H
#define DERANGED_ALGORITHM_H

#include <deranged/concepts.h>

namespace drng {

template <input_drange A, input_drange B>
auto equal(A a, B b) -> bool {
    if constexpr (sized_drange<A> and sized_drange<B>) {
        if (a.size() != b.size()) {
            return false;
        }
    }

    while (not a.empty() and not b.empty()) {
        if (a.front() != b.front()) {
            return false;
        }

        a.pop_front();
        b.pop_front();
    }

    return a.empty() and b.empty();
}

}

#endif
