#include <array_view.hpp>
#include <array_view.hpp> // Test include guard
#include <catch.hpp>

TEST_CASE("array_view<int> is defined")
{
    CHECK(sizeof(ext::array_view<int>) > 0);
}
