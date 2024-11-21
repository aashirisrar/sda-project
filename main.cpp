#include "AttendanceSystem.h"
#include <iostream>

void displayMenu() {
    std::cout << "\n--- Attendance and Leave Management System ---\n";
    std::cout << "1. Add Employee\n";
    std::cout << "2. Mark Attendance\n";
    std::cout << "3. Apply for Leave\n";
    std::cout << "4. Show Low Attendance Employees\n";
    std::cout << "5. Show Pending Leave Applications\n";
    std::cout << "6. Show Employee Attendance\n";
    std::cout << "7. Show Employee Leaves\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    AttendanceSystem system;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear input buffer

        switch (choice) {
        case 1: {
            std::string name, id;
            std::cout << "Enter Employee Name: ";
            std::getline(std::cin, name);
            std::cout << "Enter Employee ID: ";
            std::getline(std::cin, id);
            system.addEmployee(name, id);
            std::cout << "Employee added successfully!\n";
            break;
        }
        case 2: {
            std::string id;
            int hours;
            std::cout << "Enter Employee ID: ";
            std::getline(std::cin, id);
            if(!system.findEmployee(id)) {
                std::cout<<"Error! No Employee found with this ID!\n";
                break;
            }
            std::cout << "Enter Hours Worked: ";
            std::cin >> hours;
            system.markAttendance(id, hours);
            std::cout << "Attendance marked successfully!\n";
            break;
        }
        case 3: {
            std::string id, type, from_date, to_date, reason;
            std::cout << "Enter Employee ID: ";
            std::getline(std::cin, id);
            std::cout << "Enter Leave Type (Casual/Earned/Official/Unpaid): ";
            std::getline(std::cin, type);
            std::cout << "Enter From Date (DD-MM-YYYY): ";
            std::getline(std::cin, from_date);
            std::cout << "Enter To Date (DD-MM-YYYY): ";
            std::getline(std::cin, to_date);
            std::cout << "Enter Reason for Leave: ";
            std::getline(std::cin, reason);

            Leave leave = {type, from_date, to_date, reason, "Pending", __DATE__, ""};
            system.processLeaveApplication(id, leave, "Supervisor", false);
            std::cout << "Leave application submitted successfully!\n";
            break;
        }
        case 4: {
            float minPercentage;
            std::cout << "Enter Minimum Attendance Percentage: ";
            std::cin >> minPercentage;
            system.showLowAttendance(minPercentage);
            break;
        }
        case 5: {
            system.showPendingLeaves();
            break;
        }
        case 6: {
            std::string id;
            std::cout << "Enter Employee ID: ";
            std::getline(std::cin, id);
            system.showEmployeeAttendance(id);
            break;
        }
        case 7: {
            std::string id;
            std::cout << "Enter Employee ID: ";
            std::getline(std::cin, id);
            system.showEmployeeLeaves(id);
            break;
        }
        case 0:
            std::cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
