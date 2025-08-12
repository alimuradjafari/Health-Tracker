#include "Doctor.h"
#include <iostream>
#include <stdexcept>


Doctor::Doctor(const string& u, const string& n, int a): User(u, n, a) {}

void Doctor::displayMenu() const {
    cout << "\n==== Doctor Menu ====\n";
    cout << "1. View Patient Records\n"
        << "2. View Profile\n"
        << "3. Logout\n"
        << "Choice: ";
}

void Doctor::saveToFile() const {} //doctors don't need to save additional data
void Doctor::loadFromFile() {} //doctors don't need to load additional data

void Doctor::viewPatientRecords(const vector<unique_ptr<Patient>>& patients) const {
    if (patients.empty()) {
        cout << "No patients registered.\n";
        return;
    }

    cout << "\nSelect a patient:\n";
    for (size_t i = 0; i < patients.size(); ++i) {
        cout << i + 1 << ". " << patients[i]->getName() << " (" << patients[i]->getUsername() << ")\n";
    }

    cout << "Choice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > static_cast<int>(patients.size())) {
        cout << "Invalid selection.\n";
        return;
    }

    const Patient* patient = patients[choice - 1].get();
    cout << "\nHealth records for " << patient->getName() << ":\n";
    patient->viewRecords();
}