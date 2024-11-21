#ifndef ATTENDANCE_SYSTEM_H
#define ATTENDANCE_SYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

struct Leave {
    string type; // Casual, Earned, Official, Unpaid
    string from_date;
    string to_date;
    string reason;
    string status; // Pending, Approved, Rejected
    string application_date;
    string approval_date;
};

class Employee {
public:
    string name;
    string id;
    int casual_leave_balance = 15;
    int earned_leave_balance = 21;
    int attendance_hours = 0; // Total attendance hours
    vector<Leave> leave_history;

    Employee(string n, string i);
    void markAttendance(int hours);
    void applyLeave(const Leave& leave);
    void updateLeaveBalance(const string& type, int days);

    void saveToFile();
    static Employee loadFromFile(const string& id);
};

class AttendanceSystem {
public:
    vector<Employee> employees;

    void addEmployee(const string& name, const string& id);
    void markAttendance(const string& id, int hours);
    void processLeaveApplication(const string& id, Leave& leave, const string& approver, bool approve);

    void showLowAttendance(float percentage);
    void showPendingLeaves();
    void showEmployeeAttendance(const string& id);
    void showEmployeeLeaves(const string& id);
    Employee* findEmployee(const string& id);

};

#endif
