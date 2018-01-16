#include <vector>

#include <array_view.hpp>
#include <catch.hpp>

namespace ext = snsinfu::ext;

TEST_CASE("array_view can access vector elements")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> view = ext::view(vector);
}
