#include "Chef.h"
#include <iostream>
#include <algorithm>

Chef::Chef(int id, const std::string& name, double salary,
    const std::string& specialty, int experience)
    : Employee(id, name, "chef", salary),
    specialty(specialty), experienceYears(experience) {
}

void Chef::assignOrder(int orderId) {
    if (std::find(assignedOrders.begin(), assignedOrders.end(), orderId) == assignedOrders.end()) {
        assignedOrders.push_back(orderId);
    }
}

void Chef::completeOrder(int orderId) {
    assignedOrders.erase(std::remove(assignedOrders.begin(), assignedOrders.end(), orderId),
        assignedOrders.end());
}

bool Chef::isAvailable() const {
    return assignedOrders.size() < 5; // Максимум 5 заказов одновременно
}

std::string Chef::getSpecialty() const { return specialty; }
int Chef::getExperienceYears() const { return experienceYears; }

void Chef::performDuties() const {
    std::cout << "Chef " << name << " is cooking " << specialty << " dishes." << std::endl;
}