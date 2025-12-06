#include "ExpenseTracker.h"
#include <algorithm>

ExpenseTracker::ExpenseTracker(double totalBudget) : totalBudget(totalBudget) {
    categoryBudgets = { {"food", 3000.0}, {"labor", 4000.0}, {"utilities", 500.0} };
}

void ExpenseTracker::addExpense(const Expense& expense) {
    expenses.push_back(expense);
}

bool ExpenseTracker::removeExpense(int expenseId) {
    auto it = std::remove_if(expenses.begin(), expenses.end(),
        [expenseId](const Expense& expense) {
            return expense.getExpenseId() == expenseId;
        });

    if (it != expenses.end()) {
        expenses.erase(it, expenses.end());
        return true;
    }
    return false;
}

double ExpenseTracker::getTotalExpenses() const {
    double total = 0.0;
    for (const auto& expense : expenses) {
        total += expense.getAmount();
    }
    return total;
}

double ExpenseTracker::getCategoryExpenses(const std::string& category) const {
    double total = 0.0;
    for (const auto& expense : expenses) {
        if (expense.getCategory() == category) {
            total += expense.getAmount();
        }
    }
    return total;
}

double ExpenseTracker::getRemainingBudget() const {
    return totalBudget - getTotalExpenses();
}

void ExpenseTracker::setCategoryBudget(const std::string& category, double budget) {
    categoryBudgets[category] = budget;
}

void ExpenseTracker::setTotalBudget(double budget) {
    if (budget > 0) totalBudget = budget;
}