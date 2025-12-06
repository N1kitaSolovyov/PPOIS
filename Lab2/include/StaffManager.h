#pragma once
#ifndef STAFF_MANAGER_H
#define STAFF_MANAGER_H

#include "Employee.h"
#include "Waiter.h"
#include "Chef.h"
#include "Shift.h"
#include <vector>
#include <map>

class StaffManager {
private:
    std::vector<Employee*> employees;
    std::map<std::string, double> roleSalaries;
    std::vector<Shift> shiftHistory;
    int nextEmployeeId;

public:
    StaffManager();
    ~StaffManager();

    // Управление сотрудниками
    int hireEmployee(const std::string& name, const std::string& role, double salary);
    bool terminateEmployee(int employeeId);
    void updateEmployeeSalary(int employeeId, double newSalary);
    Employee* findEmployeeById(int employeeId) const;

    // Управление ролями
    void defineRole(const std::string& role, double baseSalary);
    std::vector<std::string> getAllRoles() const;
    int getEmployeeCountByRole(const std::string& role) const;

    // Финансы персонала
    double calculateTotalPayroll() const;
    double calculateAverageSalary() const;

    // Учет рабочего времени
    void recordShift(const Shift& shift);
    double calculateEmployeeHours(int employeeId) const;

    // Геттеры
    size_t getTotalEmployees() const;
    double getRoleSalary(const std::string& role) const;
    std::vector<Employee*> getEmployees() const;
};

#endif