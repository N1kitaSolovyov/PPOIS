#pragma once
#ifndef RESERVATION_H
#define RESERVATION_H

#include <ctime>
#include <string>

class Reservation {
private:
    int id;
    int customerId;
    int tableNumber;
    std::time_t reservationTime;
    int partySize;
    std::string status;
    std::string specialRequests;

public:
    Reservation(int id, int customerId, int tableNumber,
        std::time_t time, int partySize);

    // Getters
    int getId() const;
    int getCustomerId() const;
    int getTableNumber() const;
    std::time_t getReservationTime() const;
    int getPartySize() const;
    std::string getStatus() const;
    std::string getSpecialRequests() const;

    // Setters
    void setReservationTime(std::time_t newTime);
    void setPartySize(int newSize);
    void setStatus(const std::string& newStatus);
    void setSpecialRequests(const std::string& requests);

    bool isValid() const;
};

#endif