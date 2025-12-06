#pragma once
#ifndef PRICING_SERVICE_H
#define PRICING_SERVICE_H

#include "MenuItem.h"
#include "Discount.h"
#include "Order.h"
#include <vector>
#include <map>

class PricingService {
private:
    std::map<std::string, double> categoryMarkups;

public:
    PricingService();

    double calculateFinalPrice(const MenuItem& item, const std::vector<Discount>& discounts, double taxRate);
    double calculateOrderTotal(const Order& order);
    double calculateOrderProfit(const Order& order);
    double applyTimeBasedPricing(double basePrice, const std::string& timeOfDay);
    void setCategoryMarkup(const std::string& category, double markup);
};

#endif