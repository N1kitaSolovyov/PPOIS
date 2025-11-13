#pragma once
#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <string>

class OrderItem {
private:
    int menuItemId;
    std::string itemName;
    int quantity;
    double unitPrice;
    std::string specialRequest;

public:
    OrderItem(int menuItemId, const std::string& itemName,
        int quantity, double unitPrice);

    // Геттеры
    int getMenuItemId() const;
    std::string getItemName() const;
    int getQuantity() const;
    double getUnitPrice() const;
    std::string getSpecialRequest() const;

    // Сеттеры
    void setQuantity(int newQuantity);
    void setSpecialRequest(const std::string& request);

    // Простой расчет на основе данных
    double calculateSubtotal() const;
};

#endif