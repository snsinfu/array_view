#include <array>
#include <string>
#include <type_traits>
#include <vector>

#include <array_view.hpp>
#include <catch.hpp>

TEST_CASE("array_view can access vector elements")
{
    std::vector<int> vector = {0, 1, 2, 3};

    SECTION("smoke test")
    {
        ext::array_view<int> view = ext::make_array_view(vector);
        static_cast<void>(view);
    }

    SECTION("won't throw")
    {
        CHECK(noexcept(ext::make_array_view(vector)));
    }
}

TEST_CASE("array_view can access built-in arrays")
{
    int array[] = {0, 1, 2, 3};

    SECTION("smoke test")
    {
        ext::array_view<int> view = ext::make_array_view(array);
        static_cast<void>(view);
    }

    SECTION("won't throw")
    {
        CHECK(noexcept(ext::make_array_view(array)));
    }
}

TEST_CASE("array_view can access std::array")
{
    std::array<int, 4> array = {{0, 1, 2, 3}};

    SECTION("smoke test")
    {
        ext::array_view<int> view = ext::make_array_view(array);
        static_cast<void>(view);
    }

    SECTION("won't throw")
    {
        CHECK(noexcept(ext::make_array_view(array)));
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
        ext::array_view<int> view = ext::make_array_view(vector);
        static_cast<void>(view);
    }

    SECTION("won't throw")
    {
        CHECK(noexcept(ext::make_array_view(vector)));
    }
}

TEST_CASE("array_view can access std::string")
{
    std::string string = "abc";

    SECTION("smoke test")
    {
        ext::array_view<char const> view = ext::make_array_view(string);
        static_cast<void>(view);
    }

    SECTION("won't throw")
    {
        CHECK(noexcept(ext::make_array_view(string)));
    }
}

TEST_CASE("array_view can access raw memory range")
{
    int array[] = {0, 1, 2, 3};
    int* const ptr = array;
    std::size_t const size = 4;

    SECTION("smoke test")
    {
        ext::array_view<int> view = ext::make_array_view(ptr, size);
        static_cast<void>(view);
    }

    SECTION("may fail")
    {
        CHECK_FALSE(noexcept(ext::make_array_view(ptr, size)));
    }
}

TEST_CASE("array_view can access raw memory range (begin-end formalism)")
{
    int array[] = {0, 1, 2, 3};
    int* const begin = array;
    int* const end = array + 4;

    SECTION("smoke test")
    {
        ext::array_view<int> view = ext::make_array_view(begin, end);
        static_cast<void>(view);
    }

    SECTION("may fail")
    {
        CHECK_FALSE(noexcept(ext::make_array_view(begin, end)));
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
    ext::array_view<int> const view = ext::make_array_view(vector);

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
    ext::array_view<int> const view = ext::make_array_view(vector);

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
    ext::array_view<int> const view = ext::make_array_view(vector);

    CHECK(view.front() == 0);
    CHECK(view.back() == 3);
}

TEST_CASE("array_view provides raw pointer")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::make_array_view(vector);

    SECTION("fact check")
    {
        CHECK(view.data() == vector.data());
    }

    SECTION("must succeed")
    {
        CHECK(noexcept(view.data()));
    }
}

TEST_CASE("array_view provides element count")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::make_array_view(vector);

    SECTION("fact check")
    {
        CHECK(view.size() == vector.size());
    }

    SECTION("must succeed")
    {
        CHECK(noexcept(view.size()));
    }
}

TEST_CASE("array_view supports range-based for loop")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::make_array_view(vector);
    for (int& elm : view) {
        elm++;
    }
}

TEST_CASE("array_view provides iterators")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::make_array_view(vector);

    SECTION("fact check")
    {
        auto const beg = view.begin();
        auto const end = view.end();

        auto it = beg;
        CHECK(*it == vector.front());

        it += view.end() - view.begin();
        CHECK(it == end);
    }

    SECTION("must succeed")
    {
        CHECK(noexcept(view.begin()));
        CHECK(noexcept(view.end()));
    }
}

