#include "HealthRecord.h"
#include <iostream>

HealthRecord::HealthRecord(const string& d, double temp,const vector<string>& symps): date(d), temperature(temp), symptoms(symps) {}

void HealthRecord::display() const {
    cout << "\nDate: " << date;
    cout << "\nTemp: " << temperature << "C"<<endl;

    cout<<"Symptoms: ";
    for (const auto& s : symptoms) {
        cout << s << ", ";
    }
    cout << "\n";
}