#include "catch.hpp"
#include <vector>
#include <deranged/from_range.h>
#include <deranged/algorithm.h>
#include <deranged/iota.h>

TEST_CASE("equal") {
    std::vector<int> v = {1, 2, 3};
    CHECK(drng::equal(drng::from_range(v), drng::iota(1, 4)));
}
