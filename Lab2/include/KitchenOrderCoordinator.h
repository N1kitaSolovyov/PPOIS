#pragma once
#ifndef KITCHEN_ORDER_COORDINATOR_H
#define KITCHEN_ORDER_COORDINATOR_H

#include "Kitchen.h"
#include "Order.h"
#include <vector>

class KitchenOrderCoordinator {
private:
    Kitchen* kitchen;
    std::vector<Order*> pendingOrders;
    std::vector<Order*> completedOrders;

public:
    KitchenOrderCoordinator(Kitchen& kitchen);

    bool submitOrderToKitchen(Order& order);
    void completeOrder(int orderId);
    std::vector<Order*> getPendingOrders() const;
    std::vector<Order*> getCompletedOrders() const;
    int getCurrentLoad() const;
};

#endif