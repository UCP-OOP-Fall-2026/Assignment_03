#ifndef PATIENT_H
#define PATIENT_H

#include <iosfwd>
#include <string>

class HospitalManager;

class Patient {
    const int id;
    std::string name;
    int age;
    double* charges;
    int days;
    int incrementDay;
    static int registeredCount;

    double totalBill() const;

public:
    Patient(int id, const std::string& name, int age, const double* charges, int days);
    Patient(const Patient& other);
    ~Patient();

    Patient& operator=(const Patient& other);
    double operator+(const Patient& other) const;
    bool operator>(const Patient& other) const;
    bool operator==(const Patient& other) const;

    void increaseCharge(int day, double amount);
    void setIncrementDay(int day);
    double& operator[](int day);
    double operator[](int day) const;

    Patient& operator++();
    Patient operator++(int);

    static int totalRegistered();
    friend void compareBills(const Patient&, const Patient&);
    friend class HospitalManager;
    friend std::ostream& operator<<(std::ostream&, const Patient&);
};

#endif
