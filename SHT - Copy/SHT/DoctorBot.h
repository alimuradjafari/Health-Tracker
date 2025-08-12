#ifndef DOCTORBOT_H
#define DOCTORBOT_H

#include <string>
#include <vector>
using namespace std;

class DoctorBot {
public:
    string respondToMessage(const string& message);
    string analyzeSymptoms(const vector<string>& symptoms);
};

#endif