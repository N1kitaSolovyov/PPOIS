#pragma once
#ifndef ACCESS_CONTROL_H
#define ACCESS_CONTROL_H

#include <map>
#include <vector>
#include <string>

class AccessControl {
private:
    std::map<int, std::vector<std::string>> employeeAccess; // employeeId -> areas
    std::map<std::string, std::string> areaSecurityLevels; // area -> security level

public:
    AccessControl();
    void grantAccess(int employeeId, const std::string& area);
    void revokeAccess(int employeeId, const std::string& area);
    bool hasAccess(int employeeId, const std::string& area) const;
    void setAreaSecurityLevel(const std::string& area, const std::string& level);
    std::vector<std::string> getEmployeeAccessAreas(int employeeId) const;
};

#endif