#include "AttendanceSystem.h"

void displayMenu() {
    cout << "\n=== Attendance and Leave Management System ===\n";
    cout << "1. Add Employee\n";
    cout << "2. Mark Attendance\n";
    cout << "3. Apply Leave\n";
    cout << "4. Process Leave Application\n";
    cout << "5. Show Employees with Low Attendance\n";
    cout << "6. Show Pending Leaves\n";
    cout << "7. Show Employee Attendance\n";
    cout << "8. Show Employee Leave Details\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    AttendanceSystem system;
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); // To handle newline characters in the input buffer

        switch (choice) {
            case 1: {
                string name, id;
                cout << "Enter employee name: ";
                getline(cin, name);
                cout << "Enter employee ID: ";
                getline(cin, id);
                system.addEmployee(name, id);
                cout << "Employee added successfully.\n";
                break;
            }

            case 2: {
                string id;
                int hours;
                cout << "Enter employee ID: ";
                getline(cin, id);
                cout << "Enter hours worked: ";
                cin >> hours;
                system.markAttendance(id, hours);
                cout << "Attendance marked successfully.\n";
                break;
            }

            case 3: {
                string id, type, from_date, to_date, reason;
                cout << "Enter employee ID: ";
                getline(cin, id);
                cout << "Enter leave type (Casual/Earned/Official/Unpaid): ";
                getline(cin, type);
                cout << "Enter leave start date (DD-MM-YYYY): ";
                getline(cin, from_date);
                cout << "Enter leave end date (DD-MM-YYYY): ";
                getline(cin, to_date);
                cout << "Enter reason for leave: ";
                getline(cin, reason);

                Leave leave = {type, from_date, to_date, reason, "Pending", __DATE__, ""};
                Employee* emp = system.findEmployee(id);
                if (emp) {
                    emp->applyLeave(leave);
                    cout << "Leave application submitted successfully.\n";
                } else {
                    cout << "Employee not found.\n";
                }
                break;
            }

            case 4: {
                string id, approver;
                bool approve;
                cout << "Enter employee ID: ";
                getline(cin, id);
                cout << "Enter approver name: ";
                getline(cin, approver);
                cout << "Approve leave? (1 for Yes, 0 for No): ";
                cin >> approve;

                Employee* emp = system.findEmployee(id);
                if (emp && !emp->leave_history.empty()) {
                    Leave& leave = emp->leave_history.back(); // Process the most recent leave
                    system.processLeaveApplication(id, leave, approver, approve);
                    cout << (approve ? "Leave approved.\n" : "Leave rejected.\n");
                } else {
                    cout << "Employee or leave application not found.\n";
                }
                break;
            }

            case 5: {
                float percentage;
                cout << "Enter minimum attendance percentage: ";
                cin >> percentage;
                system.showLowAttendance(percentage);
                break;
            }

            case 6: {
                system.showPendingLeaves();
                break;
            }

            case 7: {
                string id;
                cout << "Enter employee ID: ";
                getline(cin, id);
                system.showEmployeeAttendance(id);
                break;
            }

            case 8: {
                string id;
                cout << "Enter employee ID: ";
                getline(cin, id);
                system.showEmployeeLeaves(id);
                break;
            }

            case 0:
                cout << "Exiting the system. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
