#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Patient.h"
#include "Doctor.h"
using namespace std;

class UserManager {
private:
    unordered_map<string, pair<string, string>> userDatabase; // username -> (password, type)
    vector<unique_ptr<Patient>> patients;
    vector<unique_ptr<Doctor>> doctors;

public:
    bool registerUser(const string& username, const string& password,const string& name, int age, const string& userType);
    bool login(const string& username, const string& password,string& out_userType);
    void saveUsers() const;
    void loadUsers();
    void loadAllUsers();

    const vector<unique_ptr<Patient>>& getPatients() const { return patients; }
    const vector<unique_ptr<Doctor>>& getDoctors() const { return doctors; }
};

#endif