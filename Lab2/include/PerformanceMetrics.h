#pragma once
#ifndef PERFORMANCE_METRICS_H
#define PERFORMANCE_METRICS_H

#include <map>
#include <string>
#include <vector>

class PerformanceMetrics {
private:
    std::map<std::string, double> currentMetrics;
    std::map<std::string, std::vector<double>> historicalData;

public:
    PerformanceMetrics();
    void setMetric(const std::string& metric, double value);
    double getMetric(const std::string& metric) const;
    void updateHistoricalData(const std::string& metric, double value);
    double getMetricAverage(const std::string& metric) const;
    double getMetricMax(const std::string& metric) const;
    double getMetricMin(const std::string& metric) const;
    std::vector<std::string> getAllMetrics() const;
    void clearMetrics();
};

#endif