#include "Payment.h"
#include <iostream>

Payment::Payment(int paymentId, int orderId, double amount, PaymentMethod method)
    : paymentId(paymentId), orderId(orderId), amount(amount), method(method),
    status(PaymentStatus::PENDING) {
    paymentDate = std::time(nullptr);
}

bool Payment::processPayment() {
    switch (method) {
    case PaymentMethod::CASH:
        status = PaymentStatus::COMPLETED;
        break;
    case PaymentMethod::CREDIT_CARD:
    case PaymentMethod::DEBIT_CARD:
        status = PaymentStatus::COMPLETED;
        transactionId = "TXN_" + std::to_string(paymentId);
        break;
    case PaymentMethod::MOBILE_PAYMENT:
        status = PaymentStatus::COMPLETED;
        break;
    }
    return status == PaymentStatus::COMPLETED;
}

bool Payment::refundPayment() {
    if (status == PaymentStatus::COMPLETED) {
        status = PaymentStatus::REFUNDED;
        return true;
    }
    return false;
}

int Payment::getPaymentId() const { return paymentId; }
int Payment::getOrderId() const { return orderId; }
double Payment::getAmount() const { return amount; }
PaymentMethod Payment::getMethod() const { return method; }
PaymentStatus Payment::getStatus() const { return status; }
std::time_t Payment::getPaymentDate() const { return paymentDate; }
std::string Payment::getTransactionId() const { return transactionId; }