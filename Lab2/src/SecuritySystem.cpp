#include "SecuritySystem.h"
#include <iostream>

SecuritySystem::SecuritySystem() : isArmed(false), securityLevel("normal") {}

void SecuritySystem::armSystem() {
    isArmed = true;
    std::cout << "Security system ARMED" << std::endl;
}

void SecuritySystem::disarmSystem() {
    isArmed = false;
    std::cout << "Security system DISARMED" << std::endl;
}

void SecuritySystem::addCamera(const SecurityCamera& camera) {
    cameras.push_back(camera);
}

void SecuritySystem::recordIncident(const SecurityIncident& incident) {
    monitor.logIncident(incident);
}

bool SecuritySystem::checkAccess(int employeeId, const std::string& area) {
    return accessControl.hasAccess(employeeId, area);
}

std::string SecuritySystem::getSecurityStatus() const {
    return "Security Level: " + securityLevel + ", Armed: " +
        (isArmed ? "Yes" : "No") + ", Cameras: " +
        std::to_string(cameras.size());
}

void SecuritySystem::setSecurityLevel(const std::string& level) {
    securityLevel = level;
}