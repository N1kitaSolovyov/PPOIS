#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <ctime>
#include <iostream>

class Employee {
protected:
    int id;
    std::string name;
    std::string position;
    std::string phone;
    double salary;
    std::time_t hireDate;
    bool isActive;

public:
    Employee(int id, const std::string& name, const std::string& position,
        double salary, const std::string& phone = "");
    virtual ~Employee() = default;

    // Геттеры
    int getId() const;
    std::string getName() const;
    std::string getPosition() const;
    std::string getPhone() const;
    double getSalary() const;
    std::time_t getHireDate() const;
    bool getIsActive() const;

    // Сеттеры
    void setPosition(const std::string& newPosition);
    void setSalary(double newSalary);
    void setPhone(const std::string& newPhone);
    void setIsActive(bool active);

    int calculateYearsOfService() const;
    virtual void performDuties() const {
        std::cout << "Employee " << name << " is performing general duties." << std::endl;
    }
};

#endif