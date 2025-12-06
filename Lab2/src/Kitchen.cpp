#include "Kitchen.h"
#include <algorithm>
#include <iostream>

Kitchen::Kitchen(int id, const std::string& name, int capacity)
    : kitchenId(id), name(name), capacity(capacity) {
}

bool Kitchen::acceptOrder(Order& order) {
    if (isFull()) return false;

    Chef* chef = findAvailableChef();
    if (!chef) return false;

    activeOrders.push_back(&order);
    chef->assignOrder(order.getId());
    order.changeStatus(OrderStatus::PREPARING);
    return true;
}

void Kitchen::completeOrder(int orderId) {
    for (auto it = activeOrders.begin(); it != activeOrders.end(); ++it) {
        if ((*it)->getId() == orderId) {
            // Освобождаем повара
            for (auto chef : chefs) {
                chef->completeOrder(orderId);
            }
            activeOrders.erase(it);
            break;
        }
    }
}



void Kitchen::addChef(Chef* chef) {
    chefs.push_back(chef);
}

Chef* Kitchen::findAvailableChef() const {
    for (auto chef : chefs) {
        if (chef->isAvailable()) return chef;
    }
    return nullptr;
}

bool Kitchen::isFull() const {
    return activeOrders.size() >= capacity;
}

int Kitchen::getCapacity() const { return capacity; }
int Kitchen::getCurrentLoad() const { return activeOrders.size(); }