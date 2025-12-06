#pragma once
#ifndef RESERVATION_SERVICE_H
#define RESERVATION_SERVICE_H

#include "Reservation.h"
#include "Table.h"
#include <vector>
#include <ctime>

class ReservationService {
public:
    ReservationService();

    bool isValidReservation(const Reservation& reservation);
    bool canModifyReservation(const Reservation& reservation);
    bool isTableAvailable(const Table& table, std::time_t requestedTime);
    std::vector<int> findAlternativeTables(const Reservation& reservation,
        const std::vector<Table>& allTables);
    int calculateReservationDuration(const Reservation& reservation);
};

#endif