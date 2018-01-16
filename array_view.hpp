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

#include <cstddef>
#include <vector>

namespace snsinfu
{
namespace ext
{
    template<typename T>
    class array_view
    {
      public:
        using reference = T&;

        array_view(T* data, std::size_t size)
            : data_{data}
            , size_{size}
        {
        }

        T* data()
        {
            return data_;
        }

        reference front()
        {
            return data_[0];
        }

        reference back()
        {
            return data_[size_ - 1];
        }

        reference operator[](std::size_t idx)
        {
            return data_[idx];
        }

      private:
        T* data_;
        std::size_t size_;
    };

    template<typename T>
    array_view<T> view(std::vector<T>& vec)
    {
        return array_view<T>{vec.data(), vec.size()};
    }

} // ext
} // snsinfu

#endif
