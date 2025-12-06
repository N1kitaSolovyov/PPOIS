#pragma once
#ifndef RESTAURANT_EXCEPTIONS_H
#define RESTAURANT_EXCEPTIONS_H

#include <stdexcept>
#include <string>

class InsufficientFundsException : public std::runtime_error {
public:
    InsufficientFundsException() : std::runtime_error("Недостаточно средств") {}
};

class InvalidPasswordException : public std::runtime_error {
public:
    InvalidPasswordException() : std::runtime_error("Неверный пароль") {}
};

class TableNotAvailableException : public std::runtime_error {
public:
    TableNotAvailableException() : std::runtime_error("Стол недоступен") {}
};

class ReservationConflictException : public std::runtime_error {
public:
    ReservationConflictException() : std::runtime_error("Конфликт брони") {}
};

class OrderProcessingException : public std::runtime_error {
public:
    OrderProcessingException() : std::runtime_error("Ошибка заказа") {}
};

class InventoryShortageException : public std::runtime_error {
public:
    InventoryShortageException() : std::runtime_error("Недостаток ингредиентов") {}
};

class PaymentFailedException : public std::runtime_error {
public:
    PaymentFailedException() : std::runtime_error("Ошибка платежа") {}
};

class CustomerNotFoundException : public std::runtime_error {
public:
    CustomerNotFoundException() : std::runtime_error("Клиент не найден") {}
};

class EmployeeNotAvailableException : public std::runtime_error {
public:
    EmployeeNotAvailableException() : std::runtime_error("Сотрудник недоступен") {}
};

class MenuItemUnavailableException : public std::runtime_error {
public:
    MenuItemUnavailableException() : std::runtime_error("Блюдо недоступно") {}
};

class DiscountExpiredException : public std::runtime_error {
public:
    DiscountExpiredException() : std::runtime_error("Скидка истекла") {}
};

class KitchenOverloadException : public std::runtime_error {
public:
    KitchenOverloadException() : std::runtime_error("Кухня перегружена") {}
};

#endif