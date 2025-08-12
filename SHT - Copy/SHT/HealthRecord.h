#ifndef HEALTHRECORD_H
#define HEALTHRECORD_H

#include <string>
#include <vector>
using namespace std;

class HealthRecord {
private:
    string date;
    double temperature;
    vector<string> symptoms;

public:
    HealthRecord(const string& d, double temp, const vector<string>& symps);

    void display() const;
    string getDate() const { return date; }
    double getTemp() const { return temperature; }
    const vector<string>& getSymptoms() const { return symptoms; }
};

#endif