#include "Expense.h"

Expense::Expense(int expenseId, const std::string& category, double amount,
    const std::string& description, const std::string& vendor)
    : expenseId(expenseId), category(category), amount(amount),
    description(description), vendor(vendor) {
    date = std::time(nullptr);
}

int Expense::getExpenseId() const { return expenseId; }
std::string Expense::getCategory() const { return category; }
double Expense::getAmount() const { return amount; }
std::string Expense::getDescription() const { return description; }
std::time_t Expense::getDate() const { return date; }
std::string Expense::getVendor() const { return vendor; }

bool Expense::isOverBudget(double budgetLimit) const {
    return amount > budgetLimit;
}