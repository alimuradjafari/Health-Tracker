#ifndef PATIENT_H
#define PATIENT_H

#include "User.h"
#include "HealthRecord.h"
#include "MedicineReminder.h"
#include <vector>
using namespace std;

class Patient : public User {
private:
    vector<HealthRecord> records;
    vector<MedicineReminder> reminders;

public:
    Patient(const string& u, const string& n, int a);

    void displayMenu() const override;
    void saveToFile() const override;
    void loadFromFile() override;

    void addRecord(const HealthRecord& record);
    void addReminder(const MedicineReminder& reminder);
    void viewRecords() const;
    void viewReminders() const;

    const vector<HealthRecord>& getRecords() const { return records; }
};

#endif