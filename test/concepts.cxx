#include "catch.hpp"
#include <deranged/concepts.h>
#include <vector>

TEST_CASE("concepts basics") {
    struct A {
        void pop_front();
        auto front() -> int;
        auto empty() const -> bool;
    };
    STATIC_REQUIRE(drng::input_drange<A>);
    STATIC_REQUIRE(drng::input_drange<A&>);
    STATIC_REQUIRE(drng::input_drange<A&&>);
    STATIC_REQUIRE_FALSE(drng::input_drange<A const>);
    STATIC_REQUIRE_FALSE(drng::input_drange<A const&>);
    STATIC_REQUIRE_FALSE(drng::input_drange<A const&&>);
    STATIC_REQUIRE(drng::forward_drange<A>);
    STATIC_REQUIRE(drng::forward_drange<A&>);
    STATIC_REQUIRE(drng::forward_drange<A&&>);

    // missing const
    struct B {
        void pop_front();
        auto front() -> int;
        auto empty() -> bool;
    };
    STATIC_REQUIRE_FALSE(drng::input_drange<B>);
    STATIC_REQUIRE_FALSE(drng::input_drange<B&>);
    STATIC_REQUIRE_FALSE(drng::input_drange<B&&>);
    STATIC_REQUIRE_FALSE(drng::input_drange<B const>);
    STATIC_REQUIRE_FALSE(drng::input_drange<B const&>);
    STATIC_REQUIRE_FALSE(drng::input_drange<B const&&>);

    // move-only
    struct C : A {
        C(C&&) = default;
        C& operator=(C&&) = default;
    };
    STATIC_REQUIRE(drng::input_drange<C>);
    STATIC_REQUIRE(drng::input_drange<C&>);
    STATIC_REQUIRE(drng::input_drange<C&&>);
    STATIC_REQUIRE_FALSE(drng::input_drange<C const>);
    STATIC_REQUIRE_FALSE(drng::input_drange<C const&>);
    STATIC_REQUIRE_FALSE(drng::input_drange<C const&&>);
    STATIC_REQUIRE_FALSE(drng::forward_drange<C>);
    STATIC_REQUIRE_FALSE(drng::forward_drange<C&>);
    STATIC_REQUIRE_FALSE(drng::forward_drange<C&&>);
}
