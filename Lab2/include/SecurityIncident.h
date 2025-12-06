#pragma once
#ifndef SECURITY_INCIDENT_H
#define SECURITY_INCIDENT_H

#include <string>
#include <ctime>

class SecurityIncident {
private:
    int incidentId;
    std::string type; // "unauthorized_access", "theft", "safety_issue"
    std::string description;
    std::time_t timestamp;
    std::string severity; // "low", "medium", "high"
    int reportedByEmployeeId;

public:
    SecurityIncident(int id, const std::string& incidentType,
        const std::string& desc, int reporterId);
    std::string getIncidentReport() const;
    bool isHighSeverity() const;
    std::time_t getTimestamp() const;
    void setSeverity(const std::string& sev);
};

#endif