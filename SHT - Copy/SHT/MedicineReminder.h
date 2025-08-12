#ifndef MEDICINEREMINDER_H
#define MEDICINEREMINDER_H

#include <string>
using namespace std;

class MedicineReminder {
private:
    string medicineName;
    string time;
    string dosage;

public:
    MedicineReminder(const string& name, const string& t, const string& d);
    void display() const;
    string toString() const;
};

#endif