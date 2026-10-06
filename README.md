# Library Manager — Algorithms & Automated Testing

A C++17 library-manager module demonstrating searching, sorting, reporting, unit testing, and time/space complexity.

## Implemented algorithms

### Searching
1. **Linear Search** — scans records from left to right.
   - Time: O(n)
   - Extra space: O(1)

2. **Binary Search** — searches a sorted vector by repeatedly halving the range.
   - Time: O(log n)
   - Extra space: O(1)

### Sorting
1. **Merge Sort** — stable divide-and-conquer sort.
   - Time: O(n log n) in best/average/worst cases
   - Extra space: O(n)

2. **Selection Sort** — repeatedly places the minimum element.
   - Time: O(n²)
   - Extra space: O(1)

## Automated tests

`tests/test_library_manager.cpp` covers:
- normal searches and sorting
- empty collection boundary case
- single-record boundary case
- first/last element boundaries
- missing ID / invalid search cases
- duplicate titles
- already-sorted and reverse-sorted data
- invalid/empty input validation

## Build and run

### Linux / macOS
```bash
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp -o library_manager
./library_manager

g++ -std=c++17 -Wall -Wextra -pedantic tests/test_library_manager.cpp -o library_tests
./library_tests
```

### Windows (MinGW)
```bat
g++ -std=c++17 -Wall -Wextra -pedantic src\main.cpp -o library_manager.exe
library_manager.exe

g++ -std=c++17 -Wall -Wextra -pedantic tests\test_library_manager.cpp -o library_tests.exe
library_tests.exe
```

## Expected test result

```text
All automated tests passed.
Passed: 25
Failed: 0
```

## Submission

Submit the public GitHub repository/project page containing this folder. The repository includes source code, tests, a complexity note, and test evidence.
