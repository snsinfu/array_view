array\_view for C++11
=====================

![C++11][cxx-badge]
[![Boost License][license-badge]][license-url]
[![Build Status][travis-badge]][travis-url]

Single header-only library of `array_view`, a lightweight range view class for
accessing contiguous sequence of objects.

- [Why](#why)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)

[cxx-badge]: https://img.shields.io/badge/C%2B%2B-11-orange.svg
[license-badge]: http://img.shields.io/badge/license-Boost-blue.svg
[license-url]: https://github.com/snsinfu/array_view/blob/master/LICENSE.txt
[travis-badge]: https://travis-ci.org/snsinfu/array_view.svg?branch=master
[travis-url]: https://travis-ci.org/snsinfu/array_view

## Why?

`array_view` is a lightweight random-access range abstraction of an array slice:

```
double array[5] = {1, 2, 3, 4, 5};
ext::array_view<double> view{array, 3}; // view of {1, 2, 3} part
```

The concept is the same as that of [GSL][gsl]'s `span`, but `array_view` uses
`size_t` for index type for better compatibility with the standard library. I'm
okay with GSL's idea of using signed index itself, but the incompatibility with
the standard library really annoys me.

[gsl]: https://github.com/Microsoft/GSL

## Installation

This library has no dependency. Just copy [array\_view.hpp][header] to your
include directory and you are done!

[header]: https://raw.githubusercontent.com/snsinfu/array_view/master/array_view.hpp

## Usage

The library provides two things:

- `ext::array_view`
- `ext::make_array_view()`

Use `ext::make_array_view()` to create a view from a container object or an
array. The created view then works as a random-access range and also supports
slicing operations such as `subview(i, n)`, `first(n)` and `drop_last(n)`.

```c++
#include <iostream>
#include <vector>
#include <array_view.hpp>

int main()
{
    std::vector<int> vector = {1, 2, 3, 4};
    ext::array_view<int> view = ext::make_array_view(vector);

    for (int& num : view.drop_last(1)) {
        std::cout << num << ' ';
    }
    std::cout << '\n';
    // Prints: 1 2 3
}
```

## License

Boost Software License, Version 1.0.

License text is in the header file so you do not need to bundle LICENSE.txt
with your project. Just copy the header file into your include directory.
