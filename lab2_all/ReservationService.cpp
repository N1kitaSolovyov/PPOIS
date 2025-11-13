#include "ReservationService.h"
#include <ctime>
#include <algorithm>

bool ReservationService::isValidReservation(const Reservation& reservation) {
    std::time_t now = std::time(nullptr);
    std::time_t reservationTime = reservation.getReservationTime();

    // Бронь должна быть в будущем
    if (reservationTime <= now) {
        return false;
    }

    // Нельзя бронировать больше чем за 30 дней
    const double thirtyDaysInSeconds = 30 * 24 * 60 * 60;
    if (reservationTime > now + thirtyDaysInSeconds) {
        return false;
    }

    // Минимальная группа - 1 человек
    if (reservation.getPartySize() < 1) {
        return false;
    }

    return true;
}

bool ReservationService::canModifyReservation(const Reservation& reservation) {
    std::time_t now = std::time(nullptr);
    std::time_t reservationTime = reservation.getReservationTime();

    // Можно изменять за 2 часа до брони
    const double twoHoursInSeconds = 2 * 60 * 60;
    return (reservationTime - now) > twoHoursInSeconds;
}

bool ReservationService::isTableAvailable(const Table& table, std::time_t requestedTime) {
    // В реальной системе здесь была бы проверка в расписании
    // Пока проверяем только текущий статус столика
    return table.getStatus() == TableStatus::FREE;
}

void ReservationService::sendReservationReminder(const Reservation& reservation) {
    // В реальной системе здесь была бы отправка email/SMS
    std::time_t reminderTime = reservation.getReservationTime() - (2 * 60 * 60); // За 2 часа
    // Логика отправки уведомления...
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
    // Стандартная продолжительность брони - 2 часа
    // В реальной системе могла бы зависеть от типа заведения/события
    return 2; // часа
}