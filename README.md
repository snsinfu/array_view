array\_view
===========

Single header-only library of non-owning array view for C++11 and later.

- [Introduction](#introduction)
- [Usage](#usage)
- [License](#license)

## Introduction

`array_view` is a random-access range abstraction of a pointer-length pair seen
in C APIs, like this:

    void compute_something(double* ptr, size_t len);

`array_view` is similar to [GSL][gsl]'s `span`. Notable differences are:

- `array_view` disallows implicit conversion from contiguous containers
- `array_view` uses `size_t` for size and index

[gsl]: https://github.com/Microsoft/GSL

## Usage

Just copy [array\_view.hpp][header] to your include directory.

[header]: https://github.com/snsinfu/array_view.hpp/raw/master/array_view.hpp

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

## License

Boost Software License, Version 1.0.

License text is in the header file so you do not need to bundle LICENSE.txt
with your project. Just copy the header file into your include directory.
