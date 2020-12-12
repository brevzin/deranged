#ifndef DERANGED_RANGE_BASE_H
#define DERANGED_RANGE_BASE_H

namespace drng {

#define DRNG_FWD(x) static_cast<decltype(x)&&>(x)

template <typename Derived>
class RangeBase
{
    auto self() -> Derived& {
        return *static_cast<Derived*>(this);
    }

public:
    // the "pipeline" operator.
    // Instead of implement operator| to write out x | transform(f) | filter(g)
    // this library makes you write x._(transform, f)._(filter, g)
    // It's arguably little more awkward to read but chains easier with .
    template <typename F, typename... Args>
        requires std::invocable<F&&, Derived&, Args&&...>
    auto _(F&& f, Args&&... args) & -> decltype(auto) {
        return std::invoke(DRNG_FWD(f), self(), DRNG_FWD(args)...);
    }

    template <typename F, typename... Args>
        requires std::invocable<F&&, Derived&, Args&&...>
    auto _(F&& f, Args&&... args) && -> decltype(auto) {
        return std::invoke(DRNG_FWD(f), std::move(self()), DRNG_FWD(args)...);
    }
};

}

#endif
