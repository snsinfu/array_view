#include <vector>

#include <array_view.hpp>
#include <catch.hpp>

namespace ext = snsinfu::ext;

TEST_CASE("array_view can access vector elements")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> view = ext::view(vector);

    SECTION("reading elements via indices")
    {
        CHECK(view[0] == 0);
        CHECK(view[2] == 2);
    }

    SECTION("modifying elements via indexing")
    {
        view[0] = 100;
        CHECK(vector[0] == 100);
    }
}
