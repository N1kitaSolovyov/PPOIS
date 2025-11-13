#include "DiscountService.h"
#include "Discount.h"
#include <algorithm>

double DiscountService::calculateLoyaltyDiscount(const Customer& customer) {
    int points = customer.getLoyaltyPoints();
    std::string customerType = customer.getCustomerType();

    if (customerType == "vip") {
        return 15.0; // 15% для VIP
    }
    else if (points > 1000) {
        return 10.0; // 10% за 1000+ баллов
    }
    else if (points > 500) {
        return 5.0;  // 5% за 500+ баллов
    }

    return 0.0; // Нет скидки
}

double DiscountService::calculateVolumeDiscount(const Order& order) {
    double total = 0.0;
    for (const auto& item : order.getItems()) {
        total += item.calculateSubtotal();
    }

    if (total > 5000) return 15.0; // 15% для заказов > 5000
    if (total > 3000) return 10.0; // 10% для заказов > 3000
    if (total > 1000) return 5.0;  // 5% для заказов > 1000

    return 0.0;
}

bool DiscountService::validatePromoCode(const std::string& promoCode) {
    // В реальной системе здесь была бы проверка в базе данных
    std::vector<std::string> validCodes = { "SUMMER2024", "WELCOME10", "FIRSTORDER" };

    for (const auto& validCode : validCodes) {
        if (promoCode == validCode) {
            return true;
        }
    }
    return false;
}

std::vector<Discount> DiscountService::getApplicableDiscounts(const Order& order, const Customer& customer) {
    std::vector<Discount> discounts;

    // Скидка лояльности
    double loyaltyDiscountValue = calculateLoyaltyDiscount(customer);
    if (loyaltyDiscountValue > 0) {
        Discount loyaltyDiscount("Скидка за лояльность", loyaltyDiscountValue, "percentage", "LOYALTY");
        discounts.push_back(loyaltyDiscount);
    }

    // Скидка за объем
    double volumeDiscountValue = calculateVolumeDiscount(order);
    if (volumeDiscountValue > 0) {
        Discount volumeDiscount("Скидка за объем заказа", volumeDiscountValue, "percentage", "VOLUME");
        discounts.push_back(volumeDiscount);
    }

    return discounts;
}

bool DiscountService::canCombineDiscounts(const Discount& discount1, const Discount& discount2) {
    // Некоторые скидки нельзя комбинировать
    if (discount1.getType() == "promo" && discount2.getType() == "promo") {
        return false;
    }

    // Нельзя комбинировать две фиксированные скидки
    if (discount1.getType() == "fixed" && discount2.getType() == "fixed") {
        return false;
    }

    return true;
}

// Дополнительные методы для работы со скидками
double DiscountService::calculateTotalDiscount(const std::vector<Discount>& discounts, double orderTotal) {
    double totalDiscount = 0.0;
    double currentPrice = orderTotal;

    // Применяем скидки последовательно, учитывая правила комбинирования
    for (size_t i = 0; i < discounts.size(); ++i) {
        if (!discounts[i].isValid()) {
            continue;
        }

        // Проверяем комбинирование с предыдущими примененными скидками
        bool canApply = true;
        for (size_t j = 0; j < i; ++j) {
            if (!canCombineDiscounts(discounts[j], discounts[i])) {
                canApply = false;
                break;
            }
        }

        if (canApply) {
            double discountAmount = discounts[i].calculateDiscountAmount(currentPrice);
            totalDiscount += discountAmount;
            currentPrice -= discountAmount;
        }
    }

    return totalDiscount;
}

std::vector<Discount> DiscountService::getActivePromotions() {
    std::vector<Discount> activePromotions;

    // В реальной системе здесь был бы запрос к базе данных
    // Сейчас создаем тестовые промо-акции

    // Летняя акция
    Discount summerPromo("Летняя распродажа", 20.0, "percentage", "SUMMER2024");
    summerPromo.setValidityPeriod(std::time(nullptr), std::time(nullptr) + (30 * 24 * 60 * 60)); // 30 дней

    // Приветственная скидка для новых клиентов
    Discount welcomePromo("Приветственная скидка", 10.0, "percentage", "WELCOME10");
    welcomePromo.setValidityPeriod(std::time(nullptr), std::time(nullptr) + (90 * 24 * 60 * 60)); // 90 дней

    // Фиксированная скидка на первый заказ
    Discount firstOrderPromo("Скидка на первый заказ", 500.0, "fixed", "FIRSTORDER");
    firstOrderPromo.setValidityPeriod(std::time(nullptr), std::time(nullptr) + (365 * 24 * 60 * 60)); // 1 год

    activePromotions.push_back(summerPromo);
    activePromotions.push_back(welcomePromo);
    activePromotions.push_back(firstOrderPromo);

    return activePromotions;
}

bool DiscountService::isDiscountApplicable(const Discount& discount, const Order& order, const Customer& customer) {
    if (!discount.isValid()) {
        return false;
    }

    // Проверяем минимальную сумму заказа для скидки
    double orderTotal = 0.0;
    for (const auto& item : order.getItems()) {
        orderTotal += item.calculateSubtotal();
    }

    // Для фиксированных скидок проверяем, что сумма заказа больше суммы скидки
    if (discount.getType() == "fixed" && orderTotal < discount.getValue()) {
        return false;
    }

    // Для процентных скидок проверяем минимальную сумму (например, 100 рублей)
    if (discount.getType() == "percentage" && orderTotal < 100.0) {
        return false;
    }

    // Проверяем специальные условия для определенных типов скидок
    if (discount.getCode() == "LOYALTY" && customer.getLoyaltyPoints() < 100) {
        return false;
    }

    return true;
}