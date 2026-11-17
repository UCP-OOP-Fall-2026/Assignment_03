#ifndef HOSPITALMANAGER_H
#define HOSPITALMANAGER_H

#include "Patient.h"

class HospitalManager {
public:
    void generateReport(const Patient* patients, int count) const;
};

#endif
