#ifndef DERANGED_ALGORITHM_H
#define DERANGED_ALGORITHM_H

#include <deranged/concepts.h>
#include <deranged/range_base.h>

namespace drng {

namespace impl {

template <input_drange R, std::regular_invocable<reference_t<R>> F>
class MapResult : public RangeBase<MapResult<R, F>>
{
    R input;
    F func;

public:
    MapResult(R input, F func)
        : input(std::move(input))
        , func(std::move(func))
    { }

    auto empty() const {
        return input.empty();
    }

    void pop_front() {
        input.pop_front();
    }

    auto front() -> decltype(auto) {
        return std::invoke(func, input.front());
    }

    auto size() const -> size_t requires sized_drange<R> {
        return input.size();
    }
};

}

// map(r, f) produces the range [f(e) for e in r]
// the resulting range preserves the range category of r, except that the result
// is never contiguous.
inline constexpr auto map = []<input_drange R, std::regular_invocable<reference_t<R>> F>(R r, F f){
    return impl::MapResult(r, f);
};

// equal(a, b) is true if all the elements of a and b compare equal with == and
// a and b have the same number of elements
inline constexpr auto equal = []<input_drange A, input_drange B>(A a, B b) -> bool {
    // can't compare infinite ranges
    static_assert(not (infinite_drange<A> and infinite_drange<B>));

    // but if only one of them is infinite, that's clearly false
    if constexpr (infinite_drange<A> or infinite_drange<B>) {
        return false;
    }

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
};

}

#endif
