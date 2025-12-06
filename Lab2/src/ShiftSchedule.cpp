#include "ShiftSchedule.h"
#include <algorithm>

ShiftSchedule::ShiftSchedule() {
    roleRequirements = { {"waiter", 3}, {"chef", 2}, {"bartender", 1} };
}

void ShiftSchedule::addShift(const Shift& shift) {
    shifts.push_back(shift);
}

bool ShiftSchedule::removeShift(int shiftId) {
    auto it = std::remove_if(shifts.begin(), shifts.end(),
        [shiftId](const Shift& shift) {
            return shift.getShiftId() == shiftId;
        });

    if (it != shifts.end()) {
        shifts.erase(it, shifts.end());
        return true;
    }
    return false;
}

std::vector<Shift> ShiftSchedule::getEmployeeShifts(int employeeId) const {
    std::vector<Shift> employeeShifts;
    for (const auto& shift : shifts) {
        if (shift.getEmployeeId() == employeeId) {
            employeeShifts.push_back(shift);
        }
    }
    return employeeShifts;
}

bool ShiftSchedule::assignEmployeeToShift(int employeeId, std::time_t startTime,
    std::time_t endTime, const std::string& role) {
    if (!canEmployeeWorkShift(employeeId, startTime, endTime)) {
        return false;
    }

    int newShiftId = shifts.empty() ? 1 : shifts.back().getShiftId() + 1;
    shifts.emplace_back(newShiftId, employeeId, startTime, endTime, "scheduled", role);
    return true;
}

bool ShiftSchedule::canEmployeeWorkShift(int employeeId, std::time_t startTime, std::time_t endTime) const {
    Shift testShift(0, employeeId, startTime, endTime, "test", "test");
    for (const auto& shift : shifts) {
        if (shift.getEmployeeId() == employeeId && shift.overlapsWith(testShift)) {
            return false;
        }
    }
    return true;
}

int ShiftSchedule::getTotalShifts() const { return shifts.size(); }

void ShiftSchedule::setRoleRequirement(const std::string& role, int requiredCount) {
    roleRequirements[role] = requiredCount;
}