TEST_CASE("array_view provides reverse iterators")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::make_array_view(vector);

    SECTION("fact check")
    {
        auto const beg = view.rbegin();
        auto const end = view.rend();

        auto it = beg;
        CHECK(*it == vector.back());

        it += view.end() - view.begin();
        CHECK(it == end);
    }

    SECTION("must succeed")
    {
        CHECK(noexcept(view.rbegin()));
        CHECK(noexcept(view.rend()));
    }
}

TEST_CASE("array_view supports constexpr for literal strings")
{
    SECTION("constexpr view")
    {
        constexpr ext::array_view<char const> view = ext::make_array_view("abc");
        static_cast<void>(view);
    }

    SECTION("constexpr view (ptr/size memory)")
    {
        constexpr char const* ptr = "abc";
        constexpr ext::array_view<char const> view = ext::make_array_view(ptr, 3);
        static_cast<void>(view);
    }

    SECTION("constexpr view (begin/end memory)")
    {
        constexpr char const* ptr = "abc";
        constexpr ext::array_view<char const> view = ext::make_array_view(ptr, ptr + 3);
        static_cast<void>(view);
    }

    SECTION("constexpr query of size and pointer")
    {
        constexpr ext::array_view<char const> view = ext::make_array_view("abc");
        constexpr std::size_t size = view.size();
        constexpr char const* ptr = view.data();
        CHECK(size == 4); // Note the terminating nul character
    }

    SECTION("constexpr access of elements")
    {
        constexpr ext::array_view<char const> view = ext::make_array_view("abc");
        constexpr char const& a = view.front();
        constexpr char const& b = view[1];
        constexpr char const& z = view.back();
        CHECK(a == 'a');
        CHECK(b == 'b');
        CHECK(z == '\0');
    }

    SECTION("constexpr iterators")
    {
        constexpr ext::array_view<char const> view = ext::make_array_view("abc");
        constexpr auto beg = view.begin();
        constexpr auto end = view.end();
        CHECK(beg != end);
    }

    SECTION("constexpr transformation to const view")
    {
        constexpr ext::array_view<char const> view = ext::make_array_view("abc");
        constexpr ext::array_view<char const> cview = view.as_const();
        CHECK(cview == view);
    }

    SECTION("constexpr slicing")
    {
        constexpr ext::array_view<char const> view = ext::make_array_view("abc");
        constexpr ext::array_view<char const> subview = view.subview(1, 2);
        constexpr ext::array_view<char const> first = view.first(2);
        constexpr ext::array_view<char const> last = view.last(2);
        constexpr ext::array_view<char const> tail = view.drop_first(2);
        constexpr ext::array_view<char const> init = view.drop_last(2);
        CHECK(subview.size() == 2);
        CHECK(first.size() == 2);
        CHECK(last.size() == 2);
        CHECK(tail.size() == view.size() - 2);
        CHECK(init.size() == view.size() - 2);
    }

    SECTION("constexpr emptiness check")
    {
        constexpr ext::array_view<char const> view = ext::make_array_view("abc");
        constexpr bool empty = view.empty();
        CHECK_FALSE(empty);
    }
}

TEST_CASE("array_view can be transformed to const view")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::make_array_view(vector);

    SECTION("fact check")
    {
        ext::array_view<int const> const cview = view.as_const();
        CHECK(cview == view);
    }

    SECTION("must succeed")
    {
        CHECK(noexcept(view.as_const()));
    }
}

TEST_CASE("array_view can be implicitly converted to const view")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::make_array_view(vector);

    SECTION("fact check")
    {
        ext::array_view<int const> const const_view = view;
        CHECK(const_view.data() == view.data());
        CHECK(const_view.size() == view.size());
    }

    SECTION("must succeed")
    {
        CHECK(noexcept(static_cast<ext::array_view<int const>>(view)));
    }
}

