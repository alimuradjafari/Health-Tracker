#include "MedicineReminder.h"
#include <iostream>

MedicineReminder::MedicineReminder(const string& name,const string& t, const string& d): medicineName(name), time(t), dosage(d) {}

void MedicineReminder::display() const {
    cout << medicineName << " - " << dosage << " at " << time << "\n";
}

string MedicineReminder::toString() const {
    return medicineName + "|" + time + "|" + dosage;
}