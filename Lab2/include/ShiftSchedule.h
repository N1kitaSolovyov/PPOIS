#pragma once
#ifndef SHIFT_SCHEDULE_H
#define SHIFT_SCHEDULE_H

#include "Shift.h"
#include <vector>
#include <map>
#include <string>

class ShiftSchedule {
private:
    std::vector<Shift> shifts;
    std::map<std::string, int> roleRequirements;

public:
    ShiftSchedule();

    void addShift(const Shift& shift);
    bool removeShift(int shiftId);
    std::vector<Shift> getEmployeeShifts(int employeeId) const;
    bool assignEmployeeToShift(int employeeId, std::time_t startTime,
        std::time_t endTime, const std::string& role);
    bool canEmployeeWorkShift(int employeeId, std::time_t startTime, std::time_t endTime) const;

    int getTotalShifts() const;
    void setRoleRequirement(const std::string& role, int requiredCount);
};

#endif