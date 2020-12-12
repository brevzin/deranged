#ifndef DERANGED_CONCEPTS_H
#define DERANGED_CONCEPTS_H

#include <concepts>

namespace drng {

template <typename T>
concept non_void = not std::same_as<T, void>;

template <typename T>
using cref = std::remove_reference_t<T> const&;

template <typename T, typename... Ts>
concept any_of = (std::same_as<T, Ts> or ... );

// maybe reconsider if R& should count as a range at some point
template <typename R>
concept input_drange = std::movable<std::remove_reference_t<R>>
    and requires (R r, cref<R> cr) {
        { cr.empty() } -> any_of<bool, std::false_type>;
        { r.pop_front() } -> std::same_as<void>;
        { r.front() } -> non_void;
    };

template <typename R>
concept forward_drange = input_drange<R> and std::copyable<std::remove_reference_t<R>>;

template <typename R>
concept infinite_drange = input_drange<R>
    and requires (cref<R> cr) {
        { cr.empty() } -> std::same_as<std::false_type>;
    };

template <typename R>
concept finite_drange = input_drange<R> and not infinite_drange<R>;

template <typename R>
concept sized_drange = input_drange<R>
    and requires (cref<R> cr) {
        { cr.size() } -> std::same_as<size_t>;
    };

template <typename R>
using value_t = typename R::value_type;

template <typename R>
using reference_t = decltype(std::declval<R&>().front());

}

#endif
