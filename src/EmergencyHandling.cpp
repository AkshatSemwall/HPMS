#include "../include/EmergencyHandling.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>

std::priority_queue<EmergencyCase> EmergencyHandling::emergencyQueue;
std::vector<std::string> EmergencyHandling::processedIDs;

void EmergencyHandling::loadEmergencyCases() {
    std::ifstream file("../data/patients.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open patients.csv in data folder.\n";
        return;
    }

    emergencyQueue = std::priority_queue<EmergencyCase>(); // Clear previous data
    std::unordered_set<std::string> processedSet(processedIDs.begin(), processedIDs.end());

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<std::string> tokens;
        std::string token;

        while (std::getline(ss, token, '\t')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 15) continue;

        std::string patientID = tokens[0];
        std::string name = tokens[1];
        std::string severity = tokens[4];
        std::string dischargeDate = tokens[6];
        int priority = std::stoi(tokens[9]);

        if (severity == "High" && priority == 5 && (dischargeDate == "-" || dischargeDate.empty()) && !processedSet.count(patientID)) {
            emergencyQueue.push({patientID, name, priority});
            std::cout << "• ID: " << patientID << ", Name: " << name << ", Priority: " << priority << "\n";
        }
    }

    file.close();
    if (emergencyQueue.empty()) {
        std::cout << "No active emergency cases to process.\n";
    } else {
        std::cout << "Emergency cases loaded.\n";
    }
}

void EmergencyHandling::processEmergencyCase() {
    if (emergencyQueue.empty()) {
        std::cout << "No active emergency cases to process.\n";
        return;
    }

    EmergencyCase ec = emergencyQueue.top();
    emergencyQueue.pop();
    processedIDs.push_back(ec.patientID);

    std::cout << "Processing emergency case:\n";
    std::cout << "ID: " << ec.patientID << ", Name: " << ec.name << ", Priority: " << ec.priority << "\n";
}
