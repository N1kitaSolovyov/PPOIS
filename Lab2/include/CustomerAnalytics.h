#pragma once
#ifndef CUSTOMER_ANALYTICS_H
#define CUSTOMER_ANALYTICS_H

#include <map>
#include <vector>
#include <string>

class CustomerAnalytics {
private:
    std::map<int, std::vector<std::string>> customerBehaviors;
    std::map<int, int> customerVisitCount;
    std::map<int, double> customerSpending;
    std::map<int, std::string> customerSegments;

public:
    CustomerAnalytics();
    void recordVisit(int customerId);
    void recordSpending(int customerId, double amount);
    void recordBehavior(int customerId, const std::string& behavior);
    void segmentCustomer(int customerId, const std::string& segment);
    int getVisitCount(int customerId) const;
    double getTotalSpending(int customerId) const;
    std::vector<std::string> getCustomerBehaviors(int customerId) const;
    std::string getCustomerSegment(int customerId) const;
    int getTotalCustomers() const;
    std::vector<int> getTopSpenders(int count) const;
};

#endif