#include "AnalyticsService.h"
#include <iostream>
#include <sstream>

AnalyticsService::AnalyticsService() {}

void AnalyticsService::generateDailyReport() {
    std::stringstream report;
    report << "=== DAILY ANALYTICS REPORT ===" << std::endl;
    report << "Total Customers: " << customerAnalytics.getTotalCustomers() << std::endl;
    report << "Total Revenue: $" << salesAnalytics.getTotalRevenue() << std::endl;
    report << "Top Category: " << salesAnalytics.getTopCategory() << std::endl;

    reportHistory.push_back(report.str());
    std::cout << "Generated daily analytics report" << std::endl;
}

void AnalyticsService::generateWeeklyReport() {
    std::stringstream report;
    report << "=== WEEKLY ANALYTICS REPORT ===" << std::endl;
    report << "Average Order Value: $" << performanceMetrics.getMetric("avg_order_value") << std::endl;
    report << "Customer Retention: " << performanceMetrics.getMetric("retention_rate") << "%" << std::endl;

    reportHistory.push_back(report.str());
    std::cout << "Generated weekly analytics report" << std::endl;
}

void AnalyticsService::generateMonthlyReport() {
    std::stringstream report;
    report << "=== MONTHLY ANALYTICS REPORT ===" << std::endl;
    report << "Monthly Growth: " << performanceMetrics.getMetric("growth_rate") << "%" << std::endl;
    report << "Customer Satisfaction: " << performanceMetrics.getMetric("satisfaction_score") << "/10" << std::endl;

    reportHistory.push_back(report.str());
    std::cout << "Generated monthly analytics report" << std::endl;
}

void AnalyticsService::trackCustomerBehavior(int customerId, const std::string& behavior) {
    customerAnalytics.recordBehavior(customerId, behavior);
}

void AnalyticsService::trackSalesData(const std::string& category, double amount) {
    salesAnalytics.recordSale(category, amount);
}

void AnalyticsService::updatePerformanceMetrics(const std::string& metric, double value) {
    performanceMetrics.setMetric(metric, value);
}

std::string AnalyticsService::getLastReport() const {
    return reportHistory.empty() ? "No reports available" : reportHistory.back();
}

void AnalyticsService::exportData(const std::string& format) const {
    std::cout << "Exporting analytics data in " << format << " format" << std::endl;
}