# Complexity Notes

| Algorithm | Purpose | Time | Extra Space |
|---|---|---:|---:|
| Linear Search | Find ID in unsorted records | O(n) | O(1) |
| Binary Search | Find ID in ID-sorted records | O(log n) | O(1) |
| Merge Sort | Sort by title | O(n log n) | O(n) |
| Selection Sort | Sort by year | O(n²) | O(1) |
| Count/report | Reporting | O(n) | O(1) |

## Correctness reasoning

- Linear search checks every possible record until the requested ID is found, so it cannot skip a matching record.
- Binary search maintains the invariant that if the ID exists, it remains inside the current search interval. Each step removes about half the remaining interval.
- Merge sort recursively sorts both halves and merges two sorted ranges while preserving the ordering rule.
- Selection sort places the smallest remaining record at each position; after iteration `i`, positions before `i` are in final sorted order.
- Tests include normal, boundary, duplicate-value, missing-value, empty-input, single-record, and invalid-input cases.
