#include "SalesAnalytics.h"
#include <algorithm>
#include <limits>

SalesAnalytics::SalesAnalytics() : totalRevenue(0.0) {}

void SalesAnalytics::recordSale(const std::string& category, double amount) {
    categoryRevenue[category] += amount;
    categoryCount[category]++;
    totalRevenue += amount;
}

void SalesAnalytics::recordHourlySale(const std::string& hour, double amount) {
    hourlyRevenue[hour] += amount;
}

double SalesAnalytics::getTotalRevenue() const {
    return totalRevenue;
}

double SalesAnalytics::getCategoryRevenue(const std::string& category) const {
    auto it = categoryRevenue.find(category);
    return it != categoryRevenue.end() ? it->second : 0.0;
}

int SalesAnalytics::getCategoryCount(const std::string& category) const {
    auto it = categoryCount.find(category);
    return it != categoryCount.end() ? it->second : 0;
}

std::string SalesAnalytics::getTopCategory() const {
    std::string topCategory;
    double maxRevenue = -1.0;

    for (const auto& entry : categoryRevenue) {
        if (entry.second > maxRevenue) {
            maxRevenue = entry.second;
            topCategory = entry.first;
        }
    }

    return topCategory.empty() ? "No sales" : topCategory;
}

double SalesAnalytics::getHourlyRevenue(const std::string& hour) const {
    auto it = hourlyRevenue.find(hour);
    return it != hourlyRevenue.end() ? it->second : 0.0;
}

void SalesAnalytics::clearDailyData() {
    categoryRevenue.clear();
    categoryCount.clear();
    hourlyRevenue.clear();
    totalRevenue = 0.0;
}