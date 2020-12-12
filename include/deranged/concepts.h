#ifndef DERANGED_CONCEPTS_H
#define DERANGED_CONCEPTS_H

#include <concepts>

namespace drng {

template <typename T>
concept non_void = not std::same_as<T, void>;

template <typename T>
using cref = std::remove_reference_t<T> const&;

// maybe reconsider if R& should count as a range at some point
template <typename R>
concept input_drange = std::movable<std::remove_reference_t<R>>
    && requires (R r, cref<R> cr) {
        { cr.empty() } -> std::same_as<bool>;
        { r.pop_front() } -> std::same_as<void>;
        { r.front() } -> non_void;
    };

template <typename R>
concept forward_drange = input_drange<R> && std::copyable<std::remove_reference_t<R>>;

template <typename R>
concept sized_drange = input_drange<R>
    && requires (cref<R> cr) {
        { cr.size() } -> std::same_as<size_t>;
    };

}

#endif
