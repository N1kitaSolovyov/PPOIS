#pragma once
#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>

class MenuItem {
private:
    int id;
    std::string name;
    std::string description;
    double basePrice;
    std::string category;
    bool isAvailable;
    double costPrice;
    std::string taxCategory;

public:
    MenuItem(int id, const std::string& name, double basePrice,
        const std::string& category, double costPrice = 0.0);

    // Business logic
    double calculateProfit() const;
    bool isProfitable() const;
    void applyPriceIncrease(double percentage);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    double getBasePrice() const;
    std::string getCategory() const;
    bool getIsAvailable() const;
    double getCostPrice() const;
    std::string getTaxCategory() const;

    // Setters
    void setName(const std::string& newName);
    void setDescription(const std::string& newDescription);
    void setBasePrice(double newPrice);
    void setCategory(const std::string& newCategory);
    void setIsAvailable(bool available);
    void setCostPrice(double newCost);
    void setTaxCategory(const std::string& newTaxCategory);
};

#endif