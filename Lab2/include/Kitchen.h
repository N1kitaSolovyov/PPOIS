#pragma once
#ifndef KITCHEN_H
#define KITCHEN_H

#include "Order.h"
#include "Chef.h"
#include <vector>

class Kitchen {
private:
    int kitchenId;
    std::string name;
    std::vector<Chef*> chefs;
    std::vector<Order*> activeOrders;
    int capacity;

public:
    Kitchen(int id, const std::string& name, int capacity = 20);

    bool acceptOrder(Order& order);
    void completeOrder(int orderId);
    void addChef(Chef* chef);
    Chef* findAvailableChef() const;
    bool isFull() const;
    int getCapacity() const;
    int getCurrentLoad() const;
};

#endif