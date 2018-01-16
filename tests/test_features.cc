#include <array>
#include <vector>

#include <array_view.hpp>
#include <catch.hpp>

namespace ext = snsinfu::ext;

TEST_CASE("array_view can access vector elements")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::view(vector);

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

    SECTION("accessing front and back elements")
    {
        CHECK(view.front() == 0);
        CHECK(view.back() == 3);
    }

    SECTION("getting raw pointer")
    {
        CHECK(view.data() == vector.data());
    }

    SECTION("getting the number of elements")
    {
        CHECK(view.size() == vector.size());
    }

    SECTION("iterating with range interface")
    {
        for (int& elm : view) {
            elm += 10;
        }
        CHECK(vector == std::vector<int>{10, 11, 12, 13});
    }

    SECTION("indexing with bounds-check")
    {
        CHECK_NOTHROW(view.at(0));
        CHECK_THROWS_AS(view.at(view.size()), std::out_of_range);
    }

    SECTION("reverse iterator")
    {
        auto beg = view.rbegin();
        auto end = view.rend();

        auto it = beg;
        CHECK(*it == vector.back());

        it += view.end() - view.begin();
        CHECK(it == end);
    }
}

TEST_CASE("array_view can access built-in arrays")
{
    int array[] = {0, 1, 2, 3};

    SECTION("smoke test")
    {
        ext::array_view<int> view = ext::view(array);
    }

    SECTION("won't throw")
    {
        CHECK(noexcept(ext::view(array)));
    }
}

TEST_CASE("array_view can access std::array")
{
    std::array<int, 4> array = {{0, 1, 2, 3}};

    SECTION("smoke test")
    {
        ext::array_view<int> view = ext::view(array);
    }

    SECTION("won't throw")
    {
        CHECK(noexcept(ext::view(array)));
    }
}

TEST_CASE("array_view can access std::vector with custom allocator")
{
    class custom_int_allocator : public std::allocator<int>
    {
    };
    std::vector<int, custom_int_allocator> vector = {0, 1, 2, 3};

    SECTION("smoke test")
    {
        ext::array_view<int> view = ext::view(vector);
    }

    SECTION("won't throw")
    {
        CHECK(noexcept(ext::view(vector)));
    }
}

TEST_CASE("array_view is default constructible")
{
    ext::array_view<int> view;
    CHECK(view.data() == nullptr);
    CHECK(view.size() == 0);
}
