array\_view
===========

Single header-only library of non-owning array view for C++11 and later.

- [Usage](#usage)
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

## License

Boost Software License, Version 1.0.

License text is in the header file so you do not need to bundle LICENSE.txt
with your project. Just copy the header file into your include directory.
