#include "../include/PatientRegistration.h"
#include <iostream>
#include <fstream>
#include <string>

void PatientRegistration::registerPatient() {
    std::ofstream file("../data/patients.csv", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open patients.csv in data folder.\n";
        return;
    }

    std::string patientID, name, gender, conditionSeverity, admissionDate, dischargeDate, medicalHistory;
    std::string locality, insuranceCoverage, paymentStatus;
    int age, priorityLevel;
    double billAmount, amountPaid, outstandingAmount;

    std::cout << "Enter Patient ID: ";
    std::cin >> patientID;
    std::cout << "Enter Patient Name: ";
    std::cin.ignore(); std::getline(std::cin, name);
    std::cout << "Enter Age: ";
    std::cin >> age;
    std::cout << "Enter Gender (M/F): ";
    std::cin >> gender;
    std::cout << "Enter Condition Severity (High/Medium/Low): ";
    std::cin >> conditionSeverity;
    std::cout << "Enter Admission Date (MM/DD/YYYY): ";
    std::cin >> admissionDate;
    std::cout << "Enter Discharge Date (MM/DD/YYYY or - if not discharged): ";
    std::cin >> dischargeDate;
    std::cin.ignore();
    std::cout << "Enter Medical History: ";
    std::getline(std::cin, medicalHistory);
    std::cout << "Enter Bill Amount: ";
    std::cin >> billAmount;
    std::cout << "Enter Priority Level (1-5): ";
    std::cin >> priorityLevel;
    std::cout << "Enter Locality: ";
    std::cin.ignore(); std::getline(std::cin, locality);
    std::cout << "Enter Insurance Coverage (Yes/No): ";
    std::cin >> insuranceCoverage;
    std::cout << "Enter Amount Paid: ";
    std::cin >> amountPaid;
    std::cout << "Enter Payment Status (Paid/Unpaid): ";
    std::cin >> paymentStatus;

    outstandingAmount = billAmount - amountPaid;

    file << patientID << "\t" << name << "\t" << age << "\t" << gender << "\t"
         << conditionSeverity << "\t" << admissionDate << "\t" << dischargeDate << "\t"
         << medicalHistory << "\t" << billAmount << "\t" << priorityLevel << "\t"
         << locality << "\t" << insuranceCoverage << "\t" << amountPaid << "\t"
         << outstandingAmount << "\t" << paymentStatus << "\n";

    file.close();
    std::cout << " Patient registered successfully!\n";
}
