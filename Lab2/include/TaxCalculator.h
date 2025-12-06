#pragma once
#ifndef TAX_CALCULATOR_H
#define TAX_CALCULATOR_H

#include "MenuItem.h"
#include "Order.h"
#include <map>
#include <string>

class TaxCalculator {
private:
    std::map<std::string, double> taxRates;

public:
    TaxCalculator();

    double calculateTax(const MenuItem& item) const;
    double calculateTotalTax(const Order& order) const;
    double getTaxRate(const std::string& category) const;
    void setTaxRate(const std::string& category, double rate);
};

#endif