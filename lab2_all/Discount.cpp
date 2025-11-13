#include "Discount.h"
#include <ctime>
#include <algorithm>

Discount::Discount(const std::string& name, double value, const std::string& type,
    const std::string& code, bool isActive)
    : name(name), value(value), type(type), code(code), isActive(isActive) {
    // По умолчанию скидка действует бессрочно
    std::time_t now = std::time(nullptr);
    validFrom = now;
    validTo = now + (365 * 24 * 60 * 60); // 1 год по умолчанию
}

double Discount::calculateDiscountAmount(double originalPrice) const {
    if (!isValid() || !isApplicableToPrice(originalPrice)) {
        return 0.0;
    }

    if (type == "percentage") {
        return originalPrice * (value / 100);
    }
    else if (type == "fixed") {
        return std::min(value, originalPrice); // Не больше исходной цены
    }

    return 0.0;
}

bool Discount::isValid() const {
    if (!isActive) {
        return false;
    }

    std::time_t now = std::time(nullptr);
    return (now >= validFrom && now <= validTo);
}

bool Discount::isApplicableToPrice(double price) const {
    // Минимальная цена для применения скидки
    double minPrice = 0.0;
    if (type == "fixed") {
        minPrice = value; // Для фиксированной скидки цена должна быть >= суммы скидки
    }
    else if (type == "percentage") {
        minPrice = 10.0; // Минимальная цена 10 для процентных скидок
    }

    return price >= minPrice;
}

std::string Discount::getName() const {
    return name;
}

double Discount::getValue() const {
    return value;
}

std::string Discount::getType() const {
    return type;
}

std::string Discount::getCode() const {
    return code;
}

bool Discount::getIsActive() const {
    return isActive;
}

std::time_t Discount::getValidFrom() const {
    return validFrom;
}

std::time_t Discount::getValidTo() const {
    return validTo;
}

void Discount::setName(const std::string& newName) {
    name = newName;
}

void Discount::setValue(double newValue) {
    value = newValue;
}

void Discount::setType(const std::string& newType) {
    type = newType;
}

void Discount::setCode(const std::string& newCode) {
    code = newCode;
}

void Discount::setIsActive(bool active) {
    isActive = active;
}

void Discount::setValidityPeriod(std::time_t from, std::time_t to) {
    validFrom = from;
    validTo = to;
}