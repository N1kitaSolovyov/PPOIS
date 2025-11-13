#include "PricingService.h"
#include "Discount.h"

double PricingService::calculateFinalPrice(const MenuItem& item,
    const std::vector<Discount>& discounts,
    double taxRate) {
    double price = item.getBasePrice();

    // Применяем скидки
    for (const auto& discount : discounts) {
        price -= discount.calculateDiscountAmount(price);
    }

    // Добавляем налог
    price += price * (taxRate / 100);

    return price;
}

double PricingService::calculateOrderTotal(const Order& order) {
    double total = 0.0;
    for (const auto& item : order.getItems()) {
        total += item.calculateSubtotal();
    }
    return total;
}

double PricingService::calculateOrderProfit(const Order& order) {
    // Для расчета прибыли нужен доступ к себестоимости блюд
    // В реальной системе здесь был бы запрос к базе данных
    double totalRevenue = calculateOrderTotal(order);
    double estimatedCost = totalRevenue * 0.3; // Пример: 30% себестоимость
    return totalRevenue - estimatedCost;
}

double PricingService::applyTimeBasedPricing(double basePrice, const std::string& timeOfDay) {
    std::map<std::string, double> multipliers = {
        {"lunch", 0.9},      // 10% скидка в обед
        {"dinner", 1.0},     // Полная цена на ужин
        {"late_night", 1.1}  // 10% наценка поздно вечером
    };

    auto it = multipliers.find(timeOfDay);
    if (it != multipliers.end()) {
        return basePrice * it->second;
    }
    return basePrice; // По умолчанию базовая цена
}

double PricingService::calculateMarkup(double costPrice, double markupPercentage) {
    return costPrice * (1 + markupPercentage / 100);
}