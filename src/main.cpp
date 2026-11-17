#include "HospitalManager.h"
#include "Patient.h"
#include "Product.h"
#include "ResourceManager.h"
#include "Student.h"
#include "Wallet.h"

#include <iostream>
#include <new>
#include <string>

void deleteStudentInput(int* ids, int* semesters, double* cgpas,
                        std::string* names) {
    delete[] ids;
    delete[] semesters;
    delete[] cgpas;
    delete[] names;
}

void runQuestion1() {
    int studentCount;
    std::cout << "\nNumber of students: ";
    if (!(std::cin >> studentCount) || studentCount <= 0) {
        std::cout << "Enter a positive number of students.\n";
        return;
    }

    int* studentIds = new int[studentCount];
    int* semesters = new int[studentCount];
    double* cgpas = new double[studentCount];
    std::string* names = new std::string[studentCount];

    for (int i = 0; i < studentCount; ++i) {
        std::cout << "\nStudent " << i + 1 << " ID: ";
        std::cin >> studentIds[i];
        std::cout << "Name: ";
        std::cin >> std::ws;
        std::getline(std::cin, names[i]);
        std::cout << "Semester: ";
        std::cin >> semesters[i];
        std::cout << "CGPA: ";
        std::cin >> cgpas[i];
    }

    // Each Student must be constructed with its final, constant ID.
    Student* students = static_cast<Student*>(
        ::operator new[](sizeof(Student) * studentCount));
    for (int i = 0; i < studentCount; ++i) {
        new (&students[i]) Student(studentIds[i], names[i], semesters[i], cgpas[i]);
    }

    int searchId;
    std::cout << "\nEnter Student ID to search: ";
    std::cin >> searchId;

    bool foundStudent = false;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].getId() == searchId) {
            std::cout << "Student Record Found:\n";
            Student::displayStudent(&students[i]);
            foundStudent = true;
            break;
        }
    }
    if (!foundStudent) {
        std::cout << "Student not found.\n";
    }
    std::cout << "Total Registered Students: "
              << Student::totalRegistered() << '\n';

    for (int i = 0; i < studentCount; ++i) {
        students[i].~Student();
    }
    ::operator delete[](students);
    deleteStudentInput(studentIds, semesters, cgpas, names);
}

void runWalletTransactions(Wallet& wallet) {
    int transactionCount;
    std::cout << "Number of transactions: ";
    if (!(std::cin >> transactionCount) || transactionCount < 0) {
        std::cout << "Enter a non-negative transaction count.\n";
        return;
    }

    for (int i = 0; i < transactionCount; ++i) {
        char transactionType;
        double amount;
        std::cout << "Enter D amount to deposit or W amount to withdraw: ";
        std::cin >> transactionType >> amount;

        if (amount <= 0) {
            std::cout << "Amount must be positive.\n";
        } else if (transactionType == 'D' || transactionType == 'd') {
            wallet.deposit(amount);
        } else if (transactionType == 'W' || transactionType == 'w') {
            if (!wallet.withdraw(amount)) {
                std::cout << "Withdrawal rejected.\n";
            }
        } else {
            std::cout << "Unknown transaction type.\n";
        }
    }
}

void runQuestion2() {
    int firstId, secondId;
    double firstBalance, secondBalance;
    std::string firstOwner, secondOwner;

    std::cout << "\nWallet 1 ID: ";
    if (!(std::cin >> firstId)) return;
    std::cout << "Wallet 1 owner name: ";
    std::cin >> std::ws;
    std::getline(std::cin, firstOwner);
    std::cout << "Wallet 1 initial balance: ";
    if (!(std::cin >> firstBalance) || firstBalance < 0) return;

    std::cout << "Wallet 2 ID: ";
    if (!(std::cin >> secondId)) return;
    std::cout << "Wallet 2 owner name: ";
    std::cin >> std::ws;
    std::getline(std::cin, secondOwner);
    std::cout << "Wallet 2 initial balance: ";
    if (!(std::cin >> secondBalance) || secondBalance < 0) return;

    Wallet firstWallet(firstId, firstOwner, firstBalance);
    Wallet secondWallet(secondId, secondOwner, secondBalance);

    std::cout << "\nTransactions for Wallet 1:\n";
    runWalletTransactions(firstWallet);
    std::cout << "Transactions for Wallet 2:\n";
    runWalletTransactions(secondWallet);

    std::cout << "\nWallet 1:\n" << firstWallet;
    std::cout << "Wallet 2:\n" << secondWallet;
    compareWallets(firstWallet, secondWallet);

    std::cout << "Combined balance: Rs. "
              << firstWallet + secondWallet << '\n';
    std::cout << "Balance difference (Wallet 1 - Wallet 2): Rs. "
              << firstWallet - secondWallet << '\n';
    std::cout << "Equal balances: "
              << (firstWallet == secondWallet ? "yes" : "no") << '\n';

    Wallet copiedWallet(firstWallet);
    copiedWallet.deposit(250);
    std::cout << "\nOriginal wallet:\n" << firstWallet;
    std::cout << "Copied wallet after another deposit:\n" << copiedWallet;

    Wallet assignedWallet(999, "Temporary", 0);
    assignedWallet = firstWallet;
    std::cout << "Assignment copy (destination ID remains 999):\n"
              << assignedWallet;
    std::cout << "Total wallets created: " << Wallet::totalCreated() << '\n';
}

