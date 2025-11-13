#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    int id;
    std::string name;
    std::string phone;
    std::string email;
    int loyaltyPoints;
    std::string customerType;

public:
    Customer(int id, const std::string& name, const std::string& phone);

    // Геттеры
    int getId() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;
    int getLoyaltyPoints() const;
    std::string getCustomerType() const;

    // Сеттеры
    void setName(const std::string& newName);
    void setPhone(const std::string& newPhone);
    void setEmail(const std::string& newEmail);
    void setLoyaltyPoints(int points);
    void setCustomerType(const std::string& type);
};

#endif