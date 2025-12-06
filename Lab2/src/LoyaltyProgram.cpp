#include "LoyaltyProgram.h"

LoyaltyProgram::LoyaltyProgram(double pointsRate)
    : pointsPerDollar(pointsRate), isActive(true) {
}

void LoyaltyProgram::enrollCustomer(int customerId) {
    if (customerPoints.find(customerId) == customerPoints.end()) {
        customerPoints[customerId] = 0;
    }
}

void LoyaltyProgram::addPoints(int customerId, double purchaseAmount) {
    if (!isActive) return;
    enrollCustomer(customerId);
    int pointsEarned = static_cast<int>(purchaseAmount * pointsPerDollar);
    customerPoints[customerId] += pointsEarned;
}

bool LoyaltyProgram::redeemPoints(int customerId, int points) {
    auto it = customerPoints.find(customerId);
    if (it == customerPoints.end() || it->second < points) {
        return false;
    }
    it->second -= points;
    return true;
}

int LoyaltyProgram::getCustomerPoints(int customerId) const {
    auto it = customerPoints.find(customerId);
    return it != customerPoints.end() ? it->second : 0;
}

double LoyaltyProgram::getCustomerDiscountRate(int customerId) const {
    int points = getCustomerPoints(customerId);
    if (points > 1000) return 0.15;
    if (points > 500) return 0.10;
    if (points > 200) return 0.05;
    return 0.0;
}

int LoyaltyProgram::getTotalEnrolledCustomers() const {
    return customerPoints.size();
}

void LoyaltyProgram::setIsActive(bool active) {
    isActive = active;
}