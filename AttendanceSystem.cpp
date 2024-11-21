#include "AttendanceSystem.h"

Employee::Employee(string n, string i) : name(n), id(i) {}

void Employee::markAttendance(int hours) {
    attendance_hours += hours;
    saveToFile();
}

void Employee::applyLeave(const Leave& leave) {
    leave_history.push_back(leave);
    saveToFile();
}

void Employee::updateLeaveBalance(const string& type, int days) {
    if (type == "Casual") casual_leave_balance -= days;
    else if (type == "Earned") earned_leave_balance -= days;
    saveToFile();
}

void Employee::saveToFile() {
    ofstream file("Employee_" + id + ".txt");
    if (file) {
        file << name << '\n' << id << '\n';
        file << attendance_hours << '\n';
        file << casual_leave_balance << '\n' << earned_leave_balance << '\n';

        file << leave_history.size() << '\n';
        for (const auto& leave : leave_history) {
            file << leave.type << '\n' << leave.from_date << '\n'
                 << leave.to_date << '\n' << leave.reason << '\n'
                 << leave.status << '\n' << leave.application_date << '\n'
                 << leave.approval_date << '\n';
        }
        file.close();
    }
}

Employee Employee::loadFromFile(const string& id) {
    ifstream file("Employee_" + id + ".txt");
    if (!file) throw runtime_error("Employee not found!");

    string name, emp_id;
    int attendance, casual, earned, leave_count;

    file >> name >> emp_id;
    file >> attendance >> casual >> earned >> leave_count;

    Employee emp(name, emp_id);
    emp.attendance_hours = attendance;
    emp.casual_leave_balance = casual;
    emp.earned_leave_balance = earned;

    for (int i = 0; i < leave_count; ++i) {
        Leave leave;
        file >> leave.type >> leave.from_date >> leave.to_date;
        file >> leave.reason >> leave.status;
        file >> leave.application_date >> leave.approval_date;
        emp.leave_history.push_back(leave);
    }

    return emp;
}

void AttendanceSystem::addEmployee(const string& name, const string& id) {
    employees.emplace_back(name, id);
    employees.back().saveToFile();
}

void AttendanceSystem::markAttendance(const string& id, int hours) {
    Employee* emp = findEmployee(id);
    if (emp) emp->markAttendance(hours);
}

void AttendanceSystem::processLeaveApplication(const string& id, Leave& leave, const string& approver, bool approve) {
    Employee* emp = findEmployee(id);
    if (!emp) return;

    leave.status = approve ? "Approved" : "Rejected";
    leave.approval_date = __DATE__;

    emp->applyLeave(leave);
    if (approve && (leave.type == "Casual" || leave.type == "Earned")) {
        int days = stoi(leave.to_date.substr(0, 2)) - stoi(leave.from_date.substr(0, 2)) + 1;
        emp->updateLeaveBalance(leave.type, days);
    }
}

void AttendanceSystem::showLowAttendance(float percentage) {
    for (const auto& emp : employees) {
        float actual = (emp.attendance_hours / (40.0 * 4)) * 100;
        if (actual < percentage) {
            cout << "Employee: " << emp.name << " (" << emp.id << "), Attendance: " << actual << "%\n";
        }
    }
}

void AttendanceSystem::showPendingLeaves() {
    for (const auto& emp : employees) {
        for (const auto& leave : emp.leave_history) {
            if (leave.status == "Pending") {
                cout << "Employee: " << emp.name << " (" << emp.id << "), Leave Type: " << leave.type << ", From: "
                     << leave.from_date << ", To: " << leave.to_date << ", Reason: " << leave.reason << '\n';
            }
        }
    }
}

void AttendanceSystem::showEmployeeAttendance(const string& id) {
    Employee* emp = findEmployee(id);
    if (emp) {
        cout << "Attendance for " << emp->name << ": " << emp->attendance_hours << " hours\n";
    }
}

void AttendanceSystem::showEmployeeLeaves(const string& id) {
    Employee* emp = findEmployee(id);
    if (emp) {
        cout << "Leave Balance: Casual: " << emp->casual_leave_balance << ", Earned: " << emp->earned_leave_balance << '\n';
        for (const auto& leave : emp->leave_history) {
            cout << "Leave: " << leave.type << ", From: " << leave.from_date << ", To: " << leave.to_date
                 << ", Status: " << leave.status << '\n';
        }
    }
}

Employee* AttendanceSystem::findEmployee(const string& id) {
    for (auto& emp : employees) {
        if (emp.id == id) return &emp;
    }
    return nullptr;
}
