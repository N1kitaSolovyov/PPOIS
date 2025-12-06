#include "Shift.h"
#include <iostream>

Shift::Shift(int shiftId, int employeeId, std::time_t startTime,
    std::time_t endTime, const std::string& shiftType, const std::string& role)
    : shiftId(shiftId), employeeId(employeeId), startTime(startTime),
    endTime(endTime), shiftType(shiftType), role(role), isConfirmed(false) {
}

void Shift::confirmShift() {
    isConfirmed = true;
}

double Shift::calculateDuration() const {
    double seconds = std::difftime(endTime, startTime);
    return seconds / 3600.0;
}

bool Shift::overlapsWith(const Shift& other) const {
    return (startTime < other.endTime && other.startTime < endTime);
}

int Shift::getShiftId() const { return shiftId; }
int Shift::getEmployeeId() const { return employeeId; }
std::time_t Shift::getStartTime() const { return startTime; }
std::time_t Shift::getEndTime() const { return endTime; }
std::string Shift::getShiftType() const { return shiftType; }
std::string Shift::getRole() const { return role; }
bool Shift::getIsConfirmed() const { return isConfirmed; }