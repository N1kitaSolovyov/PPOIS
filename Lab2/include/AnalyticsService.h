#pragma once
#ifndef ANALYTICS_SERVICE_H
#define ANALYTICS_SERVICE_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "CustomerAnalytics.h"
#include "SalesAnalytics.h"
#include "PerformanceMetrics.h"

class AnalyticsService {
private:
    CustomerAnalytics customerAnalytics;
    SalesAnalytics salesAnalytics;
    PerformanceMetrics performanceMetrics;
    std::vector<std::string> reportHistory;

public:
    AnalyticsService();
    void generateDailyReport();
    void generateWeeklyReport();
    void generateMonthlyReport();
    void trackCustomerBehavior(int customerId, const std::string& behavior);
    void trackSalesData(const std::string& category, double amount);
    void updatePerformanceMetrics(const std::string& metric, double value);
    std::string getLastReport() const;
    void exportData(const std::string& format) const;
};

#endif