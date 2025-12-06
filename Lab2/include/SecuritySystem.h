#pragma once
#ifndef SECURITY_SYSTEM_H
#define SECURITY_SYSTEM_H

#include <vector>
#include <string>
#include "SecurityCamera.h"
#include "AccessControl.h"
#include "SecurityIncident.h"
#include "SecurityMonitor.h"

class SecuritySystem {
private:
    std::vector<SecurityCamera> cameras;
    AccessControl accessControl;
    SecurityMonitor monitor;
    bool isArmed;
    std::string securityLevel;

public:
    SecuritySystem();
    void armSystem();
    void disarmSystem();
    void addCamera(const SecurityCamera& camera);
    void recordIncident(const SecurityIncident& incident);
    bool checkAccess(int employeeId, const std::string& area);
    std::string getSecurityStatus() const;
    void setSecurityLevel(const std::string& level);
};

#endif