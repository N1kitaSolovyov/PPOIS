#include "StockItem.h"
#include <iostream>
#include <ctime>

StockItem::StockItem(int itemId, const std::string& itemName, const std::string& itemCategory,
    int initialQuantity, double cost)
    : id(itemId), name(itemName), category(itemCategory), quantity(initialQuantity),
    unitCost(cost), lowStockThreshold(10) {
    expiryDate = std::time(nullptr) + (365 * 24 * 60 * 60); // 1 year from now
    lastRestocked = std::time(nullptr);
}

void StockItem::setQuantity(int newQuantity) {
    quantity = newQuantity;
}

void StockItem::setUnitCost(double cost) {
    unitCost = cost;
}

void StockItem::setExpiryDate(std::time_t date) {
    expiryDate = date;
}

void StockItem::setLowStockThreshold(int threshold) {
    lowStockThreshold = threshold;
}

void StockItem::restock(int amount) {
    quantity += amount;
    lastRestocked = std::time(nullptr);
    std::cout << "Restocked " << name << " with " << amount << " units" << std::endl;
}

bool StockItem::isLowStock() const {
    return quantity < lowStockThreshold;
}

bool StockItem::isExpired() const {
    return std::time(nullptr) > expiryDate;
}

int StockItem::getId() const {
    return id;
}

std::string StockItem::getName() const {
    return name;
}

std::string StockItem::getCategory() const {
    return category;
}

int StockItem::getQuantity() const {
    return quantity;
}

double StockItem::getUnitCost() const {
    return unitCost;
}

std::time_t StockItem::getExpiryDate() const {
    return expiryDate;
}

std::string StockItem::getStatus() const {
    if (isExpired()) return "EXPIRED";
    if (isLowStock()) return "LOW_STOCK";
    return "OK";
}