#pragma once
#ifndef SALES_ANALYTICS_H
#define SALES_ANALYTICS_H

#include <map>
#include <string>
#include <vector>

class SalesAnalytics {
private:
    std::map<std::string, double> categoryRevenue;
    std::map<std::string, int> categoryCount;
    std::map<std::string, double> hourlyRevenue;
    double totalRevenue;

public:
    SalesAnalytics();
    void recordSale(const std::string& category, double amount);
    void recordHourlySale(const std::string& hour, double amount);
    double getTotalRevenue() const;
    double getCategoryRevenue(const std::string& category) const;
    int getCategoryCount(const std::string& category) const;
    std::string getTopCategory() const;
    double getHourlyRevenue(const std::string& hour) const;
    void clearDailyData();
};

#endif