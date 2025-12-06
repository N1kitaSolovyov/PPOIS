#include "PerformanceMetrics.h"
#include <algorithm>
#include <numeric>
#include <iterator>

PerformanceMetrics::PerformanceMetrics() {
    // Initialize default metrics
    currentMetrics["avg_order_value"] = 0.0;
    currentMetrics["retention_rate"] = 0.0;
    currentMetrics["growth_rate"] = 0.0;
    currentMetrics["satisfaction_score"] = 0.0;
}

void PerformanceMetrics::setMetric(const std::string& metric, double value) {
    currentMetrics[metric] = value;
}

double PerformanceMetrics::getMetric(const std::string& metric) const {
    auto it = currentMetrics.find(metric);
    return it != currentMetrics.end() ? it->second : 0.0;
}

void PerformanceMetrics::updateHistoricalData(const std::string& metric, double value) {
    historicalData[metric].push_back(value);
}

double PerformanceMetrics::getMetricAverage(const std::string& metric) const {
    auto it = historicalData.find(metric);
    if (it != historicalData.end() && !it->second.empty()) {
        double sum = std::accumulate(it->second.begin(), it->second.end(), 0.0);
        return sum / it->second.size();
    }
    return 0.0;
}

double PerformanceMetrics::getMetricMax(const std::string& metric) const {
    auto it = historicalData.find(metric);
    if (it != historicalData.end() && !it->second.empty()) {
        return *std::max_element(it->second.begin(), it->second.end());
    }
    return 0.0;
}

double PerformanceMetrics::getMetricMin(const std::string& metric) const {
    auto it = historicalData.find(metric);
    if (it != historicalData.end() && !it->second.empty()) {
        return *std::min_element(it->second.begin(), it->second.end());
    }
    return 0.0;
}

std::vector<std::string> PerformanceMetrics::getAllMetrics() const {
    std::vector<std::string> metrics;
    for (const auto& entry : currentMetrics) {
        metrics.push_back(entry.first);
    }
    return metrics;
}

void PerformanceMetrics::clearMetrics() {
    currentMetrics.clear();
    historicalData.clear();
}