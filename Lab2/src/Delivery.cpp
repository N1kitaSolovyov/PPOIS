#include "Delivery.h"
#include <iostream>
#include <ctime>

Delivery::Delivery(int deliveryId, int suppId, std::time_t expectedDeliveryDate)
    : id(deliveryId), supplierId(suppId), expectedDate(expectedDeliveryDate),
    status("PENDING"), trackingNumber("") {
    deliveryDate = 0;
}

void Delivery::addItem(int itemId, int quantity) {
    // Check if item already exists
    for (auto& item : items) {
        if (item.first == itemId) {
            item.second += quantity;
            return;
        }
    }
    items.emplace_back(itemId, quantity);
}

void Delivery::removeItem(int itemId) {
    items.erase(
        std::remove_if(items.begin(), items.end(),
            [itemId](const std::pair<int, int>& item) {
                return item.first == itemId;
            }),
        items.end()
    );
}

void Delivery::setStatus(const std::string& newStatus) {
    status = newStatus;
}

void Delivery::setTrackingNumber(const std::string& tracking) {
    trackingNumber = tracking;
}

void Delivery::markAsDelivered() {
    status = "DELIVERED";
    deliveryDate = std::time(nullptr);
    std::cout << "Delivery " << id << " marked as delivered" << std::endl;
}

bool Delivery::isDelivered() const {
    return status == "DELIVERED";
}

bool Delivery::isOverdue() const {
    return !isDelivered() && std::time(nullptr) > expectedDate;
}

int Delivery::getId() const {
    return id;
}

int Delivery::getSupplierId() const {
    return supplierId;
}

std::time_t Delivery::getDeliveryDate() const {
    return deliveryDate;
}

std::time_t Delivery::getExpectedDate() const {
    return expectedDate;
}

std::string Delivery::getStatus() const {
    return status;
}

std::string Delivery::getTrackingNumber() const {
    return trackingNumber;
}

std::vector<std::pair<int, int>> Delivery::getItems() const {
    return items;
}