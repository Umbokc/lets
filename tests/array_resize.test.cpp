#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "vendor/doctest/doctest.h"

#include <string>

#include "lib/array.h"

using lets_lib::Array;

TEST_CASE("Array resizes without losing existing elements") {
    Array<int> array;

    array.set(0, 42);
    CHECK(array.size() == 1);
    CHECK(array[0] == 42);

    array.set(5, 7);
    CHECK(array.size() == 6);
    CHECK(array[0] == 42);
    CHECK(array[5] == 7);

    array.set(1, 99);
    CHECK(array.size() == 6);
    CHECK(array[0] == 42);
    CHECK(array[1] == 99);
    CHECK(array[5] == 7);
}

TEST_CASE("Array::at resizes to accommodate new indices") {
    Array<std::string> array;

    array.at(2) = "hello";
    CHECK(array.size() == 3);
    CHECK(array[2] == "hello");

    array.at(1) = "world";
    CHECK(array.size() == 3);
    CHECK(array[1] == "world");
    CHECK(array[2] == "hello");
}
