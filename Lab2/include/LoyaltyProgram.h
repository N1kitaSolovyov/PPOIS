#pragma once
#ifndef LOYALTY_PROGRAM_H
#define LOYALTY_PROGRAM_H

#include "Customer.h"
#include <map>

class LoyaltyProgram {
private:
    std::map<int, int> customerPoints; // customerId -> points
    double pointsPerDollar;
    bool isActive;

public:
    LoyaltyProgram(double pointsRate = 1.0);

    void enrollCustomer(int customerId);
    void addPoints(int customerId, double purchaseAmount);
    bool redeemPoints(int customerId, int points);
    int getCustomerPoints(int customerId) const;
    double getCustomerDiscountRate(int customerId) const;

    int getTotalEnrolledCustomers() const;
    void setIsActive(bool active);
};

#endif