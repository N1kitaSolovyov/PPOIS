#include "StockManager.h"
#include <iostream>
#include <algorithm>
#include <ctime>

StockManager::StockManager() : totalStockValue(0.0), nextItemId(1), nextSupplierId(1), nextDeliveryId(1) {}

void StockManager::addStockItem(const std::string& name, const std::string& category, int quantity, double cost) {
    StockItem item(nextItemId++, name, category, quantity, cost);
    stockItems.push_back(item);
    totalStockValue += cost * quantity;
    std::cout << "Added stock item: " << name << " (Qty: " << quantity << ")" << std::endl;
}

void StockManager::removeStockItem(int itemId) {
    auto it = std::remove_if(stockItems.begin(), stockItems.end(),
        [itemId](const StockItem& item) {
            return item.getId() == itemId;
        });

    if (it != stockItems.end()) {
        totalStockValue -= it->getUnitCost() * it->getQuantity();
        stockItems.erase(it, stockItems.end());
        std::cout << "Removed stock item ID: " << itemId << std::endl;
    }
}

void StockManager::updateStockQuantity(int itemId, int newQuantity) {
    for (auto& item : stockItems) {
        if (item.getId() == itemId) {
            totalStockValue -= item.getUnitCost() * item.getQuantity();
            item.setQuantity(newQuantity);
            totalStockValue += item.getUnitCost() * newQuantity;
            std::cout << "Updated item " << itemId << " quantity to " << newQuantity << std::endl;
            return;
        }
    }
}

void StockManager::processDelivery(const Delivery& delivery) {
    deliveries.push_back(delivery);
    std::cout << "Processed delivery ID: " << delivery.getId() << std::endl;
}

void StockManager::addSupplier(const std::string& name, const std::string& contact) {
    Supplier supplier(nextSupplierId++, name, contact);
    suppliers.push_back(supplier);
    std::cout << "Added supplier: " << name << std::endl;
}

StockItem* StockManager::findItemById(int itemId) {
    for (auto& item : stockItems) {
        if (item.getId() == itemId) {
            return &item;
        }
    }
    return nullptr;
}

Supplier* StockManager::findSupplierById(int supplierId) {
    for (auto& supplier : suppliers) {
        if (supplier.getId() == supplierId) {
            return &supplier;
        }
    }
    return nullptr;
}

double StockManager::calculateTotalStockValue() {
    totalStockValue = 0.0;
    for (const auto& item : stockItems) {
        totalStockValue += item.getUnitCost() * item.getQuantity();
    }
    return totalStockValue;
}

std::vector<StockItem> StockManager::getLowStockItems(int threshold) const {
    std::vector<StockItem> lowStock;
    for (const auto& item : stockItems) {
        if (item.getQuantity() < threshold) {
            lowStock.push_back(item);
        }
    }
    return lowStock;
}

std::vector<StockItem> StockManager::getExpiredItems() const {
    std::vector<StockItem> expired;
    std::time_t now = std::time(nullptr);
    for (const auto& item : stockItems) {
        if (item.isExpired()) {
            expired.push_back(item);
        }
    }
    return expired;
}

int StockManager::getTotalItems() const {
    return static_cast<int>(stockItems.size());
}

void StockManager::generateInventoryReport() const {
    std::cout << "=== INVENTORY REPORT ===" << std::endl;
    std::cout << "Total Items: " << stockItems.size() << std::endl;
    std::cout << "Total Stock Value: $" << totalStockValue << std::endl;
    std::cout << "Total Suppliers: " << suppliers.size() << std::endl;
    std::cout << "Total Deliveries: " << deliveries.size() << std::endl;
}