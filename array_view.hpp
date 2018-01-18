// Copyright snsinfu 2018.
// Distributed under the Boost Software License, Version 1.0.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef SNSINFU_EXT_ARRAY_VIEW_HPP
#define SNSINFU_EXT_ARRAY_VIEW_HPP

#include <cstddef> // size_t
#include <iterator> // reverse_iterator
#include <stdexcept> // out_of_range
#include <type_traits> // remove_cv
#include <utility> // declval

namespace snsinfu
{
namespace ext
{
    template<typename T>
    class array_view
    {
      public:
        using value_type = typename std::remove_cv<T>::type;
        using pointer = T*;
        using reference = T&;
        using size_type = std::size_t;
        using iterator = T*;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_array_view = array_view<T const>;

        array_view() = default;

        constexpr array_view(pointer data, size_type size)
            : data_{data}
            , size_{size}
        {
        }

        constexpr bool empty() const noexcept
        {
            return size() == 0;
        }

        constexpr size_type size() const noexcept
        {
            return size_;
        }

        constexpr pointer data() const noexcept
        {
            return data_;
        }

        constexpr reference front() const
        {
            return operator[](0);
        }

        constexpr reference back() const
        {
            return operator[](size() - 1);
        }

        constexpr reference operator[](size_type idx) const
        {
            return data()[idx];
        }

        constexpr reference at(size_type idx) const
        {
            return idx < size() ? operator[](idx)
                                : throw std::out_of_range(
                                      "array_view access out-of-bounds");
        }

        constexpr iterator begin() const noexcept
        {
            return data();
        }

        constexpr iterator end() const noexcept
        {
            return data() + size();
        }

        reverse_iterator rbegin() const noexcept
        {
            return reverse_iterator{end()};
        }

        reverse_iterator rend() const noexcept
        {
            return reverse_iterator{begin()};
        }

        constexpr const_array_view as_const() const noexcept
        {
            return {data(), size()};
        }

        operator const_array_view() const noexcept
        {
            return as_const();
        }

        void swap(array_view& other) noexcept
        {
            auto const this_copy = *this;
            *this = other;
            other = this_copy;
        }

        constexpr array_view subview(size_type offset, size_type count) const
        {
            return {data() + offset, count};
        }

        constexpr array_view subview(size_type offset) const
        {
            return subview(offset, size() - offset);
        }

        constexpr array_view first(size_type count) const
        {
            return subview(0, count);
        }

        constexpr array_view last(size_type count) const
        {
            return subview(size() - count, count);
        }

        constexpr array_view drop_first(size_type count) const
        {
            return subview(count);
        }

        constexpr array_view drop_last(size_type count) const
        {
            return subview(0, size() - count);
        }

      private:
        pointer data_ = nullptr;
        size_type size_ = 0;
    };

    template<typename T>
    bool operator==(array_view<T> const& lhs, array_view<T> const& rhs) noexcept
    {
        return lhs.data() == rhs.data() && lhs.size() == rhs.size();
    }

    template<typename T>
    bool operator==(array_view<T const> const& lhs, array_view<T> const& rhs) noexcept
    {
        return lhs == rhs.as_const();
    }

    template<typename T>
    bool operator==(array_view<T> const& lhs, array_view<T const> const& rhs) noexcept
    {
        return lhs.as_const() == rhs;
    }

    template<typename T>
    bool operator!=(array_view<T> const& lhs, array_view<T> const& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template<typename T>
    bool operator!=(array_view<T const> const& lhs, array_view<T> const& rhs) noexcept
    {
        return lhs != rhs.as_const();
    }

    template<typename T>
    bool operator!=(array_view<T> const& lhs, array_view<T const> const& rhs) noexcept
    {
        return lhs.as_const() != rhs;
    }

    namespace detail
    {
        template<typename T>
        struct deref;

        template<typename T>
        struct deref<T*>
        {
            using type = T;
        };

        template<typename T>
        using deref_t = typename deref<T>::type;

        template<typename Cont>
        constexpr auto data(Cont& cont) noexcept -> decltype(cont.data())
        {
            return cont.data();
        }

        template<typename T, std::size_t N>
        constexpr auto data(T (&arr)[N]) noexcept -> T*
        {
            return arr;
        }

        template<typename Cont>
        constexpr auto size(Cont& cont) noexcept -> decltype(cont.size())
        {
            return cont.size();
        }

        template<typename T, std::size_t N>
        constexpr auto size(T (&)[N]) noexcept -> std::size_t
        {
            return N;
        }
    }

    template<typename Cont,
        typename P = decltype(detail::data(std::declval<Cont&>())),
        typename S = decltype(detail::size(std::declval<Cont&>()))>
    constexpr array_view<detail::deref_t<P>> view(Cont& cont) noexcept
    {
        return {detail::data(cont), detail::size(cont)};
    }

    template<typename T>
    constexpr array_view<T> view(T* ptr, std::size_t size)
    {
        return {ptr, size};
    }

    template<typename T>
    constexpr array_view<T> view(T* begin, T* end)
    {
        return {begin, static_cast<std::size_t>(end - begin)};
    }
} // ext
} // snsinfu

#endif
