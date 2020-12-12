#include "catch.hpp"
#include <deranged/iota.h>
#include <deranged/concepts.h>

TEST_CASE("iota finite") {
    auto r = drng::iota(0, 10);
    STATIC_REQUIRE(drng::input_drange<decltype(r)>);
    STATIC_REQUIRE(drng::forward_drange<decltype(r)>);
    STATIC_REQUIRE(drng::sized_drange<decltype(r)>);

    for (int i = 0; i < 10; ++i) {
        REQUIRE_FALSE(r.empty());
        CHECK(r.front() == i);
        CHECK(r.size() == size_t(10 - i));
        r.pop_front();
    }
}

TEST_CASE("iota infinite") {
    auto r = drng::iota(0);
    STATIC_REQUIRE(drng::input_drange<decltype(r)>);
    STATIC_REQUIRE(drng::forward_drange<decltype(r)>);
    STATIC_REQUIRE_FALSE(drng::sized_drange<decltype(r)>);

    for (int i = 0; i < 100; ++i) {
        REQUIRE_FALSE(r.empty());
        CHECK(r.front() == i);
        r.pop_front();
    }
}
