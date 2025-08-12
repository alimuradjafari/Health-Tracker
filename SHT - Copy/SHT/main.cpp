#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <memory>
#include "UserManager.h"
#include "Patient.h"
#include "Doctor.h"
#include "DoctorBot.h"
#include "MedicineReminder.h"
#include "HealthRecord.h"
using namespace std;

void createDataDirectory() {
#ifdef _WIN32
    system("mkdir data 2> nul");
#else
    system("mkdir -p data 2> /dev/null");
#endif
}

void showMainMenu() {
    cout << "\n==== Health Tracker ====\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Exit\n";
    cout << "Choice: ";
}

void chatWithDoctorBot(DoctorBot& bot) {
    cout << "\n=== DoctorBot Chat ===\n";
    cout << "(type 'bye' to exit)\n";
    string message;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "You: ";
        getline(cin, message);

        string userMsg = message;
        for (char& c : userMsg) {
            c = tolower(c);
        }

        if (userMsg == "bye") {
            cout << "DoctorBot: Goodbye! Take care of your health.\n";
            break;
        }

        string response = bot.respondToMessage(message);
        cout << "DoctorBot: " << response << "\n";
    }
}

void addHealthRecord(Patient* patient, DoctorBot& bot) {
    string date, symptom;
    double temp;
    vector<string> symptoms;

    cout << "Enter date (DD-MM-YYYY): ";
    getline(cin, date);

    cout << "Enter temperature (in Celsius): ";
    while (!(cin >> temp)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore();

    cout << "Enter symptoms (one per line, press Enter twice to finish):\n";
    while (getline(cin, symptom)) {
        if (symptom.empty()) {
            break;
        }
        symptoms.push_back(symptom);
    }

    patient->addRecord(HealthRecord(date, temp, symptoms));
    cout << "\nHealth record added successfully!\n";

    cout << "\n=== DoctorBot Analysis ===\n";
    cout << bot.analyzeSymptoms(symptoms) << "\n";
}

void addMedicineReminder(Patient* patient) {
    string name, time, dosage;

    cout << "Medicine Name: ";
    getline(cin, name);

    cout << "Time (e.g., 08:00 AM): ";
    getline(cin, time);

    cout << "Dosage (e.g., 1 tablet): ";
    getline(cin, dosage);

    patient->addReminder(MedicineReminder(name, time, dosage));
    cout << "Reminder added successfully!\n";
}

int main() {
    createDataDirectory();
    UserManager userManager;
    DoctorBot doctorBot;
    User* currentUser = nullptr;

    userManager.loadUsers();
    userManager.loadAllUsers();

    while (true) {
        showMainMenu();
        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore();

        if (choice == 1) { // Login
            string username, password, userType;
            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);

            if (userManager.login(username, password, userType)) {
                if (userType == "patient") {
                    for (auto& patient : userManager.getPatients()) {
                        if (patient->getUsername() == username) {
                            currentUser = patient.get();
                            break;
                        }
                    }
                }
                else if (userType == "doctor") {
                    for (auto& doctor : userManager.getDoctors()) {
                        if (doctor->getUsername() == username) {
                            currentUser = doctor.get();
                            break;
                        }
                    }
                }

                if (!currentUser) {
                    cout << "User data not found. Please contact administrator.\n";
                    continue;
                }

                cout << "\nWelcome " << currentUser->getName() << "!\n";

                while (true) {
                    currentUser->displayMenu();
                    cin >> choice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid input. Please enter a number.\n";
                        continue;
                    }
                    cin.ignore();

                    if (auto* patient = dynamic_cast<Patient*>(currentUser)) {
                        switch (choice) {
                        case 1: addHealthRecord(patient, doctorBot); break;
                        case 2: patient->viewRecords(); break;
                        case 3: addMedicineReminder(patient); break;
                        case 4: patient->viewReminders(); break;
                        case 5: chatWithDoctorBot(doctorBot); break;
                        case 6: patient->viewProfile(); break;
                        case 7:
                            patient->saveToFile();
                            currentUser = nullptr;
                            cout << "Logged out successfully.\n";
                            break;
                        default: cout << "Invalid choice.\n";
                        }
                        if (choice == 7) break;
                    }
                    else if (auto* doctor = dynamic_cast<Doctor*>(currentUser)) {
                        switch (choice) {
                        case 1: doctor->viewPatientRecords(userManager.getPatients()); break;
                        case 2: doctor->viewProfile(); break;
                        case 3:
                            currentUser = nullptr;
                            cout << "Logged out successfully.\n";
                            break;
                        default: cout << "Invalid choice.\n";
                        }
                        if (choice == 3) break;
                    }
                }
            }
            else {
                cout << "Login failed! Invalid username or password.\n";
            }
        }
        else if (choice == 2) { // Register
            string username, password, name, userType;
            int age;

            cout << "Username: ";
            getline(cin, username);

            if (username.empty()) {
                cout << "Username cannot be empty.\n";
                continue;
            }

            cout << "Password: ";
            getline(cin, password);

            if (password.empty()) {
                cout << "Password cannot be empty.\n";
                continue;
            }

            cout << "Register as (patient/doctor): ";
            getline(cin, userType);

            if (userType != "patient" && userType != "doctor") {
                cout << "Invalid user type. Please enter 'patient' or 'doctor'.\n";
                continue;
            }

            cout << "Full Name: ";
            getline(cin, name);

            cout << "Age: ";
            while (!(cin >> age) || age <= 0) {
                cout << "Invalid age. Please enter a positive number: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin.ignore();

            if (userManager.registerUser(username, password, name, age, userType)) {
                cout << "Registration successful! You can now login.\n";
            }
            else {
                cout << "Username already exists! Please choose another username.\n";
            }
        }
        else if (choice == 3) { // Exit
            break;
        }
        else {
            cout << "Invalid choice. Please select 1-3.\n";
        }
    }

    userManager.saveUsers();
    cout << "Goodbye! Thanks for using Health Tracker.\n";
    return 0;
}