void deleteProductInput(int* ids, int* quantities, double* prices,
                        std::string* names, std::string* categories) {
    delete[] ids;
    delete[] quantities;
    delete[] prices;
    delete[] names;
    delete[] categories;
}

void runQuestion3() {
    int productCount;
    std::cout << "\nNumber of products: ";
    if (!(std::cin >> productCount) || productCount <= 0) {
        std::cout << "Enter a positive number of products.\n";
        return;
    }

    int* productIds = new int[productCount];
    int* quantities = new int[productCount];
    double* prices = new double[productCount];
    std::string* names = new std::string[productCount];
    std::string* categories = new std::string[productCount];

    for (int i = 0; i < productCount; ++i) {
        std::cout << "\nProduct " << i + 1 << " ID: ";
        std::cin >> productIds[i];
        std::cout << "Name: ";
        std::cin >> std::ws;
        std::getline(std::cin, names[i]);
        std::cout << "Category: ";
        std::getline(std::cin, categories[i]);
        std::cout << "Price and quantity: ";
        std::cin >> prices[i] >> quantities[i];

        if (prices[i] < 0 || quantities[i] < 0) {
            std::cout << "Price and quantity cannot be negative.\n";
            deleteProductInput(productIds, quantities, prices, names, categories);
            return;
        }
    }

    // Product IDs are const, so construct each product after reading its ID.
    Product* products = static_cast<Product*>(
        ::operator new[](sizeof(Product) * productCount));
    for (int i = 0; i < productCount; ++i) {
        new (&products[i]) Product(productIds[i], names[i], categories[i],
                                   prices[i], quantities[i]);
    }

    int searchId;
    std::cout << "Enter Product ID to search: ";
    std::cin >> searchId;
    bool foundProduct = false;
    for (int i = 0; i < productCount; ++i) {
        if (products[i].getId() == searchId) {
            std::cout << "Product found:\n" << products[i];
            foundProduct = true;
            break;
        }
    }
    if (!foundProduct) {
        std::cout << "Product not found.\n";
    }

    double minimumPrice, maximumPrice;
    std::cout << "Enter minimum and maximum price: ";
    std::cin >> minimumPrice >> maximumPrice;
    std::cout << "Products within the price range:\n";
    for (int i = 0; i < productCount; ++i) {
        if (products[i].getPrice() >= minimumPrice &&
            products[i].getPrice() <= maximumPrice) {
            std::cout << products[i];
        }
    }

    int idToUpdate, stockToAdd;
    std::cout << "Enter Product ID and quantity to add: ";
    std::cin >> idToUpdate >> stockToAdd;
    ResourceManager inventoryManager;
    bool stockUpdated = false;
    for (int i = 0; i < productCount; ++i) {
        if (products[i].getId() == idToUpdate) {
            if (products[i].getQuantity() + stockToAdd < 0) {
                std::cout << "Stock cannot become negative.\n";
            } else {
                inventoryManager.updateStock(&products[i], stockToAdd);
                std::cout << "Updated product:\n" << products[i];
            }
            stockUpdated = true;
            break;
        }
    }
    if (!stockUpdated) {
        std::cout << "Product not found.\n";
    }

    if (productCount >= 2) {
        std::cout << "First product costs more than the second: "
                  << (products[0] > products[1] ? "yes" : "no") << '\n';
        std::cout << "First two products have the same ID: "
                  << (products[0] == products[1] ? "yes" : "no") << '\n';
    }

    // Products with the same ID can combine their stock using +.
    {
        Product copiedProduct(products[0]);
        std::cout << "Combined stock with a copy: "
                  << products[0] + copiedProduct << '\n';
        std::cout << "First stock-history value: " << products[0][0] << '\n';

        ++copiedProduct;
        Product previousVersion = copiedProduct++;
        std::cout << "Stock after prefix and postfix ++: "
                  << copiedProduct.getQuantity() << '\n';
        std::cout << "Stock returned by postfix ++: "
                  << previousVersion.getQuantity() << '\n';

        Product assignedProduct(products[0]);
        assignedProduct = copiedProduct;
        std::cout << "Assignment keeps product ID: "
                  << assignedProduct.getId() << '\n';
    }

    std::cout << "\nComplete inventory report:\n";
    inventoryManager.displayInventory(products, productCount);
    std::cout << "Total products in inventory: "
              << Product::totalStored() << '\n';

    for (int i = 0; i < productCount; ++i) {
        products[i].~Product();
    }
    ::operator delete[](products);
    deleteProductInput(productIds, quantities, prices, names, categories);
}

void deletePatientInput(int* ids, int* ages, int* treatmentDays,
                        std::string* names, double** dailyCharges,
                        int patientCount) {
    for (int i = 0; i < patientCount; ++i) {
        delete[] dailyCharges[i];
    }
    delete[] ids;
    delete[] ages;
    delete[] treatmentDays;
    delete[] names;
    delete[] dailyCharges;
}

