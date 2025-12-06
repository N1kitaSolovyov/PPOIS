#pragma once
#ifndef DISCOUNT_SERVICE_H
#define DISCOUNT_SERVICE_H

#include "Discount.h"
#include "Customer.h"
#include "Order.h"
#include <vector>

class DiscountService {
public:
    DiscountService();

    double calculateLoyaltyDiscount(const Customer& customer);
    double calculateVolumeDiscount(const Order& order);
    bool validatePromoCode(const std::string& promoCode);
    std::vector<Discount> getApplicableDiscounts(const Order& order, const Customer& customer);
    double calculateTotalDiscount(const std::vector<Discount>& discounts, double orderTotal);
};

#endif