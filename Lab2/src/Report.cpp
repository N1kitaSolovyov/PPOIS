#include "Report.h"
#include <cmath>

Report::Report(int id, const std::string& title, const std::string& type)
    : reportId(id), title(title), reportType(type) {
    generatedAt = std::time(nullptr);
    periodStart = generatedAt;
    periodEnd = generatedAt;
}

void Report::setPeriod(std::time_t start, std::time_t end) {
    periodStart = start;
    periodEnd = end;
}

double Report::calculatePeriodDays() const {
    double seconds = std::difftime(periodEnd, periodStart);
    return seconds / (24 * 60 * 60);
}

int Report::getReportId() const { return reportId; }
std::string Report::getTitle() const { return title; }
std::string Report::getReportType() const { return reportType; }