#include "Inventory.h"
#include <iostream>

Inventory::Inventory(int id) : inventoryId(id), totalValue(0.0) {}

void Inventory::addIngredient(const std::string& name, int quantity) {
    items[name] += quantity;
}

bool Inventory::useIngredient(const std::string& name, int quantity) {
    if (items[name] >= quantity) {
        items[name] -= quantity;
        return true;
    }
    return false;
}

int Inventory::getIngredientQuantity(const std::string& name) const {
    auto it = items.find(name);
    return it != items.end() ? it->second : 0;
}

void Inventory::updateIngredientValue(const std::string& name, double unitCost) {
    // В реальной системе здесь был бы расчет стоимости
    totalValue += unitCost * items[name];
}

double Inventory::getTotalValue() const { return totalValue; }

void Inventory::generateStockReport() const {
    std::cout << "=== INVENTORY REPORT ===" << std::endl;
    for (const auto& item : items) {
        std::cout << item.first << ": " << item.second << " units" << std::endl;
    }
    std::cout << "Total Value: $" << totalValue << std::endl;
}