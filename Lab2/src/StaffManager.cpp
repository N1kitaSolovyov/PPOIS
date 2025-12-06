#include "StaffManager.h"
#include <algorithm>
#include <iostream>

StaffManager::StaffManager() : nextEmployeeId(1) {
    roleSalaries = {
        {"waiter", 25000.0}, {"chef", 50000.0},
        {"manager", 60000.0}, {"bartender", 30000.0}
    };
}

StaffManager::~StaffManager() {
    for (auto employee : employees) {
        delete employee;
    }
}

int StaffManager::hireEmployee(const std::string& name, const std::string& role, double salary) {
    int employeeId = nextEmployeeId++;

    if (role == "waiter") {
        employees.push_back(new Waiter(employeeId, name, salary));
    }
    else if (role == "chef") {
        employees.push_back(new Chef(employeeId, name, salary, "general"));
    }
    else {
        // Используем базовый класс Employee
        employees.push_back(new Employee(employeeId, name, role, salary));
    }

    std::cout << "Hired new " << role << ": " << name << " (ID: " << employeeId << ")" << std::endl;
    return employeeId;
}

bool StaffManager::terminateEmployee(int employeeId) {
    auto it = std::remove_if(employees.begin(), employees.end(),
        [employeeId](Employee* emp) {
            return emp->getId() == employeeId;
        });

    if (it != employees.end()) {
        delete* it;
        employees.erase(it, employees.end());
        return true;
    }
    return false;
}

void StaffManager::updateEmployeeSalary(int employeeId, double newSalary) {
    Employee* employee = findEmployeeById(employeeId);
    if (employee) {
        employee->setSalary(newSalary);
    }
}

Employee* StaffManager::findEmployeeById(int employeeId) const {
    for (auto employee : employees) {
        if (employee->getId() == employeeId) {
            return employee;
        }
    }
    return nullptr;
}

void StaffManager::defineRole(const std::string& role, double baseSalary) {
    roleSalaries[role] = baseSalary;
}

std::vector<std::string> StaffManager::getAllRoles() const {
    std::vector<std::string> roles;
    for (const auto& pair : roleSalaries) {
        roles.push_back(pair.first);
    }
    return roles;
}

int StaffManager::getEmployeeCountByRole(const std::string& role) const {
    int count = 0;
    for (const auto& employee : employees) {
        if (employee->getPosition() == role) {
            count++;
        }
    }
    return count;
}

double StaffManager::calculateTotalPayroll() const {
    double total = 0.0;
    for (const auto& employee : employees) {
        total += employee->getSalary();
    }
    return total;
}

double StaffManager::calculateAverageSalary() const {
    return employees.empty() ? 0.0 : calculateTotalPayroll() / employees.size();
}

void StaffManager::recordShift(const Shift& shift) {
    shiftHistory.push_back(shift);
}

double StaffManager::calculateEmployeeHours(int employeeId) const {
    double totalHours = 0.0;
    for (const auto& shift : shiftHistory) {
        if (shift.getEmployeeId() == employeeId && shift.getIsConfirmed()) {
            totalHours += shift.calculateDuration();
        }
    }
    return totalHours;
}

size_t StaffManager::getTotalEmployees() const {
    return employees.size();
}

double StaffManager::getRoleSalary(const std::string& role) const {
    auto it = roleSalaries.find(role);
    return it != roleSalaries.end() ? it->second : 0.0;
}

std::vector<Employee*> StaffManager::getEmployees() const {
    return employees;
}