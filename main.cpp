#include <iostream>

// Create your own .h/.cpp file for each class (see README.md) and include
// the headers here as you write them, e.g.:
// #include "Student.h"

using namespace std;

// No global variables: each demo creates its own objects locally.

void runQuestion1() {
    cout << "Q1: Student Registration System - TODO" << endl;
    // TODO: read students, search by ID, show total registered
}

void runQuestion2() {
    cout << "Q2: Digital Wallet System - TODO" << endl;
    // TODO: deposits/withdrawals, compareWallets, operators, deep-copy demo
}

void runQuestion3() {
    cout << "Q3: Inventory Management System - TODO" << endl;
    // TODO: price-range search, stock update, ResourceManager, operators
}

void runQuestion4() {
    cout << "Q4: Hospital Billing System - TODO" << endl;
    // TODO: patients, compareBills, HospitalManager report, operators
}

int main() {
    int choice = 0;
    do {
        cout << "\n===== OOP Assignment =====\n"
             << "1. Student Registration System\n"
             << "2. Digital Wallet System\n"
             << "3. Inventory Management System\n"
             << "4. Hospital Billing System\n"
             << "0. Exit\n"
             << "Choice: ";
        cin >> choice;
        switch (choice) {
            case 1: runQuestion1(); break;
            case 2: runQuestion2(); break;
            case 3: runQuestion3(); break;
            case 4: runQuestion4(); break;
            case 0: break;
            default: cout << "Invalid choice." << endl;
        }
    } while (choice != 0);
    return 0;
}
