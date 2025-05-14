#ifndef EMERGENCY_HANDLING_H
#define EMERGENCY_HANDLING_H

#include <queue>
#include <string>
#include <vector>

struct EmergencyCase {
    std::string patientID;
    std::string name;
    int priority;

    bool operator<(const EmergencyCase& other) const {
        return priority < other.priority;
    }
};

class EmergencyHandling {
public:
    static void loadEmergencyCases();
    static void processEmergencyCase();

private:
    static std::priority_queue<EmergencyCase> emergencyQueue;
    static std::vector<std::string> processedIDs;
};

#endif
