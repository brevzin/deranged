#ifndef DERANGED_FROM_RANGE_H
#define DERANGED_FROM_RANGE_H

#include <ranges>

namespace drng {

template <std::input_or_output_iterator I, std::sentinel_for<I> S>
class iter_range {
    I first;
    S last;

public:
    iter_range(I first, S last)
        : first(std::move(first))
        , last(std::move(last))
    { }

    auto empty() const -> bool {
        return first == last;
    }

    void pop_front() {
        ++first;
    }

    auto front() -> decltype(auto) {
        return *first;
    } 
};

template <std::ranges::viewable_range R>
auto from_range(R&& r) {
    return iter_range(std::ranges::begin(r), std::ranges::end(r));
}

}

#endif
