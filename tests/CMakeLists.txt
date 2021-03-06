# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.1)

project(array_view CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    ..
    ../third_party/Catch2
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Wpedantic \
        -Wconversion -Wsign-conversion -Wshadow")
endif()

add_executable(run
    run.cc
    test_smoketest.cc
    test_features.cc
    test_examples.cc
)

enable_testing()
add_test(unittest run)
