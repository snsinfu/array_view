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

#ifndef EXT_ARRAY_VIEW_HPP
#define EXT_ARRAY_VIEW_HPP

#include <cstddef> // size_t
#include <iterator> // reverse_iterator
#include <stdexcept> // out_of_range
#include <type_traits> // remove_cv
#include <utility> // declval

/// Additional vocabulary to the standard.
namespace ext
{
    /// Lightweight view of an array.
    template<typename T>
    class array_view
    {
      public:
        /// The non-qualified type of the elements.
        using value_type = typename std::remove_cv<T>::type;

        /// The type of a pointer to an element.
        using pointer = T*;

        /// The type of a reference to an element.
        using reference = T&;

        /// The type of size and index values.
        using size_type = std::size_t;

        /// The type of iterators. Guaranteed to be a random access iterator.
        /// Currently implemented as an alias of T* but this may change in the
        /// future.
        using iterator = T*;

        /// The type of reverse iterators. Guaranteed to be a random access
        /// iterator.
        using reverse_iterator = std::reverse_iterator<iterator>;

        /// The type of read-only array_view with the same value_type. This is
        /// the same as array_view<T> if T is already const qualified.
        using const_array_view = array_view<T const>;

        /// The default constructor creates an empty view.
        constexpr array_view() noexcept = default;

        /// This constructor creates a view of region [data, data + size).
        constexpr array_view(pointer data, size_type size)
            : data_{data}
            , size_{size}
        {
        }

        /// Tests if the view is empty.
        constexpr bool empty() const noexcept
        {
            return size() == 0;
        }

        /// Returns the number of elements.
        constexpr size_type size() const noexcept
        {
            return size_;
        }

        /// Returns a pointer to the first element. The pointer may or may not
        /// be null if the view is empty.
        constexpr pointer data() const noexcept
        {
            return data_;
        }

        /// Returns a reference to the first element. The behavior is
        /// undefined if the view is empty.
        constexpr reference front() const
        {
            return operator[](0);
        }

        /// Returns a reference to the last element. The behavior is undefined
        /// if the view is empty.
        constexpr reference back() const
        {
            return operator[](size() - 1);
        }

        /// Returns a reference to the idx-th element. The behavior is
        /// undefined if the index is out of bounds.
        constexpr reference operator[](size_type idx) const
        {
            return data()[idx];
        }

        /// Returns a reference to the idx-th element.
        /// .
        /// @exception std::out_of_range if the index is out of bounds.
        constexpr reference at(size_type idx) const
        {
            return idx < size() ? operator[](idx)
                                : throw std::out_of_range(
                                      "array_view access out-of-bounds");
        }

        /// Returns an iterator to the beginning.
        constexpr iterator begin() const noexcept
        {
            return data();
        }

        /// Returns an iterator to the end.
        constexpr iterator end() const noexcept
        {
            return data() + size();
        }

        /// Returns a reverse iterator to the reverse beginning.
        reverse_iterator rbegin() const noexcept
        {
            return reverse_iterator{end()};
        }

        /// Returns a reverse iterator to the reverse end.
        reverse_iterator rend() const noexcept
        {
            return reverse_iterator{begin()};
        }

        /// Returns a read-only view of the same array.
        constexpr const_array_view as_const() const noexcept
        {
            return {data(), size()};
        }

        /// A view is always implicitly convertible to a read-only view.
        operator const_array_view() const noexcept
        {
            return as_const();
        }

        /// Swaps the viewed array.
        void swap(array_view& other) noexcept
        {
            auto const this_copy = *this;
            *this = other;
            other = this_copy;
        }

        /// Returns a view of the subarray with given region.
        constexpr array_view subview(size_type offset, size_type count) const
        {
            return {data() + offset, count};
        }

        /// Returns a view of a subarray starts at offset.
        constexpr array_view subview(size_type offset) const
        {
            return subview(offset, size() - offset);
        }

        /// Returns a view of the first count elements.
        constexpr array_view first(size_type count) const
        {
            return subview(0, count);
        }

        /// Returns a view of the last count elements.
        constexpr array_view last(size_type count) const
        {
            return subview(size() - count, count);
        }

