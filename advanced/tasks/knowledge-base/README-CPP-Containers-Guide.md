# Extended C++ Containers Tutorial: `vector`, `unordered_set`, `unordered_map`, and `map`

## Table of Contents

1. [Introduction](#introduction)
2. [Containers Overview](#containers-overview)
3. [Vector](#vector)
4. [Unordered Set](#unordered-set)
5. [Unordered Map](#unordered-map)
6. [Ordered Map (std::map)](#ordered-map-stdmap)
7. [Comparison and Usage Scenarios](#comparison-and-usage-scenarios)
8. [Project Idea](#project-idea) - A sample project using all containers together

---

## Introduction

This guide covers key C++ containers, including **full code examples** for commonly used functions, different construction methods, iteration techniques, and complex examples.

---

## Containers Overview

| Container         | Characteristics                            | Lookup Time | Insertion Time | Allows Duplicates | Ordered |
| ----------------- | ------------------------------------------ | ----------- | -------------- | ----------------- | ------- |
| **Vector**        | Dynamic array, indexed by position         | `O(1)`      | `O(1)` (end)   | Yes               | No      |
| **Unordered Set** | Stores unique items with hash-based lookup | `O(1)`      | `O(1)`         | No                | No      |
| **Unordered Map** | Key-value pairs with hash-based lookup     | `O(1)`      | `O(1)`         | No (unique keys)  | No      |
| **Map**           | Key-value pairs with tree-based lookup     | `O(log n)`  | `O(log n)`     | No (unique keys)  | Yes     |

---

## Unordered Map

An `unordered_map` is a hash-based dictionary that stores unique keys associated with values. It provides efficient lookup and insertion in constant average time.

### Commonly Used Functions

| Function               | Description                 | Example Usage                          |
| ---------------------- | --------------------------- | -------------------------------------- |
| `insert({key, value})` | Inserts a key-value pair    | `myMap.insert({1, "Alice"});`          |
| `erase(key)`           | Removes a key-value pair    | `myMap.erase(1);`                      |
| `find(key)`            | Finds element by key        | `if (myMap.find(1) != myMap.end()) {}` |
| `size()`               | Returns the number of pairs | `size_t n = myMap.size();`             |
| `clear()`              | Removes all pairs           | `myMap.clear();`                       |
| `empty()`              | Checks if map is empty      | `bool isEmpty = myMap.empty();`        |
| `count(key)`           | Checks if key exists        | `if (myMap.count(1)) {}`               |
| `operator[key]`        | Accesses value by key       | `std::string name = myMap[1];`         |

### Examples

#### Basic Example

```cpp
#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<int, std::string> studentNames;
    studentNames[101] = "Alice";
    studentNames[102] = "Bob";

    std::cout << "Student Names:" << std::endl;
    for (const auto& [id, name] : studentNames) {
        std::cout << "ID: " << id << ", Name: " << name << std::endl;
    }
    std::cout << "Size: " << studentNames.size() << std::endl;

    return 0;
}
// Output:
// ID: 101, Name: Alice
// ID: 102, Name: Bob
// Size: 2
```

#### Intermediate Example

```cpp
#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> wordCount;
    wordCount["apple"] = 2;
    wordCount["banana"] = 3;

    // Access and update values
    wordCount["apple"] += 1;

    std::cout << "Word Frequencies:" << std::endl;
    for (const auto& [word, count] : wordCount) {
        std::cout << word << ": " << count << std::endl;
    }
    return 0;
}
// Output:
// Word Frequencies:
// apple: 3
// banana: 3
```

#### Hard Example

This example demonstrates counting the frequency of each character in a string using an `unordered_map`.

```cpp
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    std::string text = "university";
    std::unordered_map<char, int> charCount;

    // Count the frequency of each character
    for (char ch : text) {
        charCount[ch]++;
    }

    std::cout << "Character Frequencies:" << std::endl;
    for (const auto& [ch, count] : charCount) {
        std::cout << ch << ": " << count << std::endl;
    }
    return 0;
}
// Output:
// Character Frequencies:
// u: 1
// n: 1
// i: 2
// v: 1
// e: 1
// r: 1
// s: 1
// t: 1
// y: 1
```

### Different Ways to Iterate Over an Unordered Map

```cpp
std::unordered_map<int, std::string> studentNames = {{101, "Alice"}, {102, "Bob"}};

// Range-based for loop with structured binding
for (const auto& [id, name] : studentNames) {
    std::cout << "ID: " << id << ", Name: " << name << std::endl;
}

// Iterator-based loop
for (auto it = studentNames.begin(); it != studentNames.end(); ++it) {
    std::cout << "ID: " << it->first << ", Name: " << it->second << std::endl;
}
```

### Complex Example

This example combines insertion, deletion, and iteration on an `unordered_map` representing student grades.

```cpp
#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<int, std::string> studentGrades;

    // Insert student grades
    studentGrades[101] = "A";
    studentGrades[102] = "B";
    studentGrades[103] = "C";

    // Update a grade
    studentGrades[102] = "A";

    // Remove a student by ID
    studentGrades.erase(103);

    // Display student grades
    std::cout << "Student Grades:" << std::endl;
    for (const auto& [id, grade] : studentGrades) {
        std::cout << "ID: " << id << ", Grade: " << grade << std::endl;
    }

    return 0;
}
// Output:
// Student Grades:
// ID: 101, Grade: A
// ID: 102, Grade: A
```

---

## Ordered Map (std::map)

A `map` (ordered map) is a tree-based dictionary that stores unique keys with associated values in sorted order by keys. It is implemented as a balanced binary tree, providing logarithmic time complexity for lookups, insertions, and deletions.

### Commonly Used Functions

| Function               | Description                 | Example Usage                          |
| ---------------------- | --------------------------- | -------------------------------------- |
| `insert({key, value})` | Inserts a key-value pair    | `myMap.insert({1, "Alice"});`          |
| `erase(key)`           | Removes a key-value pair    | `myMap.erase(1);`                      |
| `find(key)`            | Finds element by key        | `if (myMap.find(1) != myMap.end()) {}` |
| `size()`               | Returns the number of pairs | `size_t n = myMap.size();`             |
| `clear()`              | Removes all pairs           | `myMap.clear();`                       |
| `empty()`              | Checks if map is empty      | `bool isEmpty = myMap.empty();`        |
| `count(key)`           | Checks if key exists        | `if (myMap.count(1)) {}`               |
| `operator[key]`        | Accesses value by key       | `std::string name = myMap[1];`         |

### Examples

#### Basic Example

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> studentNames;
    studentNames[101] = "Alice";
    studentNames[102] = "Bob";

    std::cout << "Student Names:" << std::endl;
    for (const auto& [id, name] : studentNames) {
        std::cout << "ID: " << id << ", Name: " << name << std::endl;
    }
    std::cout << "Size: " << studentNames.size() << std::endl;

    return 0;
}
// Output:
// ID: 101, Name: Alice
// ID: 102, Name: Bob
// Size: 2
```

#### Intermediate

Example

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> orderedMap;
    orderedMap[3] = "three";
    orderedMap[1] = "one";
    orderedMap[2] = "two";

    std::cout << "Ordered Map:" << std::endl;
    for (const auto& [key, value] : orderedMap) {
        std::cout << key << ": " << value << std::endl;
    }

    return 0;
}
// Output (sorted by key):
// 1: one
// 2: two
// 3: three
```

#### Hard Example

This example demonstrates finding the minimum and maximum key-value pairs in a `map`.

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> items;
    items[10] = "apple";
    items[20] = "banana";
    items[30] = "carrot";

    // Find minimum and maximum keys
    auto minItem = *items.begin();
    auto maxItem = *items.rbegin();

    std::cout << "Min Item: " << minItem.first << " -> " << minItem.second << std::endl;
    std::cout << "Max Item: " << maxItem.first << " -> " << maxItem.second << std::endl;

    return 0;
}
// Output:
// Min Item: 10 -> apple
// Max Item: 30 -> carrot
```

### Different Ways to Iterate Over a Map

```cpp
std::map<int, std::string> orderedMap = {{1, "one"}, {2, "two"}, {3, "three"}};

// Range-based for loop with structured binding
for (const auto& [key, value] : orderedMap) {
    std::cout << key << ": " << value << std::endl;
}

// Iterator-based loop
for (auto it = orderedMap.begin(); it != orderedMap.end(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
}

// Reverse iteration
for (auto rit = orderedMap.rbegin(); rit != orderedMap.rend(); ++rit) {
    std::cout << rit->first << ": " << rit->second << std::endl;
}
```

### Complex Example

This example combines insertion, deletion, and iteration on a `map` representing product prices.

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<int, double> productPrices;

    // Insert product prices
    productPrices[1001] = 19.99;
    productPrices[1002] = 29.99;
    productPrices[1003] = 39.99;

    // Update a price
    productPrices[1002] = 24.99;

    // Remove a product by ID
    productPrices.erase(1003);

    // Display product prices
    std::cout << "Product Prices:" << std::endl;
    for (const auto& [id, price] : productPrices) {
        std::cout << "ID: " << id << ", Price: $" << price << std::endl;
    }

    return 0;
}
// Output:
// Product Prices:
// ID: 1001, Price: $19.99
// ID: 1002, Price: $24.99
```

---

## Project Idea

### Inventory Management System

Using `vector`, `unordered_set`, `unordered_map`, and `map` together, build a simple inventory system that manages products, tracks unique categories, records product prices, and allows fast lookup and sorting by product ID.
