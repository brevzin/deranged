#include "catch.hpp"
#include <deranged/concepts.h>
#include <deranged/from_range.h>
#include <vector>

TEST_CASE("from_range") {
    std::vector<int> v = {1, 2, 3};
    auto r = drng::from_range(v);
    CHECK_FALSE(r.empty());
    CHECK(r.front() == 1);
    r.pop_front();
    CHECK_FALSE(r.empty());
    CHECK(r.front() == 2);
    r.pop_front();
    CHECK_FALSE(r.empty());
    CHECK(r.front() == 3);
    r.pop_front();
    CHECK(r.empty());

    STATIC_REQUIRE(drng::input_drange<decltype(r)>);
}
