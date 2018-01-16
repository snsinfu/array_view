#include <array>
#include <vector>

#include <array_view.hpp>
#include <catch.hpp>

namespace ext = snsinfu::ext;

TEST_CASE("array_view can access vector elements")
{
    std::vector<int> vector = {0, 1, 2, 3};

    SECTION("smoke test")
    {
        ext::array_view<int> view = ext::view(vector);
    }

    SECTION("won't throw")
    {
        CHECK(noexcept(ext::view(vector)));
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

TEST_CASE("array_view supports accessing elements by indidces")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::view(vector);

    SECTION("read")
    {
        CHECK(view[0] == 0);
        CHECK(view[2] == 2);
    }

    SECTION("write")
    {
        view[0] = 100;
        CHECK(vector[0] == 100);
    }
}

TEST_CASE("array_view supports bounds-checked access to elements")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::view(vector);

    SECTION("read")
    {
        CHECK_NOTHROW(view.at(0));
        CHECK_THROWS_AS(view.at(view.size()), std::out_of_range);
    }

    SECTION("write")
    {
        CHECK_NOTHROW(view.at(0) = 100);
    }
}

TEST_CASE("array_view supports front and back elements access")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::view(vector);

    CHECK(view.front() == 0);
    CHECK(view.back() == 3);
}

TEST_CASE("array_view provides raw pointer")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::view(vector);
    CHECK(view.data() == vector.data());
}

TEST_CASE("array_view provides element count")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::view(vector);
    CHECK(view.size() == vector.size());
}

TEST_CASE("array_view supports range-based for loop")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::view(vector);
    for (int& elm : view) {
        elm++;
    }
}

TEST_CASE("array_view provides reverse iterators")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::view(vector);

    auto const beg = view.rbegin();
    auto const end = view.rend();

    auto it = beg;
    CHECK(*it == vector.back());

    it += view.end() - view.begin();
    CHECK(it == end);
}

TEST_CASE("array_view supports constexpr for literal strings")
{
    SECTION("constexpr view")
    {
        constexpr ext::array_view<char const> view = ext::view("abc");
    }

    SECTION("constexpr query of size and pointer")
    {
        constexpr ext::array_view<char const> view = ext::view("abc");
        constexpr std::size_t size = view.size();
        constexpr char const* ptr = view.data();
    }
}
