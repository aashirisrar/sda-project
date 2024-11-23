#ifndef ATTENDANCESYSTEM_H
#define ATTENDANCESYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// Define structures for Leave and Employee
struct Leave {
    std::string type;
    std::string from_date;
    std::string to_date;
    std::string reason;
    std::string status;
    std::string date_of_application;
    std::string date_of_approval;
};

struct Employee {
    std::string name;
    std::string id;
    int total_hours;
    int casual_leaves;
    int earned_leaves;
    std::vector<Leave> leave_history; // Stores leave history for each employee

    Employee(const std::string& name, const std::string& id)
        : name(name), id(id), total_hours(0), casual_leaves(15), earned_leaves(21) {}
};

// Define the AttendanceSystem class
class AttendanceSystem {
private:
    std::vector<Employee> employees; // Stores all employee records

    // Helper methods to handle file operations
    void loadFromFile();
    void saveToFile();
    void saveAttendanceToFile(const std::string& id, int hours);
    void saveLeaveToFile(const std::string& id, const Leave& leave);

public:
    AttendanceSystem() { loadFromFile(); } // Constructor loads data from file
    ~AttendanceSystem() { saveToFile(); }  // Destructor saves data to file

    // Core functionality
    void addEmployee(const std::string& name, const std::string& id);
    void markAttendance(const std::string& id, int hours);
    Employee* findEmployee(const std::string& id);
    void processLeaveApplication(const std::string& id, Leave& leave, const std::string& approver, bool approve);
    void showLowAttendance(float minPercentage);
    void showPendingLeaves();
    void showEmployeeAttendance(const std::string& id);
    void showEmployeeLeaves(const std::string& id);
};

#endif // ATTENDANCESYSTEM_H
