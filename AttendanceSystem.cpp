#include "AttendanceSystem.h"

// Load employee data from file
void AttendanceSystem::loadFromFile() {
    std::ifstream file("employees.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, id;
        int hours, casual, earned;

        if (iss >> id >> name >> hours >> casual >> earned) {
            Employee emp(name, id);
            emp.total_hours = hours;
            emp.casual_leaves = casual;
            emp.earned_leaves = earned;
            employees.push_back(emp);
        }
    }
    file.close();
}

// Save employee data to file
void AttendanceSystem::saveToFile() {
    std::ofstream file("employees.txt", std::ios::trunc);
    for (const auto& emp : employees) {
        file << emp.id << " " << emp.name << " " << emp.total_hours << " "
             << emp.casual_leaves << " " << emp.earned_leaves << "\n";
    }
    file.close();
}

// Save attendance data to a file
void AttendanceSystem::saveAttendanceToFile(const std::string& id, int hours) {
    std::ofstream file("attendance.txt", std::ios::app);
    if (file.is_open()) {
        file << id << " " << hours << "\n";
    }
    file.close();
}

// Save leave data to a file
void AttendanceSystem::saveLeaveToFile(const std::string& id, const Leave& leave) {
    std::ofstream file("leaves.txt", std::ios::app);
    if (file.is_open()) {
        file << id << "," << leave.type << "," << leave.from_date << "," << leave.to_date
             << "," << leave.reason << "," << leave.status << "," << leave.date_of_application
             << "," << leave.date_of_approval << "\n";
    }
    file.close();
}

// Add a new employee
void AttendanceSystem::addEmployee(const std::string& name, const std::string& id) {
    employees.emplace_back(name, id);
    saveToFile();
}

// Mark attendance
void AttendanceSystem::markAttendance(const std::string& id, int hours) {
    Employee* emp = findEmployee(id);
    if (emp) {
        emp->total_hours += hours;
        saveAttendanceToFile(id, hours); // Save to attendance file
        saveToFile(); // Update employee total hours
    } else {
        std::cout << "Error: Employee ID not found.\n";
    }
}

// Find an employee
Employee* AttendanceSystem::findEmployee(const std::string& id) {
    for (auto& emp : employees) {
        if (emp.id == id) {
            return &emp;
        }
    }
    return nullptr;
}

// Process leave application
void AttendanceSystem::processLeaveApplication(const std::string& id, Leave& leave, const std::string& approver, bool approve) {
    Employee* emp = findEmployee(id);
    if (emp) {
        leave.status = approve ? "Approved" : "Rejected";
        leave.date_of_approval = __DATE__;
        emp->leave_history.push_back(leave); // Add leave to employee history
        saveLeaveToFile(id, leave);         // Save leave to file
    } else {
        std::cout << "Error: Employee ID not found.\n";
    }
}

// Show employees with low attendance
void AttendanceSystem::showLowAttendance(float minPercentage) {
    for (const auto& emp : employees) {
        float attendancePercentage = (emp.total_hours / (40.0f * 4)) * 100;
        if (attendancePercentage < minPercentage) {
            std::cout << "Employee ID: " << emp.id << ", Name: " << emp.name << ", Attendance: " << attendancePercentage << "%\n";
        }
    }
}

// Show pending leave applications
void AttendanceSystem::showPendingLeaves() {
    std::ifstream file("leaves.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, type, from_date, to_date, reason, status, date_of_application, date_of_approval;
        std::getline(iss, id, ',');
        std::getline(iss, type, ',');
        std::getline(iss, from_date, ',');
        std::getline(iss, to_date, ',');
        std::getline(iss, reason, ',');
        std::getline(iss, status, ',');
        if (status == "Pending") {
            std::cout << "Employee ID: " << id << ", Leave Type: " << type << ", Reason: " << reason << "\n";
        }
    }
    file.close();
}

// Show attendance for an employee
void AttendanceSystem::showEmployeeAttendance(const std::string& id) {
    std::ifstream file("attendance.txt");
    if (!file.is_open()) return;

    std::string line;
    int totalHours = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string empId;
        int hours;
        iss >> empId >> hours;
        if (empId == id) {
            totalHours += hours;
        }
    }
    file.close();

    Employee* emp = findEmployee(id);
    if (emp) {
        std::cout << "Employee ID: " << emp->id << ", Name: " << emp->name << ", Total Hours: " << totalHours << "\n";
    } else {
        std::cout << "Error: Employee ID not found.\n";
    }
}

// Show leaves for an employee
void AttendanceSystem::showEmployeeLeaves(const std::string& id) {
    std::ifstream file("leaves.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string empId, type, from_date, to_date, reason, status, date_of_application, date_of_approval;
        std::getline(iss, empId, ',');
        if (empId == id) {
            std::getline(iss, type, ',');
            std::getline(iss, from_date, ',');
            std::getline(iss, to_date, ',');
            std::getline(iss, reason, ',');
            std::getline(iss, status, ',');
            std::getline(iss, date_of_application, ',');
            std::getline(iss, date_of_approval, ',');
            std::cout << "Leave Type: " << type << ", From: " << from_date << ", To: " << to_date
                      << ", Status: " << status << ", Reason: " << reason << "\n";
        }
    }
    file.close();
}
