#include "CustomerAnalytics.h"
#include <algorithm>
#include <vector>
#include <utility>

CustomerAnalytics::CustomerAnalytics() {}

void CustomerAnalytics::recordVisit(int customerId) {
    customerVisitCount[customerId]++;
}

void CustomerAnalytics::recordSpending(int customerId, double amount) {
    customerSpending[customerId] += amount;
}

void CustomerAnalytics::recordBehavior(int customerId, const std::string& behavior) {
    customerBehaviors[customerId].push_back(behavior);
}

void CustomerAnalytics::segmentCustomer(int customerId, const std::string& segment) {
    customerSegments[customerId] = segment;
}

int CustomerAnalytics::getVisitCount(int customerId) const {
    auto it = customerVisitCount.find(customerId);
    return it != customerVisitCount.end() ? it->second : 0;
}

double CustomerAnalytics::getTotalSpending(int customerId) const {
    auto it = customerSpending.find(customerId);
    return it != customerSpending.end() ? it->second : 0.0;
}

std::vector<std::string> CustomerAnalytics::getCustomerBehaviors(int customerId) const {
    auto it = customerBehaviors.find(customerId);
    return it != customerBehaviors.end() ? it->second : std::vector<std::string>();
}

std::string CustomerAnalytics::getCustomerSegment(int customerId) const {
    auto it = customerSegments.find(customerId);
    return it != customerSegments.end() ? it->second : "unsegmented";
}

int CustomerAnalytics::getTotalCustomers() const {
    return static_cast<int>(customerVisitCount.size());
}

std::vector<int> CustomerAnalytics::getTopSpenders(int count) const {
    std::vector<std::pair<int, double>> spenders;
    for (const auto& entry : customerSpending) {
        spenders.emplace_back(entry.first, entry.second);
    }

    std::sort(spenders.begin(), spenders.end(),
        [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
            return a.second > b.second;
        });

    std::vector<int> result;
    for (int i = 0; i < std::min(count, static_cast<int>(spenders.size())); i++) {
        result.push_back(spenders[i].first);
    }
    return result;
}