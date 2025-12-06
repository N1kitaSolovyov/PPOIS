#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <map>

class Inventory {
private:
    int inventoryId;
    std::map<std::string, int> items; // itemName -> quantity
    double totalValue;

public:
    Inventory(int id);

    void addIngredient(const std::string& name, int quantity);
    bool useIngredient(const std::string& name, int quantity);
    int getIngredientQuantity(const std::string& name) const;
    void updateIngredientValue(const std::string& name, double unitCost);
    double getTotalValue() const;
    void generateStockReport() const;
};

#endif