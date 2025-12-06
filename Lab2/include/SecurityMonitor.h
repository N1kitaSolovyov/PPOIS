#pragma once
#ifndef SECURITY_MONITOR_H
#define SECURITY_MONITOR_H

#include "SecurityIncident.h"
#include <vector>

class SecurityMonitor {
private:
    std::vector<SecurityIncident> incidents;

public:
    SecurityMonitor() = default;
    void logIncident(const SecurityIncident& incident);
    int getIncidentCount() const;
    void generateSecurityReport() const;
};

#endif