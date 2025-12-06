#include "Employee.h"
#include <ctime>

Employee::Employee(int id, const std::string& name, const std::string& position,
    double salary, const std::string& phone)
    : id(id), name(name), position(position), phone(phone),
    salary(salary), isActive(true) {
    hireDate = std::time(nullptr);
}

int Employee::getId() const { return id; }
std::string Employee::getName() const { return name; }
std::string Employee::getPosition() const { return position; }
std::string Employee::getPhone() const { return phone; }
double Employee::getSalary() const { return salary; }
std::time_t Employee::getHireDate() const { return hireDate; }
bool Employee::getIsActive() const { return isActive; }

void Employee::setPosition(const std::string& newPosition) { position = newPosition; }
void Employee::setSalary(double newSalary) { salary = newSalary; }
void Employee::setPhone(const std::string& newPhone) { phone = newPhone; }
void Employee::setIsActive(bool active) { isActive = active; }

int Employee::calculateYearsOfService() const {
    std::time_t now = std::time(nullptr);
    double seconds = std::difftime(now, hireDate);
    return static_cast<int>(seconds / (365 * 24 * 60 * 60));
}