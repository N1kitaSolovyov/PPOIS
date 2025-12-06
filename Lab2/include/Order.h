#pragma once
#ifndef ORDER_H
#define ORDER_H

#include "OrderItem.h"
#include "OrderStatus.h"
#include <vector>
#include <ctime>

class Order {
private:
    int id;
    int tableNumber;
    int customerId;
    int waiterId;
    OrderStatus status;
    std::string specialInstructions;
    std::vector<OrderItem> items;
    std::time_t createdAt;
    std::time_t updatedAt;

public:
    Order(int id, int tableNumber, int customerId);

    // Order management
    void addItem(const OrderItem& item);
    void removeItem(int menuItemId);
    void changeStatus(OrderStatus newStatus);
    void updateTimestamp();

    // Calculations
    double calculateTotal() const;
    int getItemCount() const;
    bool isEmpty() const;

    // Getters
    int getId() const;
    int getTableNumber() const;
    int getCustomerId() const;
    int getWaiterId() const;
    OrderStatus getStatus() const;
    std::string getSpecialInstructions() const;
    std::vector<OrderItem> getItems() const;
    std::time_t getCreatedAt() const;
    std::time_t getUpdatedAt() const;

    // Setters
    void setCustomerId(int newCustomerId);
    void setWaiterId(int newWaiterId);
    void setSpecialInstructions(const std::string& instructions);
};

#endif