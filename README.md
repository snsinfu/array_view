array\_view.hpp
===============

Single header-only library of non-owning array view for C++11 and later.

- [Usage](#usage)
- [API](#api)
- [License](#license)

## Usage

Just copy [array\_view.hpp][header] to your include directory.

[header]: https://github.com/snsinfu/array_view.hpp/raw/master/array_view.hpp

### Example

```c++
#include <iostream>
#include <vector>
#include <array_view.hpp>

void print_init(ext::array_view<int const> view)
{
    for (int const& num : view.drop_last(1)) {
        std::cout << num << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::vector<int> vector = {1, 2, 3, 4};
    print_init(ext::view(vector)); // Prints: 1 2 3

    int array[] = {5, 6, 7, 8};
    print_init(ext::view(array)); // Prints: 5 6 7
}
```

## API

All entities are inside namespace `ext`.

### class `array_view<T>`

```c++
using value_type = typename std::remove_cv<T>::type;
using pointer = T*;
using reference = T&;
using size_type = std::size_t;
using iterator = T*;
using reverse_iterator = std::reverse_iterator<iterator>;
using const_array_view = array_view<T const>;

array_view() = default;
array_view(pointer data, size_type size);

bool empty() const noexcept;
size_type size() const noexcept;

pointer data() const noexcept;
reference front() const;
reference back() const;
reference operator[](size_type idx) const;
reference at(size_type idx) const;

iterator begin() const noexcept;
iterator end() const noexcept;
reverse_iterator rbegin() const noexcept;
reverse_iterator rend() const noexcept;

const_array_view as_const() const noexcept;
operator const_array_view() const noexcept;

void swap(array_view& other) noexcept;

array_view subview(size_type offset, size_type count) const;
array_view subview(size_type offset) const;
array_view first(size_type count) const;
array_view last(size_type count) const;
array_view drop_first(size_type count) const;
array_view drop_last(size_type count) const;
```

### Operators

```c++
bool operator==(array_view<T> const& lhs, array_view<T> const& rhs) noexcept;
bool operator!=(array_view<T> const& lhs, array_view<T> const& rhs) noexcept;

bool operator==(array_view<T const> const& lhs, array_view<T> const& rhs) noexcept;
bool operator!=(array_view<T const> const& lhs, array_view<T> const& rhs) noexcept;

bool operator==(array_view<T> const& lhs, array_view<T const> const& rhs) noexcept;
bool operator!=(array_view<T> const& lhs, array_view<T const> const& rhs) noexcept;
```

### Factory functions

```c++
array_view<deduced> view(Cont& cont) noexcept;
array_view<T> view(T* ptr, std::size_t size);
array_view<T> view(T* begin, T* end);
```

## License

Boost Software License, Version 1.0.

License text is in the header file so you do not need to bundle LICENSE.txt
with your project. Just copy the header file into your include directory.
