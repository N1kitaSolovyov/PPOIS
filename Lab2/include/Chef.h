#pragma once
#ifndef CHEF_H
#define CHEF_H

#include "Employee.h"
#include <string>
#include <vector>

class Chef : public Employee {
private:
    std::string specialty;
    std::vector<int> assignedOrders;
    int experienceYears;

public:
    Chef(int id, const std::string& name, double salary,
        const std::string& specialty, int experience = 0);

    void assignOrder(int orderId);
    void completeOrder(int orderId);
    bool isAvailable() const;
    std::string getSpecialty() const;
    int getExperienceYears() const;

    void performDuties() const override;
};

#endif