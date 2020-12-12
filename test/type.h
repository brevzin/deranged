#ifndef DERANGED_TYPE_H
#define DERANGED_TYPE_H

#include <string>
#include <typeinfo>
#include <memory>
#include <cxxabi.h>
#include <cstdlib>
#include "catch.hpp"

namespace drng {

template <typename T>
struct type_t { };

template <typename T>
inline constexpr type_t<T> type{};

template <typename T>
constexpr auto operator==(type_t<T>, type_t<T>) -> bool {
    return true;
}

template <typename T, typename U>
constexpr auto operator==(type_t<T>, type_t<U>) -> bool {
    return false;
}

template <typename T>
auto demangle(char const* name) -> std::string {
    std::unique_ptr<char, decltype(&std::free)> own{
        abi::__cxa_demangle(name, nullptr, nullptr, nullptr),
        std::free
    };

    std::string r = own ? own.get() : name;
    using TR = std::remove_reference_t<T>;
    if (std::is_const_v<TR>) r += " const";
    if (std::is_volatile_v<TR>) r += " volatile";
    if (std::is_lvalue_reference_v<T>) r += "&";
    if (std::is_rvalue_reference_v<T>) r += "&&";
    return r;
}

template <typename T>
auto demangle() -> std::string {
    return demangle<T>(typeid(std::remove_reference_t<T>).name());
}

}

namespace Catch {

template <typename T>
struct StringMaker<drng::type_t<T>> {
    static auto convert(drng::type_t<T>) -> std::string {
        return drng::demangle<T>();
    }
};

}

#endif
