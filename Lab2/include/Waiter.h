#pragma once
#ifndef WAITER_H
#define WAITER_H

#include "Employee.h"
#include "Table.h"
#include <vector>

class Waiter : public Employee {
private:
    std::vector<int> assignedTables; // store table numbers
    double tips;

public:
    Waiter(int id, const std::string& name, double salary, const std::string& phone = "");

    void assignTable(int tableNumber);
    void removeTable(int tableNumber);
    int getAssignedTableCount() const;
    void addTip(double amount);
    double getTotalTips() const;

    void performDuties() const override;
};

#endif