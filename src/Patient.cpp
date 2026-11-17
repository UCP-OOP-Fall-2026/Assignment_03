#include "Patient.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

int Patient::registeredCount = 0;

Patient::Patient(int id, const std::string& name, int age,
                 const double* charges, int days)
    : id(id), name(name), age(age),
      charges(days > 0 ? new double[days] : nullptr),
      days(days), incrementDay(0) {
    if (days < 0) {
        throw std::invalid_argument("Treatment days cannot be negative.");
    }

    for (int i = 0; i < days; ++i) {
        this->charges[i] = charges[i];
    }
    ++registeredCount;
}

Patient::Patient(const Patient& other)
    : id(other.id), name(other.name), age(other.age),
      charges(other.days > 0 ? new double[other.days] : nullptr),
      days(other.days), incrementDay(other.incrementDay) {
    // The copy owns its own array of treatment charges.
    for (int i = 0; i < days; ++i) {
        charges[i] = other.charges[i];
    }
}

Patient::~Patient() {
    delete[] charges;
}

Patient& Patient::operator=(const Patient& other) {
    if (this == &other) {
        return *this;
    }

    double* copiedCharges = nullptr;
    if (other.days > 0) {
        copiedCharges = new double[other.days];
        for (int i = 0; i < other.days; ++i) {
            copiedCharges[i] = other.charges[i];
        }
    }

    delete[] charges;
    charges = copiedCharges;
    days = other.days;
    name = other.name;
    age = other.age;
    incrementDay = other.incrementDay < days ? other.incrementDay : 0;

    // The patient ID is const, so assignment keeps this object's ID.
    return *this;
}

double Patient::totalBill() const {
    double total = 0;
    for (int i = 0; i < days; ++i) {
        total += charges[i];
    }
    return total;
}

double Patient::operator+(const Patient& other) const {
    return totalBill() + other.totalBill();
}

bool Patient::operator>(const Patient& other) const {
    return std::round(totalBill() * 100) >
           std::round(other.totalBill() * 100);
}

bool Patient::operator==(const Patient& other) const {
    return std::round(totalBill() * 100) ==
           std::round(other.totalBill() * 100);
}

void Patient::increaseCharge(int day, double amount) {
    if (day < 0 || day >= days) {
        throw std::out_of_range("Treatment day is out of range.");
    }
    charges[day] += amount;
}

void Patient::setIncrementDay(int day) {
    if (day < 0 || day >= days) {
        throw std::out_of_range("Treatment day is out of range.");
    }
    incrementDay = day;
}

double& Patient::operator[](int day) {
    if (day < 0 || day >= days) {
        throw std::out_of_range("Treatment day is out of range.");
    }
    return charges[day];
}

double Patient::operator[](int day) const {
    if (day < 0 || day >= days) {
        throw std::out_of_range("Treatment day is out of range.");
    }
    return charges[day];
}

Patient& Patient::operator++() {
    if (days > 0) {
        charges[incrementDay] += 100;
    }
    return *this;
}

Patient Patient::operator++(int) {
    Patient oldVersion(*this);
    ++(*this);
    return oldVersion;
}

int Patient::totalRegistered() {
    return registeredCount;
}

std::ostream& operator<<(std::ostream& out, const Patient& patient) {
    out << "Patient ID: " << patient.id
        << "\nName: " << patient.name
        << "\nAge: " << patient.age
        << "\nDaily treatment charges:\n";

    for (int i = 0; i < patient.days; ++i) {
        out << "Day " << i + 1 << ": Rs. " << patient.charges[i] << '\n';
    }
    out << "Total Bill: Rs. " << patient.totalBill() << '\n';
    return out;
}

void compareBills(const Patient& first, const Patient& second) {
    if (first > second) {
        std::cout << first.name << " has the higher bill.\n";
    } else if (second > first) {
        std::cout << second.name << " has the higher bill.\n";
    } else {
        std::cout << "Both patients have equal treatment bills.\n";
    }
}
