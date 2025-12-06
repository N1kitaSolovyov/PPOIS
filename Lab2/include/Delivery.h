#pragma once
#ifndef DELIVERY_H
#define DELIVERY_H

#include <string>
#include <ctime>
#include <vector>

class Delivery {
private:
    int id;
    int supplierId;
    std::vector<std::pair<int, int>> items; // itemId, quantity
    std::time_t deliveryDate;
    std::time_t expectedDate;
    std::string status;
    std::string trackingNumber;

public:
    Delivery(int deliveryId, int suppId, std::time_t expectedDeliveryDate);
    void addItem(int itemId, int quantity);
    void removeItem(int itemId);
    void setStatus(const std::string& newStatus);
    void setTrackingNumber(const std::string& tracking);
    void markAsDelivered();
    bool isDelivered() const;
    bool isOverdue() const;
    int getId() const;
    int getSupplierId() const;
    std::time_t getDeliveryDate() const;
    std::time_t getExpectedDate() const;
    std::string getStatus() const;
    std::string getTrackingNumber() const;
    std::vector<std::pair<int, int>> getItems() const;
};

#endif