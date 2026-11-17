# CSCP2023 — OOP Assignment: Advanced OOP Programming

**Name:** _Add your name_<br>
**Registration No.:** _Add your registration number_

The assignment paper is included as [`Assignment.pdf`](Assignment.pdf).

## Project structure

```text
.
├── Assignment.pdf
├── Makefile
├── README.md
└── src/
    ├── main.cpp
    ├── Student.h / Student.cpp
    ├── Wallet.h / Wallet.cpp
    ├── Product.h / Product.cpp
    ├── ResourceManager.h / ResourceManager.cpp
    ├── Patient.h / Patient.cpp
    └── HospitalManager.h / HospitalManager.cpp
```

The menu in `src/main.cpp` runs any of the four assignment questions. Each class has its own header and implementation file.

## Build and run

With GNU Make and a C++17 compiler:

```sh
make
make run
make clean
```

Or compile directly:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic src/*.cpp -o oop_assignment
./oop_assignment
```

On Windows with MinGW, run `oop_assignment.exe` after compiling.

## Design notes

- `Wallet::operator+` returns the combined balance; `operator-` returns Wallet 1's balance minus Wallet 2's.
- Wallet transaction records and Patient daily charges use dynamically allocated arrays. Their copy constructors make independent copies.
- Product `operator+` combines stock only when both products have the same ID. Product `operator[]` reads a stock-history entry.
- Patient `operator+` returns the combined bills. Select a day with `setIncrementDay(day)` before using prefix or postfix `++` to add Rs. 100 to that day's charge.
- Assignment operators copy mutable information while preserving the destination object's constant ID.

## Requirements checklist

- [x] Separate header and implementation files for each class
- [x] One menu-based `main.cpp` demonstrates all four questions
- [x] No global variables, public data members, or inheritance
- [x] Required arrays and dynamic memory are used instead of STL containers
- [x] Deep copy is implemented for dynamically allocated records
- [x] The menu exercises the required overloaded operators with multiple objects
