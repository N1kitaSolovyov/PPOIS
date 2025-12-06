#pragma once
#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H

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

    double calculateSubtotal() const;

    // Getters
    int getMenuItemId() const;
    std::string getItemName() const;
    int getQuantity() const;
    double getUnitPrice() const;
    std::string getSpecialRequest() const;

    // Setters
    void setQuantity(int newQuantity);
    void setSpecialRequest(const std::string& request);
};

#endif