#include "Customer.h"

Customer::Customer(int id, const std::string& name, const std::string& phone)
    : id(id), name(name), phone(phone), loyaltyPoints(0), customerType("regular") {
}

int Customer::getId() const {
    return id;
}

std::string Customer::getName() const {
    return name;
}

std::string Customer::getPhone() const {
    return phone;
}

std::string Customer::getEmail() const {
    return email;
}

int Customer::getLoyaltyPoints() const {
    return loyaltyPoints;
}

std::string Customer::getCustomerType() const {
    return customerType;
}

void Customer::setName(const std::string& newName) {
    name = newName;
}

void Customer::setPhone(const std::string& newPhone) {
    phone = newPhone;
}

void Customer::setEmail(const std::string& newEmail) {
    email = newEmail;
}

void Customer::setLoyaltyPoints(int points) {
    loyaltyPoints = points;
}

void Customer::setCustomerType(const std::string& type) {
    customerType = type;
}