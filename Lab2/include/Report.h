#pragma once
#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <ctime>

class Report {
protected:
    int reportId;
    std::string title;
    std::time_t generatedAt;
    std::time_t periodStart;
    std::time_t periodEnd;
    std::string reportType;

public:
    Report(int id, const std::string& title, const std::string& type);
    virtual ~Report() = default;

    virtual void generate() = 0;
    virtual void display() const = 0;

    void setPeriod(std::time_t start, std::time_t end);
    double calculatePeriodDays() const;

    // Геттеры
    int getReportId() const;
    std::string getTitle() const;
    std::string getReportType() const;
};

#endif