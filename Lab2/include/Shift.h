#pragma once
#ifndef SHIFT_H
#define SHIFT_H

#include <string>
#include <ctime>

class Shift {
private:
    int shiftId;
    int employeeId;
    std::time_t startTime;
    std::time_t endTime;
    std::string shiftType;
    std::string role;
    bool isConfirmed;

public:
    Shift(int shiftId, int employeeId, std::time_t startTime,
        std::time_t endTime, const std::string& shiftType, const std::string& role);

    void confirmShift();
    double calculateDuration() const;
    bool overlapsWith(const Shift& other) const;

    // Геттеры
    int getShiftId() const;
    int getEmployeeId() const;
    std::time_t getStartTime() const;
    std::time_t getEndTime() const;
    std::string getShiftType() const;
    std::string getRole() const;
    bool getIsConfirmed() const;
};

#endif