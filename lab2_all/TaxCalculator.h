#pragma once
#ifndef TAXCALCULATOR_H
#define TAXCALCULATOR_H

#include "MenuItem.h"
#include "Order.h"
#include <map>
#include <string>

class TaxCalculator {
private:
    std::map<std::string, double> taxRates; // категория -> ставка налога

public:
    TaxCalculator();

    // Расчет налога для позиции меню
    double calculateTax(const MenuItem& item) const;

    // Расчет общего налога для заказа
    double calculateTotalTax(const Order& order) const;

    // Получение налоговой ставки для категории
    double getTaxRate(const std::string& category) const;

    // Установка налоговой ставки
    void setTaxRate(const std::string& category, double rate);

    // Загрузка налоговых ставок из конфигурации
    void loadTaxRatesFromConfig(const std::map<std::string, double>& newRates);
};

#endif