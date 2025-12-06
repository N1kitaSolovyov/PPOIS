#include "Customer.h"

Customer::Customer(int id, const std::string& name, const std::string& phone)
    : id(id), name(name), phone(phone), loyaltyPoints(0), customerType("regular") {
}

void Customer::addLoyaltyPoints(int points) {
    loyaltyPoints += points;
    if (loyaltyPoints > 1000) customerType = "vip";
    else if (loyaltyPoints > 500) customerType = "premium";
}

bool Customer::isVIP() const { return customerType == "vip"; }

double Customer::getDiscountRate() const {
    if (customerType == "vip") return 0.15;
    if (customerType == "premium") return 0.10;
    if (loyaltyPoints > 200) return 0.05;
    return 0.0;
}

// Getters
int Customer::getId() const { return id; }
std::string Customer::getName() const { return name; }
std::string Customer::getPhone() const { return phone; }
std::string Customer::getEmail() const { return email; }
int Customer::getLoyaltyPoints() const { return loyaltyPoints; }
std::string Customer::getCustomerType() const { return customerType; }

// Setters
void Customer::setName(const std::string& newName) { name = newName; }
void Customer::setPhone(const std::string& newPhone) { phone = newPhone; }
void Customer::setEmail(const std::string& newEmail) { email = newEmail; }
void Customer::setLoyaltyPoints(int points) { loyaltyPoints = points; }
void Customer::setCustomerType(const std::string& type) { customerType = type; }