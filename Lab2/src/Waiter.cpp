#include "Waiter.h"
#include <iostream>
#include <algorithm>

Waiter::Waiter(int id, const std::string& name, double salary, const std::string& phone)
    : Employee(id, name, "waiter", salary, phone), tips(0.0) {
}

void Waiter::assignTable(int tableNumber) {
    if (std::find(assignedTables.begin(), assignedTables.end(), tableNumber) == assignedTables.end()) {
        assignedTables.push_back(tableNumber);
    }
}

void Waiter::removeTable(int tableNumber) {
    assignedTables.erase(std::remove(assignedTables.begin(), assignedTables.end(), tableNumber),
        assignedTables.end());
}

int Waiter::getAssignedTableCount() const {
    return assignedTables.size();
}

void Waiter::addTip(double amount) {
    tips += amount;
}

double Waiter::getTotalTips() const {
    return tips;
}

void Waiter::performDuties() const {
    std::cout << "Waiter " << name << " is serving tables and taking orders." << std::endl;
}