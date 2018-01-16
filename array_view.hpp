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

#include <array>
#include <cstddef>
#include <iterator>
#include <vector>

namespace snsinfu
{
namespace ext
{
    template<typename T>
    class array_view
    {
      public:
        using pointer = T*;
        using reference = T&;
        using size_type = std::size_t;
        using iterator = T*;
        using reverse_iterator = std::reverse_iterator<iterator>;

        array_view() = default;

        constexpr array_view(pointer data, size_type size)
            : data_{data}
            , size_{size}
        {
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
            return data_[0];
        }

        constexpr reference back() const
        {
            return data_[size_ - 1];
        }

        constexpr reference operator[](size_type idx) const
        {
            return data_[idx];
        }

        constexpr reference at(size_type idx) const
        {
            return idx < size_ ? operator[](idx)
                               : throw std::out_of_range(
                                     "array_view access out-of-bounds");
        }

        constexpr iterator begin() const
        {
            return data_;
        }

        constexpr iterator end() const
        {
            return data_ + size_;
        }

        reverse_iterator rbegin() const noexcept
        {
            return reverse_iterator{end()};
        }

        reverse_iterator rend() const noexcept
        {
            return reverse_iterator{begin()};
        }

      private:
        pointer data_ = nullptr;
        size_type size_ = 0;
    };

    template<typename T, typename Allocator>
    array_view<T> view(std::vector<T, Allocator>& vec) noexcept
    {
        return array_view<T>{vec.data(), vec.size()};
    }

    template<typename T, std::size_t N>
    constexpr array_view<T> view(T (&arr)[N]) noexcept
    {
        return array_view<T>{arr, N};
    }

    template<typename T, std::size_t N>
    array_view<T> view(std::array<T, N>& arr) noexcept
    {
        return array_view<T>{arr.data(), N};
    }

} // ext
} // snsinfu

#endif
