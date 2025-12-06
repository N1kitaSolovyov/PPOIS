#include "InventoryReport.h"
#include <iostream>

InventoryReport::InventoryReport(int id, const std::string& title)
    : Report(id, title, "Inventory"), totalInventoryValue(0.0), lowStockThreshold(10) {
}

void InventoryReport::addStockItem(const std::string& itemName, int quantity, double unitCost) {
    currentStock[itemName] = quantity;
    totalInventoryValue += quantity * unitCost;
}

void InventoryReport::analyzeStockLevels() {
    lowStockItems.clear();
    for (const auto& item : currentStock) {
        if (item.second <= lowStockThreshold) {
            lowStockItems[item.first] = item.second;
        }
    }
}

void InventoryReport::generate() {
    analyzeStockLevels();
    std::cout << "Inventory report generated: " << title << std::endl;
}

void InventoryReport::display() const {
    std::cout << "=== INVENTORY REPORT ===" << std::endl;
    std::cout << "Total Inventory Value: $" << totalInventoryValue << std::endl;
    std::cout << "Low Stock Items: " << lowStockItems.size() << std::endl;

    std::cout << "Low Stock Items:" << std::endl;
    for (const auto& item : lowStockItems) {
        std::cout << "  " << item.first << ": " << item.second << " units" << std::endl;
    }
}

void InventoryReport::setLowStockThreshold(int threshold) {
    lowStockThreshold = threshold;
}

std::vector<std::string> InventoryReport::getLowStockItems() const {
    std::vector<std::string> items;
    for (const auto& item : lowStockItems) {
        items.push_back(item.first);
    }
    return items;
}