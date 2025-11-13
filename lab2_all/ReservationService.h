#pragma once
#ifndef RESERVATIONSERVICE_H
#define RESERVATIONSERVICE_H

#include "Reservation.h"
#include "Table.h"
#include <ctime>
#include <vector>

class ReservationService {
public:
    // Проверка валидности брони
    static bool isValidReservation(const Reservation& reservation);

    // Проверка возможности изменения брони
    static bool canModifyReservation(const Reservation& reservation);

    // Проверка доступности столика
    static bool isTableAvailable(const Table& table, std::time_t requestedTime);

    // Отправка напоминания о брони
    static void sendReservationReminder(const Reservation& reservation);

    // Поиск альтернативных столиков
    static std::vector<int> findAlternativeTables(const Reservation& reservation,
        const std::vector<Table>& allTables);

    // Расчет продолжительности брони
    static int calculateReservationDuration(const Reservation& reservation);
};

#endif