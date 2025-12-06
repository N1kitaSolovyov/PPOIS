#pragma once
#ifndef STOCK_ITEM_H
#define STOCK_ITEM_H

#include <string>
#include <ctime>

class StockItem {
private:
    int id;
    std::string name;
    std::string category;
    int quantity;
    double unitCost;
    std::time_t expiryDate;
    std::time_t lastRestocked;
    int lowStockThreshold;

public:
    StockItem(int itemId, const std::string& itemName, const std::string& itemCategory,
        int initialQuantity, double cost);
    void setQuantity(int newQuantity);
    void setUnitCost(double cost);
    void setExpiryDate(std::time_t date);
    void setLowStockThreshold(int threshold);
    void restock(int amount);
    bool isLowStock() const;
    bool isExpired() const;
    int getId() const;
    std::string getName() const;
    std::string getCategory() const;
    int getQuantity() const;
    double getUnitCost() const;
    std::time_t getExpiryDate() const;
    std::string getStatus() const;
};

#endif