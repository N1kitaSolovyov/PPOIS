#include "SecurityIncident.h"
#include <iostream>

SecurityIncident::SecurityIncident(int id, const std::string& incidentType,
    const std::string& desc, int reporterId)
    : incidentId(id), type(incidentType), description(desc),
    reportedByEmployeeId(reporterId), severity("medium") {
    timestamp = std::time(nullptr);
}

std::string SecurityIncident::getIncidentReport() const {
    return "Incident #" + std::to_string(incidentId) + ": " + type +
        " - " + description + " (Severity: " + severity + ")";
}

bool SecurityIncident::isHighSeverity() const {
    return severity == "high";
}

std::time_t SecurityIncident::getTimestamp() const {
    return timestamp;
}

void SecurityIncident::setSeverity(const std::string& sev) {
    severity = sev;
}