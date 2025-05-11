#include <iostream>
#include <limits>  // For input validation
#include "PatientRegistration.h"
#include "EmergencyHandling.h"
#include "MedicalHistory.h"
#include "BillingSystem.h"
#include "ReportGeneration.h"
#include "MLIntegration.h"

using namespace std;

// Function to clear the input buffer in case of invalid input
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to display the main menu
void displayMainMenu() {
    cout << "\n========== Hospital Management System ==========\n";
    cout << "1. Register New Patient\n";
    cout << "2. Handle Emergency Case\n";
    cout << "3. View Medical History\n";
    cout << "4. Manage Billing\n";
    cout << "5. Generate Reports\n";
    cout << "6. Run ML Prediction (Disease & Revisit)\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

// Function to run the system with the menu loop
void runSystem() {
    int choice;

    do {
        displayMainMenu();

        // Input validation for user choice
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            clearInputBuffer();
        }
        clearInputBuffer(); // Clear any extra input from the buffer

        switch (choice) {
            case 1:
                registerPatient(); // Call function to register a new patient
                break;
            case 2:
                handleEmergency(); // Call function to handle an emergency case
                break;
            case 3:
                viewMedicalHistory(); // Call function to view medical history
                break;
            case 4:
                manageBilling(); // Call function to manage billing
                break;
            case 5:
                generateReport(); // Call function to generate reports
                break;
            case 6:
                runMLPrediction(); // Call function for ML predictions (Disease & Revisit)
                break;
            case 0:
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0); // Continue looping until the user chooses to exit
}

int main() {
    runSystem(); // Start the system
    return 0;
}
