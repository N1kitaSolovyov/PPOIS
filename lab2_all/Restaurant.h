#pragma once
#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include <vector>
#include "Table.h"
#include "Menu.h"
#include "Reservation.h"

class Restaurant {
private:
    std::string name;
    std::string address;
    std::string phone;
    std::vector<Table> tables;
    Menu menu;
    std::vector<Reservation> reservations;

public:
    Restaurant(const std::string& name, const std::string& address, const std::string& phone);

    // Базовые операции с данными
    void addTable(const Table& table);
    void addReservation(const Reservation& reservation);
    void removeReservation(int reservationId);

    // Геттеры
    std::string getName() const;
    std::string getAddress() const;
    std::string getPhone() const;
    std::vector<Table> getTables() const;
    Menu& getMenu();
    std::vector<Reservation> getReservations() const;

    // Сеттеры
    void setName(const std::string& newName);
    void setAddress(const std::string& newAddress);
    void setPhone(const std::string& newPhone);
};

#endif