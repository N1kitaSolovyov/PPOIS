#include "AccessControl.h"
#include <algorithm>

AccessControl::AccessControl() {
    // Initialize default security levels
    areaSecurityLevels["kitchen"] = "high";
    areaSecurityLevels["storage"] = "medium";
    areaSecurityLevels["dining"] = "low";
    areaSecurityLevels["office"] = "medium";
}

void AccessControl::grantAccess(int employeeId, const std::string& area) {
    employeeAccess[employeeId].push_back(area);
}

void AccessControl::revokeAccess(int employeeId, const std::string& area) {
    auto& areas = employeeAccess[employeeId];
    areas.erase(std::remove(areas.begin(), areas.end(), area), areas.end());
}

bool AccessControl::hasAccess(int employeeId, const std::string& area) const {
    auto it = employeeAccess.find(employeeId);
    if (it != employeeAccess.end()) {
        const auto& areas = it->second;
        return std::find(areas.begin(), areas.end(), area) != areas.end();
    }
    return false;
}

void AccessControl::setAreaSecurityLevel(const std::string& area, const std::string& level) {
    areaSecurityLevels[area] = level;
}

std::vector<std::string> AccessControl::getEmployeeAccessAreas(int employeeId) const {
    auto it = employeeAccess.find(employeeId);
    if (it != employeeAccess.end()) {
        return it->second;
    }
    return {};
}