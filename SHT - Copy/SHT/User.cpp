#include "User.h"

User::User(const string& u, const string& n, int a)
    : username(u), name(n), age(a) {
}

void User::viewProfile() const {
    cout << "\nUsername: " << username
        << "\nName: " << name
        << "\nAge: " << age << endl;
}