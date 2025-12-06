#include "KitchenOrderCoordinator.h"
#include <algorithm>

KitchenOrderCoordinator::KitchenOrderCoordinator(Kitchen& kitchen)
    : kitchen(&kitchen) {
}

bool KitchenOrderCoordinator::submitOrderToKitchen(Order& order) {
    if (kitchen->acceptOrder(order)) {
        pendingOrders.push_back(&order);
        return true;
    }
    return false;
}

void KitchenOrderCoordinator::completeOrder(int orderId) {
    for (auto it = pendingOrders.begin(); it != pendingOrders.end(); ++it) {
        if ((*it)->getId() == orderId) {
            completedOrders.push_back(*it);
            pendingOrders.erase(it);
            kitchen->completeOrder(orderId);
            break;
        }
    }
}

std::vector<Order*> KitchenOrderCoordinator::getPendingOrders() const {
    return pendingOrders;
}

std::vector<Order*> KitchenOrderCoordinator::getCompletedOrders() const {
    return completedOrders;
}

int KitchenOrderCoordinator::getCurrentLoad() const {
    return pendingOrders.size();
}