#pragma once
#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include <ctime>
#include "OrderItem.h"

enum class OrderStatus {
    CREATED,
    IN_PROGRESS,
    COMPLETED,
    CANCELLED
};

class Order {
private:
    int id;
    int tableNumber;
    int customerId;
    int waiterId;
    std::vector<OrderItem> items;
    OrderStatus status;
    std::string specialInstructions;
    std::time_t createdAt;
    std::time_t updatedAt;

public:
    Order(int id, int tableNumber, int customerId = 0);

    // Базовые операции с заказом
    void addItem(const OrderItem& item);
    void removeItem(int menuItemId);
    void changeStatus(OrderStatus newStatus);
    void updateTimestamp();

    // Геттеры
    int getId() const;
    int getTableNumber() const;
    int getCustomerId() const;
    int getWaiterId() const;
    OrderStatus getStatus() const;
    std::string getSpecialInstructions() const;
    std::vector<OrderItem> getItems() const;
    std::time_t getCreatedAt() const;
    std::time_t getUpdatedAt() const;

    // Сеттеры
    void setCustomerId(int newCustomerId);
    void setWaiterId(int newWaiterId);
    void setSpecialInstructions(const std::string& instructions);
};

#endif