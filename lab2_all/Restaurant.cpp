#include "Restaurant.h"
#include <algorithm>

Restaurant::Restaurant(const std::string& name, const std::string& address, const std::string& phone)
    : name(name), address(address), phone(phone) {
}

void Restaurant::addTable(const Table& table) {
    tables.push_back(table);
}

void Restaurant::addReservation(const Reservation& reservation) {
    reservations.push_back(reservation);
}

void Restaurant::removeReservation(int reservationId) {
    reservations.erase(
        std::remove_if(reservations.begin(), reservations.end(),
            [reservationId](const Reservation& res) {
                return res.getId() == reservationId;
            }),
        reservations.end()
    );
}

std::string Restaurant::getName() const {
    return name;
}

std::string Restaurant::getAddress() const {
    return address;
}

std::string Restaurant::getPhone() const {
    return phone;
}

std::vector<Table> Restaurant::getTables() const {
    return tables;
}

Menu& Restaurant::getMenu() {
    return menu;
}

std::vector<Reservation> Restaurant::getReservations() const {
    return reservations;
}

void Restaurant::setName(const std::string& newName) {
    name = newName;
}

void Restaurant::setAddress(const std::string& newAddress) {
    address = newAddress;
}

void Restaurant::setPhone(const std::string& newPhone) {
    phone = newPhone;
}