#include "TaxCalculator.h"

TaxCalculator::TaxCalculator() {
    taxRates = {
        {"standard", 20.0}, {"alcohol", 25.0},
        {"food", 10.0}, {"non_alcohol", 5.0},
        {"luxury", 30.0}
    };
}

double TaxCalculator::calculateTax(const MenuItem& item) const {
    std::string category = item.getTaxCategory();
    double rate = getTaxRate(category);
    return item.getBasePrice() * (rate / 100);
}

double TaxCalculator::calculateTotalTax(const Order& order) const {
    double totalTax = 0.0;
    for (const auto& item : order.getItems()) {
        totalTax += item.getUnitPrice() * item.getQuantity() * 0.2; // ”прощенный расчет
    }
    return totalTax;
}

double TaxCalculator::getTaxRate(const std::string& category) const {
    auto it = taxRates.find(category);
    return it != taxRates.end() ? it->second : taxRates.at("standard");
}

void TaxCalculator::setTaxRate(const std::string& category, double rate) {
    taxRates[category] = rate;
}