#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "../src/library_manager.h"

static int passed = 0;
static int failed = 0;

#define CHECK(condition) do { \
    if (condition) { ++passed; } \
    else { ++failed; std::cerr << "FAIL: " << #condition << "\n"; } \
} while (0)

static std::vector<Book> sample() {
    return {
        {4, "Dune", "Frank Herbert", 1965},
        {1, "Algorithms", "Sedgewick", 2011},
        {3, "C++ Primer", "Lippman", 2012},
        {2, "Algorithms", "Different Author", 2005}
    };
}

static void test_linear_search() {
    auto b = sample();
    CHECK(linear_search_by_id(b, 4) == 0);      // first boundary
    CHECK(linear_search_by_id(b, 2) == 3);      // last boundary
    CHECK(linear_search_by_id(b, 99) == -1);    // missing
    CHECK(linear_search_by_id(b, 0) == -1);     // invalid
}

static void test_binary_search() {
    auto b = sample();
    std::sort(b.begin(), b.end(),
              [](const Book& a, const Book& c) { return a.id < c.id; });
    CHECK(binary_search_by_id(b, 1) == 0);
    CHECK(binary_search_by_id(b, 4) == 3);
    CHECK(binary_search_by_id(b, 3) == 2);
    CHECK(binary_search_by_id(b, 99) == -1);
    CHECK(binary_search_by_id(b, -1) == -1);
}

static void test_merge_sort() {
    auto b = sample();
    merge_sort(b);
    CHECK(b[0].title == "Algorithms" && b[0].id == 1);
    CHECK(b[1].title == "Algorithms" && b[1].id == 2);
    CHECK(b[2].title == "C++ Primer");
    CHECK(b[3].title == "Dune");

    std::vector<Book> empty;
    merge_sort(empty);                          // empty boundary
    CHECK(empty.empty());

    std::vector<Book> one{{7, "Solo", "Author", 2020}};
    merge_sort(one);                            // single boundary
    CHECK(one.size() == 1 && one[0].id == 7);
}

static void test_selection_sort() {
    auto b = sample();
    selection_sort_by_year(b);
    CHECK(b[0].year == 1965);
    CHECK(b[1].year == 2005);
    CHECK(b[2].year == 2011);
    CHECK(b[3].year == 2012);
}

static void test_reporting_and_validation() {
    auto b = sample();
    CHECK(report(b) == "Total books: 4");
    CHECK(count_books_after_year(b, 2010) == 2);
    CHECK(count_books_after_year(b, 2025) == 0);

    bool threw = false;
    try { count_books_after_year(b, -1); }
    catch (const std::invalid_argument&) { threw = true; }
    CHECK(threw);

    threw = false;
    try { validate_book({0, "Bad", "Author", 2020}); }
    catch (const std::invalid_argument&) { threw = true; }
    CHECK(threw);

    threw = false;
    try { validate_book({10, "", "Author", 2020}); }
    catch (const std::invalid_argument&) { threw = true; }
    CHECK(threw);
}

int main() {
    test_linear_search();
    test_binary_search();
    test_merge_sort();
    test_selection_sort();
    test_reporting_and_validation();

    std::cout << "All automated tests completed.\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
