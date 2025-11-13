#include "TaxCalculator.h"

TaxCalculator::TaxCalculator() {
    // Стандартные налоговые ставки
    taxRates = {
        {"standard", 20.0},    // 20% стандартный налог
        {"alcohol", 25.0},     // 25% на алкоголь
        {"food", 10.0},        // 10% на еду
        {"non_alcohol", 5.0},  // 5% на безалкогольные напитки
        {"luxury", 30.0}       // 30% на предметы роскоши
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
        // Здесь нужен доступ к MenuItem для получения taxCategory
        // В реальной системе был бы запрос к меню по menuItemId
        totalTax += item.getUnitPrice() * item.getQuantity() * 0.2; // Пример: 20%
    }
    return totalTax;
}

double TaxCalculator::getTaxRate(const std::string& category) const {
    auto it = taxRates.find(category);
    if (it != taxRates.end()) {
        return it->second;
    }
    return taxRates.at("standard"); // Стандартная ставка по умолчанию
}

void TaxCalculator::setTaxRate(const std::string& category, double rate) {
    taxRates[category] = rate;
}

void TaxCalculator::loadTaxRatesFromConfig(const std::map<std::string, double>& newRates) {
    taxRates = newRates;
}