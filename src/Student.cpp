#include "Student.h"

#include <iostream>

int Student::registeredCount = 0;

Student::Student(int id, const std::string& name, int semester, double cgpa)
    : id(id), name(name), semester(semester), cgpa(cgpa) {
    ++registeredCount;
}

int Student::getId() const {
    return id;
}

void Student::update(const std::string& name, int semester, double cgpa) {
    this->name = name;
    this->semester = semester;
    this->cgpa = cgpa;
}

void Student::display() const {
    std::cout << "Student ID: " << id
              << "\nName: " << name
              << "\nSemester: " << semester
              << "\nCGPA: " << cgpa << '\n';
}

int Student::totalRegistered() {
    return registeredCount;
}

void Student::displayStudent(const Student* student) {
    if (student != nullptr) {
        student->display();
    }
}
