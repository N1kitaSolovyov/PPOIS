#pragma once
#ifndef STOCK_MANAGER_H
#define STOCK_MANAGER_H

#include <vector>
#include <string>
#include <map>
#include "StockItem.h"
#include "Supplier.h"
#include "Delivery.h"

class StockManager {
private:
    std::vector<StockItem> stockItems;
    std::vector<Supplier> suppliers;
    std::vector<Delivery> deliveries;
    double totalStockValue;
    int nextItemId;
    int nextSupplierId;
    int nextDeliveryId;

public:
    StockManager();
    void addStockItem(const std::string& name, const std::string& category, int quantity, double cost);
    void removeStockItem(int itemId);
    void updateStockQuantity(int itemId, int newQuantity);
    void processDelivery(const Delivery& delivery);
    void addSupplier(const std::string& name, const std::string& contact);
    StockItem* findItemById(int itemId);
    Supplier* findSupplierById(int supplierId);
    double calculateTotalStockValue();
    std::vector<StockItem> getLowStockItems(int threshold) const;
    std::vector<StockItem> getExpiredItems() const;
    int getTotalItems() const;
    void generateInventoryReport() const;
    // Добавьте в public секцию класса StockManager в StockManager.h
    StockItem* findItemByName(const std::string& name) {
        for (auto& item : stockItems) {
            if (item.getName() == name) {
                return &item;
            }
        }
        return nullptr;
    }

    int getNextDeliveryId() { return nextDeliveryId; }
};

#endif