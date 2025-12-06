#pragma once
#ifndef SALES_REPORT_H
#define SALES_REPORT_H

#include "Report.h"
#include <map>
#include <vector>

class SalesReport : public Report {
private:
    std::map<std::string, double> categoryRevenue;
    double totalRevenue;
    double averageOrderValue;
    int totalOrders;

public:
    SalesReport(int id, const std::string& title);

    void addSale(const std::string& category, double amount);
    void calculateMetrics();

    void generate() override;
    void display() const override;

    // Геттеры
    double getTotalRevenue() const;
    double getAverageOrderValue() const;
    int getTotalOrders() const;
};

#endif