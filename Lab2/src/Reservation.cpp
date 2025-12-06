#include "Reservation.h"
#include <ctime>

Reservation::Reservation(int id, int customerId, int tableNumber,
    std::time_t time, int partySize)
    : id(id), customerId(customerId), tableNumber(tableNumber),
    reservationTime(time), partySize(partySize), status("confirmed") {
}

int Reservation::getId() const { return id; }
int Reservation::getCustomerId() const { return customerId; }
int Reservation::getTableNumber() const { return tableNumber; }
std::time_t Reservation::getReservationTime() const { return reservationTime; }
int Reservation::getPartySize() const { return partySize; }
std::string Reservation::getStatus() const { return status; }
std::string Reservation::getSpecialRequests() const { return specialRequests; }

void Reservation::setReservationTime(std::time_t newTime) {
    reservationTime = newTime;
}

void Reservation::setPartySize(int newSize) {
    if (newSize > 0) partySize = newSize;
}

void Reservation::setStatus(const std::string& newStatus) {
    status = newStatus;
}

void Reservation::setSpecialRequests(const std::string& requests) {
    specialRequests = requests;
}

bool Reservation::isValid() const {
    std::time_t now = std::time(nullptr);
    return reservationTime > now && partySize > 0;
}