        /// Returns a view of the array except the first count elements.
        constexpr array_view drop_first(size_type count) const
        {
            return subview(count);
        }

        /// Returns a view of the array except the last count elements.
        constexpr array_view drop_last(size_type count) const
        {
            return subview(0, size() - count);
        }

      private:
        pointer data_ = nullptr;
        size_type size_ = 0;
    };

    /// Compares views for shallow equality.
    ///
    /// Two views are equal if and only if the viewed memory region is exactly
    /// the same. Empty views are the same if the beginning pointers match;
    /// arbitrary empty views are not necessarily the same. Still,
    /// default-constructed views are guaranteed to be the same.
    ///
    /// This is a *shallow* comprison. Use `std::lexicographic_compare`
    /// algorithm for deep element-wise comparisons.
    ///
    /// @return  true if lhs and rhs are the same view, false otherwise.
    //
    /// @par Complexity
    /// O(1)
    template<typename T>
    bool operator==(
        array_view<T> const& lhs, array_view<T> const& rhs) noexcept
    {
        return lhs.data() == rhs.data() && lhs.size() == rhs.size();
    }

    /// Supports const v.s. non-const comparisons.
    template<typename T>
    bool operator==(
        array_view<T const> const& lhs, array_view<T> const& rhs) noexcept
    {
        return lhs == rhs.as_const();
    }

    /// Supports const v.s. non-const comparisons.
    template<typename T>
    bool operator==(
        array_view<T> const& lhs, array_view<T const> const& rhs) noexcept
    {
        return lhs.as_const() == rhs;
    }

    /// Compares views for shallow inequality.
    ///
    /// This is equivalent to `!(lhs == rhs)`.
    template<typename T>
    bool operator!=(
        array_view<T> const& lhs, array_view<T> const& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    /// Supports const v.s. non-const comparisons.
    template<typename T>
    bool operator!=(
        array_view<T const> const& lhs, array_view<T> const& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    /// Supports const v.s. non-const comparisons.
    template<typename T>
    bool operator!=(
        array_view<T> const& lhs, array_view<T const> const& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    namespace detail
    {
        // Removes top-level pointer. SFINAE friendly.
        template<typename T>
        struct deref;

        template<typename T>
        struct deref<T*>
        {
            using type = T;
        };

        template<typename T>
        using deref_t = typename deref<T>::type;

        // Returns a pointer to the first element of a contiguous container.
        //
        // XXX: Here almost no concept checks are done, so this may be broken
        //      for non-STL types and can cause nasty run-time memory error!
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

        // Returns the number of elements in a container.
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

    /// Creates an array_view of the elements of a contiguous container.
    ///
    /// For an array the pointer to the first element and the compile-time
    /// length of the array are used to create a view. Otherwise `cont.data()`
    /// is assumed to be the beginning of the memory region owned by the
    /// container and `cont.size()` is assumed to be the number of elements in
    /// that memory region. The behavior is undefined if these assumptions are
    /// not met.
    ///
    /// @param cont     A contiguous container or an array.
    ///
    /// @return         A view of all the elements in the given container.
    ///
    /// @par Rationale
    /// Container-to-array_view conversion is unsafe. An array_view can easily
    /// outlive the viewed container and cause a dangling pointer bug. Such a
    /// conversion should not be overlooked in the source code. Thus, this
    /// library disallows implicit conversion and forces explicit conversion
    /// via this function.
    template<typename Cont,
        typename P = decltype(detail::data(std::declval<Cont&>())),
        typename S = decltype(detail::size(std::declval<Cont&>()))>
    constexpr array_view<detail::deref_t<P>> view(Cont& cont) noexcept
    {
        return {detail::data(cont), detail::size(cont)};
    }

    /// Creates an array_view of the region [ptr, ptr + size).
    ///
    /// The behavior is undefined if the memory region is not valid.
    template<typename T>
    constexpr array_view<T> view(T* ptr, std::size_t size)
    {
        return {ptr, size};
    }

    /// Creates an array_view of the region [begin, end).
    ///
    /// The behavior is undefined if the memory region is not valid.
    template<typename T>
    constexpr array_view<T> view(T* begin, T* end)
    {
        return {begin, static_cast<std::size_t>(end - begin)};
    }
} // ext

#endif
