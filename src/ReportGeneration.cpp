#include "../include/ReportGeneration.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Patient {
    string id, name, gender, severity, admission, discharge, history, locality, insurance, paymentStatus;
    int age, priority;
    double billAmount, amountPaid, outstanding;
};

// Safe conversion function for `stoi`
int safeStoi(const string& str) {
    try {
        return stoi(str);
    } catch (const std::invalid_argument& e) {
        return 0; // Return a default value (0) if the conversion fails
    }
}

// Safe conversion function for `stod`
double safeStod(const string& str) {
    try {
        return stod(str);
    } catch (const std::invalid_argument& e) {
        return 0.0; // Return a default value (0.0) if the conversion fails
    }
}

// Helper function to trim spaces and quotes around a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\"");
    size_t last = str.find_last_not_of(" \t\"");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

void ReportGeneration::generateDailyReport(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header

    vector<Patient> patients;
    map<string, int> diseaseCounts;
    map<string, int> localityCounts;
    map<string, int> severityCounts = { {"High", 0}, {"Medium", 0}, {"Low", 0} };
    map<string, int> genderCounts = { {"M", 0}, {"F", 0} };
    map<string, int> ageGroups = { {"0-18", 0}, {"19-40", 0}, {"41-60", 0}, {"61+", 0} };
    double totalBill = 0, maxBill = 0, minBill = 1e9;
    int emergencyCases = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Patient p;

        getline(ss, p.id, ',');
        getline(ss, p.name, ',');
        getline(ss, token, ','); p.age = safeStoi(token);
        getline(ss, p.gender, ','); genderCounts[p.gender]++;
        getline(ss, p.severity, ','); severityCounts[p.severity]++;
        getline(ss, p.admission, ',');
        getline(ss, p.discharge, ',');
        getline(ss, p.history, ',');
        getline(ss, token, ','); p.billAmount = safeStod(token); totalBill += p.billAmount;
        getline(ss, token, ','); p.priority = safeStoi(token);
        getline(ss, p.locality, ','); localityCounts[p.locality]++;
        getline(ss, p.insurance, ',');
        getline(ss, token, ','); p.amountPaid = safeStod(token);
        getline(ss, token, ','); p.outstanding = safeStod(token);
        getline(ss, p.paymentStatus, ',');

        if (p.priority == 5 || p.severity == "High" || p.discharge.empty()) {
            emergencyCases++;
        }

        // Age group count
        if (p.age <= 18) ageGroups["0-18"]++;
        else if (p.age <= 40) ageGroups["19-40"]++;
        else if (p.age <= 60) ageGroups["41-60"]++;
        else ageGroups["61+"]++;

        // Disease count (Avoid duplicates by using a set)
        stringstream diseaseStream(p.history);
        set<string> uniqueDiseases; // Set to avoid duplicates
        string disease;
        while (getline(diseaseStream, disease, ',')) { // Split by commas
            disease = trim(disease); // Trim spaces and quotes around disease names
            if (!disease.empty()) {
                uniqueDiseases.insert(disease); // Insert only unique diseases
            }
        }

        // Add unique diseases to the map
        for (const auto& uniqueDisease : uniqueDiseases) {
            diseaseCounts[uniqueDisease]++;
        }

        if (p.billAmount > maxBill) maxBill = p.billAmount;
        if (p.billAmount < minBill && p.billAmount > 0) minBill = p.billAmount;

        patients.push_back(p);
    }
    file.close();

    // Output Report
    cout << "\nDaily Hospital Report\n";
    cout << "\nPatient Summary";
    cout << "\nTotal Patients Registered: " << patients.size();
    cout << "\nEmergency Cases Handled Today: " << emergencyCases;
    cout << "\nAverage Billing Amount: ₹" << fixed << setprecision(2) << (totalBill / patients.size());
    cout << "\n\n Financial Overview";
    cout << "\nTotal Revenue Today: ₹" << fixed << setprecision(2) << totalBill;
    cout << "\nHighest Bill Generated: ₹" << maxBill;
    cout << "\nLowest Bill Generated: ₹" << minBill;
    cout << "\n\n Patient Demographics Overview\nAge Groups:\n";
    for (const auto& group : ageGroups) {
        cout << group.first << ": " << group.second << "\n";
    }
    cout << "\nDisease Trends:\n";
    for (const auto& disease : diseaseCounts) {
        cout << disease.first << ": " << disease.second << "\n";
    }

    cout << "\n Upcoming Appointments/Surgeries (Assuming appointments are integrated)\n";
    cout << "No upcoming surgeries found.\n";
}
