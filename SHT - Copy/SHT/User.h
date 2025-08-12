#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

//base class
class User {
protected:
    string username;
    string name;
    int age;

public:
    User(const string& u, const string& n, int a);
    virtual ~User() = default;

    //pure virtual functions (abstraction)
    virtual void displayMenu() const = 0;
    virtual void saveToFile() const = 0;
    virtual void loadFromFile() = 0;

    virtual void viewProfile() const;
    // Getters
    string getUsername() const { return username; }
    string getName() const { return name; }
    int getAge() const { return age; }
};

#endif