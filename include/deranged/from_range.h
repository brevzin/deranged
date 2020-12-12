#ifndef DERANGED_FROM_RANGE_H
#define DERANGED_FROM_RANGE_H

#include <ranges>

namespace drng {

template <std::ranges::view V>
class CppView {
    struct WithSize {
        WithSize(V& v)
            : value(std::ranges::size(v))
        { }
        size_t value;
    };
    struct WithoutSize {
        WithoutSize(V&) { }
    };

    static constexpr bool store_size =
        std::ranges::sized_range<V> and not std::sized_sentinel_for<
            std::ranges::sentinel_t<V>, std::ranges::iterator_t<V>>;


    V view;
    std::ranges::iterator_t<V> first;
    [[no_unique_address]] std::conditional_t<store_size, WithSize, WithoutSize> size_cache;

public:
    explicit CppView(V view)
        : view(std::move(view))
        , first(std::ranges::begin(this->view))
        , size_cache(this->view)
    { }

    auto empty() const -> bool {
        return first == std::ranges::end(view);
    }

    void pop_front() {
        ++first;
        if constexpr (store_size) {
            --size_cache.value;
        }
    }

    auto front() -> decltype(auto) {
        return *first;
    }

    auto size() const -> size_t
        requires std::ranges::sized_range<V>
    {
        if constexpr (store_size) {
            return size_cache.value;
        } else {
            return std::ranges::end(view) - first;
        }
    }
};

template <std::ranges::viewable_range R>
auto from_range(R&& r) {
    return CppView(std::views::all(r));
}

}

#endif
