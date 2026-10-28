# 📜 List — Custom STL-Compatible Doubly Linked List in C++20

![C++20](https://img.shields.io/badge/Language-C%2B%2B20-blue.svg)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple.svg)
![Type](https://img.shields.io/badge/Type-Doubly%20Linked%20List%20%7C%20STL--like-green.svg)
![Concepts](https://img.shields.io/badge/C%2B%2B20-std%3A%3Abidirectional__iterator-blueviolet.svg)
![Coursework](https://img.shields.io/badge/University-Data%20Structures%20Course-orange.svg)
![Tests](https://img.shields.io/badge/Tests-TDD%20(22%20Suites)-brightgreen.svg)

A university coursework project for the **Data Structures and Algorithms** course. This repository provides a complete, robust implementation of a doubly linked list (`List<T>`), closely mimicking the interface, ownership semantics, and behavior of `std::list` from the C++ Standard Template Library (STL).

The project is built on **C++20**, leveraging compile-time concepts for strict iterator validation.

---

## 📌 Architectural Highlights

### 1. Sentinel Node Architecture (Dummy Head & Tail)
The list utilizes two dedicated sentinel nodes (`_head` and `_tail`), which hold no payload data:
```
[_head (Sentinel)] <---> [Node 1] <---> [Node 2] <---> ... <---> [_tail (Sentinel)]
```
- Eliminates special branch conditions for empty lists, boundary insertions, and edge erasures.
- The `_tail` sentinel provides an invariant representation for `end()`, while `_head` serves as the boundary for `rend()`.

### 2. Comprehensive Bidirectional Iterators (C++20 Concepts)
Includes 4 interrelated iterator classes:
- `iterator` — standard mutable bidirectional iterator.
- `const_iterator` — read-only bidirectional iterator.
- `reverse_iterator` — backwards iterator traversing tail-to-head.
- `const_reverse_iterator` — read-only backwards iterator.

Iterator conformance is enforced at compile time via C++20 concepts:
```cpp
static_assert(std::bidirectional_iterator<iterator>);
```
Exposes the full STL iterator suite: `begin()`, `end()`, `rbegin()`, `rend()`, `cbegin()`, `cend()`, `crbegin()`, `crend()`.

### 3. Integrated List Operations
Beyond basic push/pop operations, the container implements native node algorithms:
- `merge(List& other)` — merges two sorted lists into one with linear complexity without reallocating data.
- `sort()` — in-place stable list sorting.

### 4. Range-Based Constructor
Accepts arbitrary input iterator ranges adhering to the `std::input_iterator` concept:
```cpp
template <std::input_iterator iter>
List(iter begin, iter end);
```

---

## 📁 Repository Structure

```text
List/
├── List.sln                         # Visual Studio 2022 Solution
├── .gitignore                       # Git ignores for build artifacts
│
└── List/
    ├── List.h                       # Template declaration & implementation of List<T>
    ├── main.cpp                     # Test execution entry point
    ├── List.vcxproj                 # MSVC Project file
    │
    └── Tests/                       # 22 Modular TDD Test Suites
        ├── 1BasicConstructorsTest.h
        ├── 2PushFrontBackTest.h
        ├── 3PopFrontBackTest.h
        ├── 4DestructorCallTest.h
        ├── 5CopyConstructorTest.h
        ├── 6AssignmentOperatorTest.h
        ├── 7DestructorWithAssignmentTest.h
        ├── 8ConstFrontBackTest.h
        ├── 9ClearTest.h
        ├── 10BasicIteratorTest.h
        ├── 11ReverseIteratorTest.h
        ├── 12ConstIteratorTest.h
        ├── 13ConstReverseIteratorTest.h
        ├── 14MemberAccessIteratorTest.h
        ├── 15InitializerListConstructorTest.h
        ├── 16IteratorConstructibleTest.h
        ├── 17ClassWithNoDefaultConstructorTest.h
        ├── 18InsertTest.h
        ├── 19EraseTest.h
        ├── 20MergeTest.h
        ├── 21SortTest.h
        ├── 22StlCompatibilityTest.h
        └── Fixtures/                # CustomAsserts test helpers
```

---

## 📋 Method Reference & Complexity

| Method | Signature | Time Complexity | Description |
| :--- | :--- | :--- | :--- |
| `push_front` | `void push_front(const T& val)` | `O(1)` | Inserts element at the beginning |
| `push_back` | `void push_back(const T& val)` | `O(1)` | Inserts element at the end |
| `pop_front` | `void pop_front()` | `O(1)` | Removes the first element |
| `pop_back` | `void pop_back()` | `O(1)` | Removes the last element |
| `insert` | `void insert(const iterator& it, const T& val)` | `O(1)` | Inserts element before the specified iterator |
| `erase` | `void erase(const iterator& it)` | `O(1)` | Removes element at the specified iterator |
| `front` / `back` | `T& front()`, `T& back()` | `O(1)` | Direct access to head and tail elements |
| `size` | `size_t size()` | `O(1)` | Returns active element count |
| `empty` | `bool empty()` | `O(1)` | Checks if the list contains zero elements |
| `clear` | `void clear()` | `O(N)` | Destroys all non-sentinel nodes |
| `merge` | `void merge(List& other)` | `O(N + M)` | Merges another sorted list into `this` |
| `sort` | `void sort()` | `O(N²)` | In-place element sort |
| `begin` / `end` | `iterator begin()`, `iterator end()` | `O(1)` | Forward bidirectional iterators |
| `rbegin` / `rend` | `reverse_iterator rbegin()`, ... | `O(1)` | Reverse bidirectional iterators |

---

## 🧪 Unit Testing (TDD)

The list passes **22 unit test suites**:
1. Default, sized, and filled constructors.
2. Bidirectional insertions (`push_front`, `push_back`).
3. Bidirectional removals (`pop_front`, `pop_back`).
4. **Destructor tracker**: guarantees zero memory leaks across all node allocations.
5. Deep copy construction.
6. Copy assignment operator with self-assignment safety.
7. Proper destruction during reassignment.
8. Const versions of `front()` and `back()`.
9. Total clearing via `clear()`.
10. Bidirectional iterator traversal: `++`, `--`, `*`.
11. Reverse iterator validation (`rbegin`, `rend`).
12. Const forward iterator access control.
13. Const reverse iterator validation.
14. Field selection via `it->member`.
15. `std::initializer_list<T>` construction.
16. Range construction using `std::input_iterator`.
17. Support for classes lacking default constructors.
18. Arbitrary iterator-based `insert()`.
19. Iterator-based `erase()`.
20. `merge()` sorted list concatenation.
21. `sort()` ordering verification.
22. **Standard algorithm interoperability** (`std::find`, `std::count`, `std::reverse`, `std::distance`).

---

## ⚙️ Build and Execution

1. Open `List.sln` in **Visual Studio 2022**.
2. Select configuration **Debug / x64** or **Release / x64**.
3. Compile (`Ctrl + Shift + B`) and run tests (`Ctrl + F5`).
4. Successful run output:
   ```text
   All tests passed!
   ```

---

## 👨‍💻 Author

- **Davit Bakhshyan ([DavitBakh](https://github.com/DavitBakh))**
