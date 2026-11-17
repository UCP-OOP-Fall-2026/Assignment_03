#include "HospitalManager.h"

#include <iostream>

void HospitalManager::generateReport(const Patient* patients, int count) const {
    for (int i = 0; i < count; ++i) {
        std::cout << "Patient " << i + 1 << ":\n";
        std::cout << patients[i] << '\n';
    }
}
