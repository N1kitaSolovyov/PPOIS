#include "SecurityMonitor.h"
#include <iostream>

void SecurityMonitor::logIncident(const SecurityIncident& incident) {
    incidents.push_back(incident);
}

int SecurityMonitor::getIncidentCount() const {
    return static_cast<int>(incidents.size());
}

void SecurityMonitor::generateSecurityReport() const {
    std::cout << "=== SECURITY REPORT ===" << std::endl;
    std::cout << "Total Incidents: " << incidents.size() << std::endl;
    for (const auto& incident : incidents) {
        std::cout << incident.getIncidentReport() << std::endl;
    }
}