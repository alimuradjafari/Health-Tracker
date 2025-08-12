#ifndef DOCTOR_H
#define DOCTOR_H

#include "User.h"
#include "Patient.h"
#include <vector>
#include <memory>
using namespace std;

class Doctor : public User {
public:
    Doctor(const string& u, const string& n, int a);

    void displayMenu() const override;
    void saveToFile() const override;
    void loadFromFile() override;

    void viewPatientRecords(const vector<unique_ptr<Patient>>& patients) const;
};

#endif