#include "MenuItem.h"

MenuItem::MenuItem(int id, const std::string& name, double basePrice,
    const std::string& category, double costPrice)
    : id(id), name(name), basePrice(basePrice), category(category),
    isAvailable(true), costPrice(costPrice), taxCategory("standard") {
}

double MenuItem::calculateProfit() const {
    return basePrice - costPrice;
}

bool MenuItem::isProfitable() const {
    return calculateProfit() > 0;
}

void MenuItem::applyPriceIncrease(double percentage) {
    basePrice *= (1 + percentage / 100);
}

// Getters
int MenuItem::getId() const { return id; }
std::string MenuItem::getName() const { return name; }
std::string MenuItem::getDescription() const { return description; }
double MenuItem::getBasePrice() const { return basePrice; }
std::string MenuItem::getCategory() const { return category; }
bool MenuItem::getIsAvailable() const { return isAvailable; }
double MenuItem::getCostPrice() const { return costPrice; }
std::string MenuItem::getTaxCategory() const { return taxCategory; }

// Setters
void MenuItem::setName(const std::string& newName) { name = newName; }
void MenuItem::setDescription(const std::string& newDescription) { description = newDescription; }
void MenuItem::setBasePrice(double newPrice) { basePrice = newPrice; }
void MenuItem::setCategory(const std::string& newCategory) { category = newCategory; }
void MenuItem::setIsAvailable(bool available) { isAvailable = available; }
void MenuItem::setCostPrice(double newCost) { costPrice = newCost; }
void MenuItem::setTaxCategory(const std::string& newTaxCategory) { taxCategory = newTaxCategory; }