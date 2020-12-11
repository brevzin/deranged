#ifndef DERANGED_IOTA_H
#define DERANGED_IOTA_H

namespace drng {

template <std::weakly_incrementable W, std::semiregular Bound = std::unreachable_sentinel_t>
    requires std::equality_comparable_with<W, Bound>
          && std::semiregular<W>
class iota {
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
};

}

#endif
