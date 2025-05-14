#include "../include/PatientRegistration.h"
#include "../include/EmergencyHandling.h"
#include <iostream>

int main() {
    int choice;
    while (true) {
        std::cout << "\n=== Hospital Management System ===\n";
        std::cout << "1. Register a new patient\n";
        std::cout << "2. Load Emergency Cases\n";
        std::cout << "3. Process Emergency Case\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                PatientRegistration::registerPatient();
                break;
            case 2:
                EmergencyHandling::loadEmergencyCases();
                break;
            case 3:
                EmergencyHandling::processEmergencyCase();
                break;
            case 4:
                std::cout << "Exiting program...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}
