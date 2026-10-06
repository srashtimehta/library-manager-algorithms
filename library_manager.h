#pragma once
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

struct Book {
    int id{};
    std::string title;
    std::string author;
    int year{};

    bool operator==(const Book& other) const {
        return id == other.id && title == other.title &&
               author == other.author && year == other.year;
    }
};

inline void validate_book(const Book& book) {
    if (book.id <= 0) throw std::invalid_argument("Book ID must be positive");
    if (book.title.empty()) throw std::invalid_argument("Book title cannot be empty");
    if (book.author.empty()) throw std::invalid_argument("Book author cannot be empty");
    if (book.year < 0) throw std::invalid_argument("Book year cannot be negative");
}

inline void validate_books(const std::vector<Book>& books) {
    for (const auto& book : books) validate_book(book);
}

// Searching
inline int linear_search_by_id(const std::vector<Book>& books, int id) {
    if (id <= 0) return -1;
    for (std::size_t i = 0; i < books.size(); ++i) {
        if (books[i].id == id) return static_cast<int>(i);
    }
    return -1;
}

inline int binary_search_by_id(const std::vector<Book>& books, int id) {
    if (id <= 0) return -1;
    std::size_t left = 0, right = books.size();
    while (left < right) {
        const std::size_t mid = left + (right - left) / 2;
        if (books[mid].id == id) return static_cast<int>(mid);
        if (books[mid].id < id) left = mid + 1;
        else right = mid;
    }
    return -1;
}

// Merge sort by title, then ID for deterministic ordering.
inline void merge_sort(std::vector<Book>& books) {
    if (books.size() < 2) return;

    std::vector<Book> buffer(books.size());

    auto merge_range = [&](auto&& self, std::size_t left, std::size_t mid,
                           std::size_t right) -> void {
        std::size_t i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right) {
            const bool take_left =
                books[i].title < books[j].title ||
                (books[i].title == books[j].title && books[i].id <= books[j].id);
            buffer[k++] = take_left ? books[i++] : books[j++];
        }
        while (i <= mid) buffer[k++] = books[i++];
        while (j <= right) buffer[k++] = books[j++];
        for (std::size_t p = left; p <= right; ++p) books[p] = buffer[p];
    };

    auto sort_range = [&](auto&& self, std::size_t left, std::size_t right) -> void {
        if (left >= right) return;
        const std::size_t mid = left + (right - left) / 2;
        self(self, left, mid);
        self(self, mid + 1, right);
        merge_range(merge_range, left, mid, right);
    };

    sort_range(sort_range, 0, books.size() - 1);
}

// Selection sort by year, then title, then ID.
inline void selection_sort_by_year(std::vector<Book>& books) {
    for (std::size_t i = 0; i < books.size(); ++i) {
        std::size_t min_index = i;
        for (std::size_t j = i + 1; j < books.size(); ++j) {
            if (books[j].year < books[min_index].year ||
                (books[j].year == books[min_index].year &&
                 (books[j].title < books[min_index].title ||
                  (books[j].title == books[min_index].title &&
                   books[j].id < books[min_index].id)))) {
                min_index = j;
            }
        }
        if (min_index != i) std::swap(books[i], books[min_index]);
    }
}

inline std::size_t count_books_after_year(const std::vector<Book>& books, int year) {
    if (year < 0) throw std::invalid_argument("Year cannot be negative");
    return static_cast<std::size_t>(
        std::count_if(books.begin(), books.end(),
                      [year](const Book& b) { return b.year > year; }));
}

inline std::string report(const std::vector<Book>& books) {
    return "Total books: " + std::to_string(books.size());
}
