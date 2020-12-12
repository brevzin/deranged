#include "catch.hpp"
#include <deranged/concepts.h>
#include <deranged/from_range.h>
#include <vector>
#include <list>

TEST_CASE("from_range vector") {
    std::vector<int> v = {1, 2, 3};
    auto r = drng::from_range(v);
    STATIC_REQUIRE(drng::input_drange<decltype(r)>);
    STATIC_REQUIRE(drng::sized_drange<decltype(r)>);

    CHECK_FALSE(r.empty());
    CHECK(r.front() == 1);
    CHECK(r.size() == 3);
    r.pop_front();
    CHECK_FALSE(r.empty());
    CHECK(r.front() == 2);
    CHECK(r.size() == 2);
    r.pop_front();
    CHECK_FALSE(r.empty());
    CHECK(r.front() == 3);
    CHECK(r.size() == 1);
    r.pop_front();
    CHECK(r.empty());
    CHECK(r.size() == 0);
}

TEST_CASE("from_range list") {
    std::list<int> v = {4, 5};
    auto r = drng::from_range(v);
    STATIC_REQUIRE(drng::input_drange<decltype(r)>);
    STATIC_REQUIRE(drng::sized_drange<decltype(r)>);

    CHECK_FALSE(r.empty());
    CHECK(r.front() == 4);
    CHECK(r.size() == 2);
    r.pop_front();
    CHECK_FALSE(r.empty());
    CHECK(r.front() == 5);
    CHECK(r.size() == 1);
    r.pop_front();
    CHECK(r.empty());
    CHECK(r.size() == 0);
}
