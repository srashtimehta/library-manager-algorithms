#include <iostream>
#include <vector>
#include "library_manager.h"

int main() {
    std::vector<Book> books{
        {103, "Clean Code", "Robert C. Martin", 2008},
        {101, "The C++ Programming Language", "Bjarne Stroustrup", 2013},
        {105, "Algorithms", "Robert Sedgewick", 2011},
        {102, "Effective Modern C++", "Scott Meyers", 2014}
    };

    validate_books(books);

    std::cout << report(books) << "\n";

    const int target = 102;
    std::cout << "Linear search for ID " << target
              << ": index " << linear_search_by_id(books, target) << "\n";

    std::sort(books.begin(), books.end(),
              [](const Book& a, const Book& b) { return a.id < b.id; });

    std::cout << "Binary search for ID " << target
              << ": index " << binary_search_by_id(books, target) << "\n";

    merge_sort(books);
    std::cout << "Books sorted by title:\n";
    for (const auto& b : books)
        std::cout << b.id << " | " << b.title << " | " << b.year << "\n";

    selection_sort_by_year(books);
    std::cout << "Books sorted by year:\n";
    for (const auto& b : books)
        std::cout << b.id << " | " << b.title << " | " << b.year << "\n";

    std::cout << "Books after 2010: "
              << count_books_after_year(books, 2010) << "\n";
    return 0;
}
