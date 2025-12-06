#pragma once
#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <ctime>

class Expense {
private:
    int expenseId;
    std::string category;
    double amount;
    std::string description;
    std::time_t date;
    std::string vendor;

public:
    Expense(int expenseId, const std::string& category, double amount,
        const std::string& description, const std::string& vendor = "");

    // Геттеры
    int getExpenseId() const;
    std::string getCategory() const;
    double getAmount() const;
    std::string getDescription() const;
    std::time_t getDate() const;
    std::string getVendor() const;

    bool isOverBudget(double budgetLimit) const;
};

#endif