TEST_CASE("two array_views can be swapped")
{
    std::vector<int> vector1 = {0, 1, 2, 3};
    std::vector<int> vector2 = {4, 5};

    ext::array_view<int> view1 = ext::make_array_view(vector1);
    ext::array_view<int> view2 = ext::make_array_view(vector2);

    view1.swap(view2);

    CHECK(view1.data() == vector2.data());
    CHECK(view1.size() == vector2.size());

    CHECK(view2.data() == vector1.data());
    CHECK(view2.size() == vector1.size());
}

TEST_CASE("two array_views can be compared for shallow equality")
{
    std::vector<int> vector1 = {0, 1, 2, 3};
    std::vector<int> vector2 = {0, 1, 2, 3};

    ext::array_view<int> const view1 = ext::make_array_view(vector1);
    ext::array_view<int> const view2 = ext::make_array_view(vector2);

    SECTION("fact check")
    {
        CHECK(view1 == view1);
        CHECK(view1 != view2);
    }

    SECTION("must succeed")
    {
        CHECK(noexcept(view1 == view1));
        CHECK(noexcept(view1 != view2));
    }
}

TEST_CASE("const and mutable array_views can be compared")
{
    std::vector<int> vector = {0, 1, 2, 3};

    ext::array_view<int> const mutable_view = ext::make_array_view(vector);
    ext::array_view<int const> const const_view = ext::make_array_view(vector);

    SECTION("fact check")
    {
        CHECK(mutable_view == const_view);
        CHECK(const_view == mutable_view);
        CHECK_FALSE(mutable_view != const_view);
        CHECK_FALSE(const_view != mutable_view);
    }

    SECTION("must succeed")
    {
        CHECK(noexcept(mutable_view == const_view));
        CHECK(noexcept(const_view == mutable_view));
        CHECK(noexcept(mutable_view != const_view));
        CHECK(noexcept(const_view != mutable_view));
    }
}

TEST_CASE("array_view can be sliced")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::make_array_view(vector);

    SECTION("closed slice")
    {
        ext::array_view<int> const subview = view.subview(1, 2);
        CHECK(subview.data() == view.data() + 1);
        CHECK(subview.size() == 2);
    }
}

TEST_CASE("array_view can be sliced into prefix")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::make_array_view(vector);
    ext::array_view<int> const first = view.first(2);
    CHECK(first == view.subview(0, 2));
}

TEST_CASE("array_view can be sliced into suffix")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::make_array_view(vector);
    ext::array_view<int> const first = view.last(2);
    CHECK(first == view.subview(view.size() - 2, 2));
}

TEST_CASE("array_view can be sliced after prefix")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::make_array_view(vector);
    ext::array_view<int> const tail = view.drop_first(2);
    CHECK(tail == view.subview(2, view.size() - 2));
}

TEST_CASE("array_view can be sliced before suffix")
{
    std::vector<int> vector = {0, 1, 2, 3};
    ext::array_view<int> const view = ext::make_array_view(vector);
    ext::array_view<int> const init = view.drop_last(2);
    CHECK(init == view.subview(0, view.size() - 2));
}

TEST_CASE("array_view provides emptiness check")
{
    std::vector<int> vector = {0, 1, 2, 3};

    SECTION("fact check")
    {
        ext::array_view<int> const view = ext::make_array_view(vector);
        ext::array_view<int> const empty_view;
        CHECK_FALSE(view.empty());
        CHECK(empty_view.empty());
    }

    SECTION("must succeed")
    {
        ext::array_view<int> view = ext::make_array_view(vector);
        CHECK(noexcept(view.empty()));
    }
}

TEST_CASE("array_view exposes standard typedefs")
{
    using A = ext::array_view<int const>;

    CHECK(std::is_same<A::value_type, int>::value);
    CHECK(std::is_same<A::pointer, int const*>::value);
    CHECK(std::is_same<A::reference, int const&>::value);
    CHECK(std::is_same<A::size_type, std::size_t>::value);
    CHECK(sizeof(A::iterator) > 0);
    CHECK(sizeof(A::reverse_iterator) > 0);
}
