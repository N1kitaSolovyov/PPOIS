#pragma once
#ifndef PRICINGSERVICE_H
#define PRICINGSERVICE_H

#include "MenuItem.h"
#include "Order.h"
#include <vector>
#include <map>

class Discount; // Forward declaration

class PricingService {
public:
    // Расчет итоговой цены для позиции меню
    static double calculateFinalPrice(const MenuItem& item,
        const std::vector<Discount>& discounts,
        double taxRate);

    // Расчет общей суммы заказа
    static double calculateOrderTotal(const Order& order);

    // Расчет прибыли по заказу
    static double calculateOrderProfit(const Order& order);

    // Ценообразование в зависимости от времени дня
    static double applyTimeBasedPricing(double basePrice, const std::string& timeOfDay);

    // Расчет наценки на себестоимость
    static double calculateMarkup(double costPrice, double markupPercentage);
};

#endif