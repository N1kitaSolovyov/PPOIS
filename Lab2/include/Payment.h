#pragma once
#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <ctime>

enum class PaymentMethod { CASH, CREDIT_CARD, DEBIT_CARD, MOBILE_PAYMENT };
enum class PaymentStatus { PENDING, COMPLETED, FAILED, REFUNDED };

class Payment {
private:
    int paymentId;
    int orderId;
    double amount;
    PaymentMethod method;
    PaymentStatus status;
    std::time_t paymentDate;
    std::string transactionId;

public:
    Payment(int paymentId, int orderId, double amount, PaymentMethod method);

    bool processPayment();
    bool refundPayment();

    // Геттеры
    int getPaymentId() const;
    int getOrderId() const;
    double getAmount() const;
    PaymentMethod getMethod() const;
    PaymentStatus getStatus() const;
    std::time_t getPaymentDate() const;
    std::string getTransactionId() const;
};

#endif