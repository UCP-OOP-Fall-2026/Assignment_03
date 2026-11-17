#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
    const int id;
    std::string name;
    int semester;
    double cgpa;
    static int registeredCount;

public:
    Student(int id, const std::string& name, int semester, double cgpa);

    int getId() const;
    void update(const std::string& name, int semester, double cgpa);
    void display() const;
    static int totalRegistered();
    static void displayStudent(const Student* student);
};

#endif
