#include "Patient.h"
#include <fstream>
#include <iostream>
#include <stdexcept>


Patient::Patient(const string& u, const string& n, int a)
    : User(u, n, a) {
}

void Patient::displayMenu() const {
    cout << "\n==== Patient Menu ====\n";
    cout << "1. Add Health Record\n"
        << "2. View Health Records\n"
        << "3. Add Medicine Reminder\n"
        << "4. View Medicine Reminders\n"
        << "5. Chat with DoctorBot\n"
        << "6. View Profile\n"
        << "7. Logout\n"
        << "Choice: ";
}

void Patient::addRecord(const HealthRecord& record) {
    records.push_back(record);
    saveToFile();
}

void Patient::addReminder(const MedicineReminder& reminder) {
    reminders.push_back(reminder);
    saveToFile();
}

void Patient::viewRecords() const {
    if (records.empty()) {
        cout << "No records found.\n";
        return;
    }
    cout << "\nYour Health Records:\n";
    for (const auto& r : records) {
        r.display();
    }
}

void Patient::viewReminders() const {
    if (reminders.empty()) {
        cout << "No reminders set.\n";
        return;
    }
    cout << "\nYour Medicine Reminders:\n";
    for (const auto& r : reminders) {
        r.display();
    }
}

void Patient::saveToFile() const {
    try {
        ofstream file("data/" + username + ".txt");
        if (!file) {
            throw runtime_error("Failed to open file for writing: " + username + ".txt");
        }

        file << name << "\n" << age << "\n";

        // Save health records
        for (const auto& r : records) {
            file << "RECORD\n" << r.getDate() << "\n" << r.getTemp() << "\n";
            for (const auto& s : r.getSymptoms()) {
                file << s << "\n";
            }
            file << ".\n";
        }

        // Save medicine reminders
        for (const auto& r : reminders) {
            file << "REMINDER\n" << r.toString() << "\n";
        }
    }
    catch (const exception& e) {
        cerr << "Error saving patient data: " << e.what() << endl;
    }
}

void Patient::loadFromFile() {
    try {
        ifstream file("data/" + username + ".txt");
        if (!file) {
            // File might not exist for new patients
            return;
        }

        getline(file, name);
        file >> age;
        file.ignore();

        string line;
        while (getline(file, line)) {
            if (line == "RECORD") {
                string date, symptom;
                double temp;
                vector<string> symptoms;

                getline(file, date);
                file >> temp;
                file.ignore();

                while (getline(file, symptom) && symptom != ".") {
                    symptoms.push_back(symptom);
                }

                records.emplace_back(date, temp, symptoms);
            }
            else if (line == "REMINDER") {
                string reminderStr;
                getline(file, reminderStr);

                size_t pos1 = reminderStr.find('|');
                size_t pos2 = reminderStr.find('|', pos1 + 1);

                if (pos1 == string::npos || pos2 == string::npos) {
                    throw runtime_error("Invalid reminder format: " + reminderStr);
                }

                string name = reminderStr.substr(0, pos1);
                string time = reminderStr.substr(pos1 + 1, pos2 - pos1 - 1);
                string dosage = reminderStr.substr(pos2 + 1);

                reminders.emplace_back(name, time, dosage);
            }
        }
    }
    catch (const exception& e) {
        cerr << "Error loading patient data: " << e.what() << endl;
    }
}