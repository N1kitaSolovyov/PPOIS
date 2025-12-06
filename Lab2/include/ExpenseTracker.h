#pragma once
#ifndef EXPENSE_TRACKER_H
#define EXPENSE_TRACKER_H

#include "Expense.h"
#include <vector>
#include <map>

class ExpenseTracker {
private:
    std::vector<Expense> expenses;
    std::map<std::string, double> categoryBudgets;
    double totalBudget;

public:
    ExpenseTracker(double totalBudget = 10000.0);

    void addExpense(const Expense& expense);
    bool removeExpense(int expenseId);
    double getTotalExpenses() const;
    double getCategoryExpenses(const std::string& category) const;
    double getRemainingBudget() const;

    void setCategoryBudget(const std::string& category, double budget);
    void setTotalBudget(double budget);
};

#endif