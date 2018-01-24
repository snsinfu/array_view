array\_view
===========

![C++11][cxx-badge]
[![Boost License][license-badge]][license-url]
[![Build Status][travis-badge]][travis-url]

Single header-only library of non-owning array view for C++11 and later.

- [Introduction](#introduction)
- [Usage](#usage)
- [License](#license)

[cxx-badge]: https://img.shields.io/badge/C%2B%2B-11-orange.svg
[license-badge]: http://img.shields.io/badge/license-Boost-blue.svg
[license-url]: https://github.com/snsinfu/array_view/blob/master/LICENSE.txt
[travis-badge]: https://travis-ci.org/snsinfu/array_view.svg?branch=master
[travis-url]: https://travis-ci.org/snsinfu/array_view

## Introduction

`array_view` is a random-access range abstraction of a pointer-length pair seen
in C APIs, like this:

    void compute_something(double* ptr, size_t len);

`array_view` is similar to [GSL][gsl]'s `span`. Notable differences are:

- `array_view` disallows implicit conversion from contiguous containers
- `array_view` uses `size_t` for size and index

[gsl]: https://github.com/Microsoft/GSL

## Usage

### Installation

Just copy [array\_view.hpp][header] to your include directory.

[header]: https://raw.githubusercontent.com/snsinfu/array_view/master/array_view.hpp

### Example

Use `ext::view()` to create a view from a container like `std::vector`. The
created view would then work as a random-access range and also support subview
operations such as `subview(i, n)`, `first(n)` and `drop_last(n)`.

    #include <iostream>
    #include <vector>
    #include <array_view.hpp>
    
    int main()
    {
        std::vector<int> vector = {1, 2, 3, 4};
        ext::array_view<int> view = ext::view(vector);

        for (int num : view.drop_last(1)) {
            std::cout << num << ' ';
        }
        std::cout << '\n';
        // Prints: 1 2 3
    }

### Doxygen reference

- [Main page](https://snsinfu.github.io/array_view/)
- [ext](https://snsinfu.github.io/array_view/namespaceext.html)
- [ext::array_view](https://snsinfu.github.io/array_view/classext_1_1array__view.html)

## License

Boost Software License, Version 1.0.

License text is in the header file so you do not need to bundle LICENSE.txt
with your project. Just copy the header file into your include directory.
