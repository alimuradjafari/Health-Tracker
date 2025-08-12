#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

void UserManager::loadUsers() {
    try {
        ifstream file("data/users.txt");
        if (!file) {
            return; 
        }
        
        string line;
        while (getline(file, line)) {
            istringstream ss(line);
            string username, password, userType;
            if (getline(ss, username, ',') && 
                getline(ss, password, ',') &&
                getline(ss, userType)) {
                userDatabase[username] = make_pair(password, userType);
            }
        }
    } catch (const exception& e) {
        cerr << "Error loading users: " << e.what() << endl;
    }
}

void UserManager::loadAllUsers() {
    for (const auto& pair : userDatabase) {
        const string& username = pair.first;
        const auto& data = pair.second;
        const string& password = data.first;
        const string& userType = data.second;

        if (userType == "patient") {
            auto patient = make_unique<Patient>(username, "", 0);
            patient->loadFromFile();
            patients.push_back(move(patient));
        }
        else if (userType == "doctor") {
            auto doctor = make_unique<Doctor>(username, "", 0);
            doctor->loadFromFile();
            doctors.push_back(move(doctor));
        }
    }
}


void UserManager::saveUsers() const {
    try {
        ofstream file("data/users.txt");
        if (!file) {
            throw runtime_error("Failed to open users file for writing");
        }

        for (const auto& pair : userDatabase) {
            const string& username = pair.first;
            const auto& data = pair.second;
            const string& password = data.first;
            const string& userType = data.second;

            file << username << "," << password << "," << userType << "\n";
        }
    }
    catch (const exception& e) {
        cerr << "Error saving users: " << e.what() << endl;
    }
}


bool UserManager::registerUser(const string& username, const string& password, 
                              const string& name, int age, const string& userType) {
    if (userDatabase.find(username) != userDatabase.end()) {
        return false;
    }
    
    userDatabase[username] = make_pair(password, userType);
    
    if (userType == "patient") {
        auto patient = make_unique<Patient>(username, name, age);
        patient->saveToFile();
        patients.push_back(move(patient));
    } else if (userType == "doctor") {
        auto doctor = make_unique<Doctor>(username, name, age);
        doctor->saveToFile();
        doctors.push_back(move(doctor));
    }
    
    saveUsers();
    return true;
}

bool UserManager::login(const string& username, const string& password,
    string& out_userType) {
    auto it = userDatabase.find(username);
    if (it == userDatabase.end()) {
        return false;
    }

    const string& storedPassword = it->second.first;
    const string& userType = it->second.second;

    if (storedPassword != password) {
        return false;
    }

    out_userType = userType;
    return true;
}
