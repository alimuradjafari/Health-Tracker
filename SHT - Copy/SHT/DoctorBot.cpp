#include "DoctorBot.h"
#include <algorithm>

string DoctorBot::respondToMessage(const string& message) {
    string userMsg = message;
    transform(userMsg.begin(), userMsg.end(), userMsg.begin(), ::tolower);

    if (userMsg.find("hello") != string::npos || userMsg.find("hi") != string::npos) {
        return "Hello! How can I help you?";
    }
    else if (userMsg.find("fever") != string::npos) {
        return "For fever, I recommend rest and drinking plenty of fluids.\nYou can take paracetamol if needed.";
    }
    else if (userMsg.find("headache") != string::npos) {
        return "Headaches can be caused by dehydration or stress.\nTry drinking water and resting in a quiet place.";
    }
    else if (userMsg.find("cold") != string::npos) {
        return "Cold is a common disease. focus on self-care but If symptoms worsen or persist, go to doctor.";
    }
    else if (userMsg.find("breath") != string::npos) {
        return "Seek immediate medical attention if you have severe breathing problems.";
    }
    else if (userMsg.find("medicine") != string::npos) {
        return "You can add medicine reminders through the main menu.\nWould you like me to guide you through that?";
    }
    else if (userMsg.find("yes") !=string ::npos) {
            return "When you Login here is: \n3 for Add Medicine Reminder and 4 for View Medicine Reminders";
    }
    else if (userMsg.find("advice") != string::npos) {
        return "To improve your health here are some General Advice:\n- Eat a Healthy Diet\n- Be Physically Active\n- Get Enough Sleep\n- Manage  Your Stress";
    }
    else {
        return "I'm here to help with your health concerns. "
            "Could you tell me more about your symptoms?";
    }
}

string DoctorBot::analyzeSymptoms(const vector<string>& symptoms) {
    string analysis;
    for (const auto& symptom : symptoms) {
        string lower = symptom;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        if (lower.find("fever") != string::npos) {
            analysis += "You have fever. ";
        }
        if (lower.find("cough") != string::npos) {
            analysis += "You have cough. ";
        }
    }
    return analysis.empty() ? "Your symptoms seem mild." : analysis;
}