void runQuestion4() {
    int patientCount;
    std::cout << "\nNumber of patients: ";
    if (!(std::cin >> patientCount) || patientCount <= 0) {
        std::cout << "Enter a positive number of patients.\n";
        return;
    }

    int* patientIds = new int[patientCount];
    int* ages = new int[patientCount];
    int* treatmentDays = new int[patientCount];
    std::string* names = new std::string[patientCount];
    double** dailyCharges = new double*[patientCount]();

    for (int i = 0; i < patientCount; ++i) {
        std::cout << "\nPatient " << i + 1 << " ID: ";
        std::cin >> patientIds[i];
        std::cout << "Name: ";
        std::cin >> std::ws;
        std::getline(std::cin, names[i]);
        std::cout << "Age and number of treatment days: ";
        std::cin >> ages[i] >> treatmentDays[i];

        if (ages[i] < 0 || treatmentDays[i] < 0) {
            std::cout << "Age and treatment days cannot be negative.\n";
            deletePatientInput(patientIds, ages, treatmentDays, names,
                               dailyCharges, patientCount);
            return;
        }

        dailyCharges[i] = new double[treatmentDays[i]];
        for (int day = 0; day < treatmentDays[i]; ++day) {
            std::cout << "Charge for Day " << day + 1 << ": ";
            std::cin >> dailyCharges[i][day];
        }
    }

    // Patient IDs are const, so construct each patient with its final ID.
    Patient* patients = static_cast<Patient*>(
        ::operator new[](sizeof(Patient) * patientCount));
    for (int i = 0; i < patientCount; ++i) {
        new (&patients[i]) Patient(patientIds[i], names[i], ages[i],
                                   dailyCharges[i], treatmentDays[i]);
    }

    HospitalManager hospitalManager;
    std::cout << "\nPatient Billing Report:\n";
    hospitalManager.generateReport(patients, patientCount);

    if (patientCount >= 2) {
        std::cout << "Comparing Patient Bills:\n";
        compareBills(patients[0], patients[1]);
        std::cout << "Combined bill: Rs. "
                  << patients[0] + patients[1] << '\n';
        std::cout << "Bills are equal: "
                  << (patients[0] == patients[1] ? "yes" : "no") << '\n';
    }

    int patientNumber, dayNumber;
    std::cout << "Enter patient number and day number: ";
    std::cin >> patientNumber >> dayNumber;
    if (patientNumber >= 1 && patientNumber <= patientCount &&
        dayNumber >= 1 && dayNumber <= treatmentDays[patientNumber - 1]) {
        std::cout << "Treatment charge: Rs. "
                  << patients[patientNumber - 1][dayNumber - 1] << '\n';
    } else {
        std::cout << "Invalid patient number or treatment day.\n";
    }

    const int selectedPatient =
        (patientNumber >= 1 && patientNumber <= patientCount)
            ? patientNumber - 1
            : 0;
    {
        Patient copiedPatient(patients[selectedPatient]);
        if (treatmentDays[selectedPatient] > 0) {
            int selectedDay = 0;
            if (dayNumber >= 1 && dayNumber <= treatmentDays[selectedPatient]) {
                selectedDay = dayNumber - 1;
            }
            copiedPatient.setIncrementDay(selectedDay);
            copiedPatient[selectedDay] += 500;
        }

        Patient assignedPatient(patients[selectedPatient]);
        assignedPatient = patients[selectedPatient];
        Patient beforePostfixIncrement = copiedPatient++;
        ++copiedPatient;

        std::cout << "\nOriginal patient (unchanged):\n"
                  << patients[selectedPatient];
        std::cout << "Modified deep copy:\n" << copiedPatient;
        std::cout << "Postfix returned the earlier copy: "
                  << (beforePostfixIncrement == patients[selectedPatient]
                          ? "yes"
                          : "no") << '\n';
        std::cout << "Assignment copy:\n" << assignedPatient;
    }

    std::cout << "Total registered patients: "
              << Patient::totalRegistered() << '\n';

    for (int i = 0; i < patientCount; ++i) {
        patients[i].~Patient();
    }
    ::operator delete[](patients);
    deletePatientInput(patientIds, ages, treatmentDays, names, dailyCharges,
                       patientCount);
}

int main() {
    int choice = -1;

    do {
        std::cout << "\n===== OOP Assignment =====\n"
                  << "1. Student Registration System\n"
                  << "2. Digital Wallet System\n"
                  << "3. Inventory Management System\n"
                  << "4. Hospital Billing System\n"
                  << "0. Exit\n"
                  << "Choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Please enter a number from 0 to 4.\n";
            return 1;
        }

        switch (choice) {
            case 1:
                runQuestion1();
                break;
            case 2:
                runQuestion2();
                break;
            case 3:
                runQuestion3();
                break;
            case 4:
                runQuestion4();
                break;
            case 0:
                std::cout << "Goodbye.\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
