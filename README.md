# Data Structures Implementations

A compact, well-documented collection of classic data structures with clear APIs, example usage, and notes on time/space trade‑offs.

> Languages used across folders: **C++**

---

## 📚 Contents
- [Overview](#overview)
- [Implemented Structures](#implemented-structures)
- [Complexity Cheat Sheet](#complexity-cheat-sheet)
- [Project Layout](#project-layout)
- [Getting Started](#getting-started)
- [Examples](#examples)
- [Tests](#tests)
- [Benchmarks](#benchmarks)
- [Design Notes](#design-notes)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [License](#license)

---

## Overview
This repository is a study and reference hub for common data structures. Each folder includes:
- A clean implementation
- Short, runnable examples
- Comments with edge cases and key ideas

The goal: write code you can read in six months and still smile.

---

## Implemented Structures
- **Binary Search Tree (BST)**
  - Insert, search, delete, min/max, inorder/preorder/postorder, height, balance checks
- **Heaps**
  - Min‑heap / max‑heap, build‑heap, heapify, push/pop (priority queue)
- **Hash Maps**
  - Separate chaining and open addressing (linear probing), dynamic resize
- **Linked Lists**
  - Singly and doubly linked lists, push/pop front/back, reverse, cycle check (Floyd)
- **OOP / Inheritance practice**
  - Base `Collection` interface + derived types, virtual methods, and simple polymorphism demos

> Extras: input validation, guard clauses, and basic error handling.

---

## Complexity Cheat Sheet

| Structure | Insert | Search / Access | Delete | Space |
|---|---:|---:|---:|---:|
| BST (avg) | O(log n) | O(log n) | O(log n) | O(n) |
| BST (worst, skewed) | O(n) | O(n) | O(n) | O(n) |
| Heap | O(log n) | — (top O(1)) | O(log n) | O(n) |
| Hash Map (avg) | O(1) | O(1) | O(1) | O(n) |
| Hash Map (worst) | O(n) | O(n) | O(n) | O(n) |
| Singly List (at head) | O(1) | O(n) | O(1) at head | O(n) |
| Doubly List | O(1) ends | O(n) | O(1) ends | O(n) |

*Notes:* Hash map performance assumes a good hash function and a healthy load factor.

---

## Benchmarks
A light script is included to time basic operations for lists vs hash maps vs trees at sizes `n = {2k, 4k, 8k, ...}`. Results will vary by compiler, JVM, Python version, and machine.

Sample output (illustrative):
```
HashMap (avg lookup)  n=4000  -> 0.02 ms
Vector  (avg lookup)  n=4000  -> 0.18 ms
TreeMap (avg lookup)  n=4000  -> 0.11 ms
```
