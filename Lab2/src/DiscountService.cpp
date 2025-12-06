#include "DiscountService.h"
#include <algorithm>

DiscountService::DiscountService() {}

double DiscountService::calculateLoyaltyDiscount(const Customer& customer) {
    if (customer.isVIP()) return 15.0;
    int points = customer.getLoyaltyPoints();
    if (points > 1000) return 10.0;
    if (points > 500) return 5.0;
    return 0.0;
}

double DiscountService::calculateVolumeDiscount(const Order& order) {
    double total = order.calculateTotal();
    if (total > 5000) return 15.0;
    if (total > 3000) return 10.0;
    if (total > 1000) return 5.0;
    return 0.0;
}

bool DiscountService::validatePromoCode(const std::string& promoCode) {
    std::vector<std::string> validCodes = { "SUMMER2024", "WELCOME10", "FIRSTORDER" };
    return std::find(validCodes.begin(), validCodes.end(), promoCode) != validCodes.end();
}

std::vector<Discount> DiscountService::getApplicableDiscounts(const Order& order, const Customer& customer) {
    std::vector<Discount> discounts;

    double loyaltyDiscount = calculateLoyaltyDiscount(customer);
    if (loyaltyDiscount > 0) {
        discounts.emplace_back("Loyalty Discount", loyaltyDiscount, "percentage", "LOYALTY");
    }

    double volumeDiscount = calculateVolumeDiscount(order);
    if (volumeDiscount > 0) {
        discounts.emplace_back("Volume Discount", volumeDiscount, "percentage", "VOLUME");
    }

    return discounts;
}

double DiscountService::calculateTotalDiscount(const std::vector<Discount>& discounts, double orderTotal) {
    double totalDiscount = 0.0;
    double currentPrice = orderTotal;

    for (const auto& discount : discounts) {
        if (discount.isValid()) {
            double discountAmount = discount.calculateDiscountAmount(currentPrice);
            totalDiscount += discountAmount;
            currentPrice -= discountAmount;
        }
    }

    return totalDiscount;
}