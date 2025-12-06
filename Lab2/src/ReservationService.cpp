#include "ReservationService.h"
#include <ctime>
#include <algorithm>

ReservationService::ReservationService() {}

bool ReservationService::isValidReservation(const Reservation& reservation) {
    std::time_t now = std::time(nullptr);
    std::time_t reservationTime = reservation.getReservationTime();

    if (reservationTime <= now) return false;

    const double thirtyDaysInSeconds = 30 * 24 * 60 * 60;
    if (reservationTime > now + thirtyDaysInSeconds) return false;

    return reservation.getPartySize() > 0;
}

bool ReservationService::canModifyReservation(const Reservation& reservation) {
    std::time_t now = std::time(nullptr);
    std::time_t reservationTime = reservation.getReservationTime();
    const double twoHoursInSeconds = 2 * 60 * 60;
    return (reservationTime - now) > twoHoursInSeconds;
}

bool ReservationService::isTableAvailable(const Table& table, std::time_t requestedTime) {
    return table.getStatus() == TableStatus::FREE;
}

std::vector<int> ReservationService::findAlternativeTables(const Reservation& reservation,
    const std::vector<Table>& allTables) {
    std::vector<int> alternatives;
    int requiredCapacity = reservation.getPartySize();

    for (const auto& table : allTables) {
        if (table.canAccommodate(requiredCapacity) &&
            isTableAvailable(table, reservation.getReservationTime())) {
            alternatives.push_back(table.getNumber());
        }
    }
    return alternatives;
}

int ReservationService::calculateReservationDuration(const Reservation& reservation) {
    return 2; // Стандартно 2 часа
}