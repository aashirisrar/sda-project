#include "AttendanceSystem.h"

AttendanceSystem::AttendanceSystem() {
    loadFromFile();
}

AttendanceSystem::~AttendanceSystem() {
    saveToFile();
}

void AttendanceSystem::loadFromFile() {
    std::ifstream file("employees.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, id;
        int hours, casual, earned;

        if (iss >> name >> id >> hours >> casual >> earned) {
            Employee emp(name, id);
            emp.total_hours = hours;
            emp.casual_leaves = casual;
            emp.earned_leaves = earned;
            employees.push_back(emp);
        }
    }
    file.close();
}

void AttendanceSystem::saveToFile() {
    std::ofstream file("employees.txt", std::ios::trunc);
    for (const auto& emp : employees) {
        file << emp.name << " " << emp.id << " " << emp.total_hours << " "
             << emp.casual_leaves << " " << emp.earned_leaves << "\n";
    }
    file.close();
}

void AttendanceSystem::addEmployee(const std::string& name, const std::string& id) {
    employees.emplace_back(name, id);
    saveToFile();
}

void AttendanceSystem::markAttendance(const std::string& id, int hours) {
    Employee* emp = findEmployee(id);
    if (emp) {
        emp->total_hours += hours;
    } 
}

Employee* AttendanceSystem::findEmployee(const std::string& id) {
    for (auto& emp : employees) {
        if (emp.id == id) return &emp;
    }
    return nullptr;
}

void AttendanceSystem::processLeaveApplication(const std::string& id, Leave& leave, const std::string& approver, bool approve) {
    Employee* emp = findEmployee(id);
    if (emp) {
        leave.status = approve ? "Approved" : "Rejected";
        leave.date_of_approval = __DATE__;
        emp->leave_history.push_back(leave);
    }
}

void AttendanceSystem::showLowAttendance(float minPercentage) {
    for (const auto& emp : employees) {
        float attendancePercentage = (emp.total_hours / 40.0f) * 100;
        if (attendancePercentage < minPercentage) {
            std::cout << "Employee ID: " << emp.id << ", Name: " << emp.name << ", Attendance: " << attendancePercentage << "%\n";
        }
    }
}

void AttendanceSystem::showPendingLeaves() {
    for (const auto& emp : employees) {
        for (const auto& leave : emp.leave_history) {
            if (leave.status == "Pending") {
                std::cout << "Employee ID: " << emp.id << ", Name: " << emp.name
                          << ", Leave Type: " << leave.type << ", Reason: " << leave.reason << "\n";
            }
        }
    }
}

void AttendanceSystem::showEmployeeAttendance(const std::string& id) {
    Employee* emp = findEmployee(id);
    if (emp) {
        std::cout << "Employee ID: " << emp->id << ", Name: " << emp->name << ", Total Hours: " << emp->total_hours << "\n";
    }
}

void AttendanceSystem::showEmployeeLeaves(const std::string& id) {
    Employee* emp = findEmployee(id);
    if (emp) {
        std::cout << "Employee ID: " << emp->id << ", Name: " << emp->name << "\n";
        for (const auto& leave : emp->leave_history) {
            std::cout << "Leave Type: " << leave.type << ", From: " << leave.from_date
                      << ", To: " << leave.to_date << ", Status: " << leave.status << "\n";
        }
    }
}
