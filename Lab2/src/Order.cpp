#include "Order.h"
#include <algorithm>

Order::Order(int id, int tableNumber, int customerId)
    : id(id), tableNumber(tableNumber), customerId(customerId),
    waiterId(0), status(OrderStatus::CREATED) {
    createdAt = std::time(nullptr);
    updatedAt = std::time(nullptr);
}

void Order::addItem(const OrderItem& item) {
    items.push_back(item);
    updateTimestamp();
}

void Order::removeItem(int menuItemId) {
    items.erase(std::remove_if(items.begin(), items.end(),
        [menuItemId](const OrderItem& item) {
            return item.getMenuItemId() == menuItemId;
        }), items.end());
    updateTimestamp();
}

void Order::changeStatus(OrderStatus newStatus) {
    status = newStatus;
    updateTimestamp();
}

void Order::updateTimestamp() {
    updatedAt = std::time(nullptr);
}

double Order::calculateTotal() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.calculateSubtotal();
    }
    return total;
}

int Order::getItemCount() const { return items.size(); }
bool Order::isEmpty() const { return items.empty(); }

// Getters
int Order::getId() const { return id; }
int Order::getTableNumber() const { return tableNumber; }
int Order::getCustomerId() const { return customerId; }
int Order::getWaiterId() const { return waiterId; }
OrderStatus Order::getStatus() const { return status; }
std::string Order::getSpecialInstructions() const { return specialInstructions; }
std::vector<OrderItem> Order::getItems() const { return items; }
std::time_t Order::getCreatedAt() const { return createdAt; }
std::time_t Order::getUpdatedAt() const { return updatedAt; }

// Setters
void Order::setCustomerId(int newCustomerId) {
    customerId = newCustomerId;
    updateTimestamp();
}

void Order::setWaiterId(int newWaiterId) {
    waiterId = newWaiterId;
    updateTimestamp();
}

void Order::setSpecialInstructions(const std::string& instructions) {
    specialInstructions = instructions;
    updateTimestamp();
}