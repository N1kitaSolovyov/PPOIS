#include "SalesReport.h"
#include <iostream>

SalesReport::SalesReport(int id, const std::string& title)
    : Report(id, title, "Sales"), totalRevenue(0.0), averageOrderValue(0.0), totalOrders(0) {
}

void SalesReport::addSale(const std::string& category, double amount) {
    categoryRevenue[category] += amount;
    totalRevenue += amount;
    totalOrders++;
}

void SalesReport::calculateMetrics() {
    averageOrderValue = totalOrders > 0 ? totalRevenue / totalOrders : 0.0;
}

void SalesReport::generate() {
    calculateMetrics();
    std::cout << "Sales report generated: " << title << std::endl;
}

void SalesReport::display() const {
    std::cout << "=== SALES REPORT ===" << std::endl;
    std::cout << "Total Revenue: $" << totalRevenue << std::endl;
    std::cout << "Total Orders: " << totalOrders << std::endl;
    std::cout << "Average Order: $" << averageOrderValue << std::endl;

    std::cout << "Revenue by Category:" << std::endl;
    for (const auto& category : categoryRevenue) {
        std::cout << "  " << category.first << ": $" << category.second << std::endl;
    }
}

double SalesReport::getTotalRevenue() const { return totalRevenue; }
double SalesReport::getAverageOrderValue() const { return averageOrderValue; }
int SalesReport::getTotalOrders() const { return totalOrders; }