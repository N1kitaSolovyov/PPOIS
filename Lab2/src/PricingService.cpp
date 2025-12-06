#include "PricingService.h"

PricingService::PricingService() {
    categoryMarkups = {
        {"appetizer", 0.4}, {"main", 0.5},
        {"dessert", 0.6}, {"beverage", 0.7}
    };
}

double PricingService::calculateFinalPrice(const MenuItem& item,
    const std::vector<Discount>& discounts,
    double taxRate) {
    double price = item.getBasePrice();

    for (const auto& discount : discounts) {
        price -= discount.calculateDiscountAmount(price);
    }

    price += price * (taxRate / 100);
    return price;
}

double PricingService::calculateOrderTotal(const Order& order) {
    return order.calculateTotal();
}

double PricingService::calculateOrderProfit(const Order& order) {
    return calculateOrderTotal(order) * 0.3; // 30% прибыль
}

double PricingService::applyTimeBasedPricing(double basePrice, const std::string& timeOfDay) {
    if (timeOfDay == "lunch") return basePrice * 0.9;
    if (timeOfDay == "late_night") return basePrice * 1.1;
    return basePrice;
}

void PricingService::setCategoryMarkup(const std::string& category, double markup) {
    categoryMarkups[category] = markup;
}