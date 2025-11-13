#pragma once
#ifndef DISCOUNTSERVICE_H
#define DISCOUNTSERVICE_H

#include "Order.h"
#include "Customer.h"
#include <vector>
#include <string>

class Discount;

class DiscountService {
public:
    // Расчет скидки по программе лояльности
    static double calculateLoyaltyDiscount(const Customer& customer);

    // Расчет скидки за объем заказа
    static double calculateVolumeDiscount(const Order& order);

    // Валидация промокода
    static bool validatePromoCode(const std::string& promoCode);

    // Получение всех применимых скидок для заказа и клиента
    static std::vector<Discount> getApplicableDiscounts(const Order& order, const Customer& customer);

    // Проверка возможности комбинирования скидок
    static bool canCombineDiscounts(const Discount& discount1, const Discount& discount2);

    // Расчет общей суммы скидки с учетом комбинирования
    static double calculateTotalDiscount(const std::vector<Discount>& discounts, double orderTotal);

    // Получение списка активных промо-акций
    static std::vector<Discount> getActivePromotions();

    // Проверка применимости конкретной скидки к заказу и клиенту
    static bool isDiscountApplicable(const Discount& discount, const Order& order, const Customer& customer);
};

#endif