#ifndef DERANGED_IOTA_H
#define DERANGED_IOTA_H

#include <deranged/range_base.h>
#include <deranged/concepts.h>

namespace drng {

template <typename T, typename U>
concept weak_equality_comparable_with = requires (cref<T> t, cref<U> u) {
    { t == u } -> std::convertible_to<bool>;
    { t != u } -> std::convertible_to<bool>;
    { u == t } -> std::convertible_to<bool>;
    { u != t } -> std::convertible_to<bool>;
};

template <std::weakly_incrementable W, std::semiregular Bound = std::unreachable_sentinel_t>
    requires weak_equality_comparable_with<W, Bound>
          && std::semiregular<W>
class iota : public RangeBase<iota<W, Bound>> {
    W value_;
    Bound bound_ = {};

public:
    iota(W value)
        : value_(std::move(value))
    { }

    iota(W value, Bound bound)
        : value_(std::move(value))
        , bound_(std::move(bound))
    { }

    auto empty() const -> bool {
        return value_ == bound_;
    }

    void pop_front() {
        ++value_;
    }

    auto front() -> W {
        return value_;
    }

    auto size() const -> size_t
        requires requires { { bound_ - value_ } -> std::convertible_to<size_t>; }
    {
        return bound_ - value_;
    }
};

}

#endif
