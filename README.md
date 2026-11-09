# CSCP2023 – OOP Assignment: Advanced OOP Programming

**Name:** _your name_
**Registration No.:** _your reg. number_

The full assignment is in [`docs/Assignment.pdf`](docs/Assignment.pdf).

## Project Structure

Only `src/main.cpp` is provided. **You create the rest** by adding a `.h` and a
`.cpp` file for every class inside `src/`. When you are done it should look like:

```text
.
├── README.md
├── Makefile
├── docs/
│   └── Assignment.pdf
└── src/
    ├── main.cpp                 # provided: menu for all four questions
    ├── Student.h / Student.cpp  # you create (Q1)
    └── ...                      # same for Wallet, Product, ResourceManager,
                                 # Patient, HospitalManager
```

### How to split a class into `.h` and `.cpp`

Example class (not part of the assignment):

`src/Book.h` : declaration only
```cpp
#ifndef BOOK_H
#define BOOK_H
#include <string>

class Book {
    std::string title;
    int pages;
public:
    Book(std::string t, int p);
    void display() const;
};

#endif
```

`src/Book.cpp` : function bodies, with `Book::` in front of each name
```cpp
#include "Book.h"
#include <iostream>
using namespace std;

Book::Book(string t, int p) : title(t), pages(p) {}

void Book::display() const {
    cout << title << " (" << pages << " pages)" << endl;
}
```

`src/main.cpp` : just include the header
```cpp
#include "Book.h"
// ...
```

The Makefile compiles every `.cpp` in `src/` automatically, so new files need no
extra setup.

## Compilation Instructions

Using the Makefile (needs `g++` and `make`):

```bash
make        # build
make run    # build and run
make clean  # remove build files
```

Without make:

```bash
g++ -std=c++17 -Wall -Wextra src/*.cpp -o oop_assignment
./oop_assignment      # Windows: oop_assignment.exe
```

## Notes on My Implementation

_Briefly describe design decisions here (e.g. what `+` returns for Wallet, how
`[]` is used in Product), as you may be asked to explain them during evaluation._

## Rules Checklist

- [ ] Separate `.h` and `.cpp` file for each class
- [ ] `main.cpp` demonstrates all functionality
- [ ] No global variables, no public data members
- [ ] No inheritance, no STL containers replacing required arrays
- [ ] Deep copy where needed, no memory leaks or dangling pointers
- [ ] All overloaded operators tested with multiple objects
- [ ] Committed regularly with meaningful messages (e.g. `Q2: Wallet deep copy done`)
