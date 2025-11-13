#pragma once
#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <string>

class Discount {
private:
    std::string name;
    double value;
    std::string type; // "percentage", "fixed", "loyalty"
    std::string code;
    bool isActive;
    std::time_t validFrom;
    std::time_t validTo;

public:
    Discount(const std::string& name, double value, const std::string& type,
        const std::string& code = "", bool isActive = true);

    // Расчет суммы скидки
    double calculateDiscountAmount(double originalPrice) const;

    // Проверка валидности скидки
    bool isValid() const;

    // Проверка применимости к цене
    bool isApplicableToPrice(double price) const;

    // Геттеры
    std::string getName() const;
    double getValue() const;
    std::string getType() const;
    std::string getCode() const;
    bool getIsActive() const;
    std::time_t getValidFrom() const;
    std::time_t getValidTo() const;

    // Сеттеры
    void setName(const std::string& newName);
    void setValue(double newValue);
    void setType(const std::string& newType);
    void setCode(const std::string& newCode);
    void setIsActive(bool active);
    void setValidityPeriod(std::time_t from, std::time_t to);
};

#endif