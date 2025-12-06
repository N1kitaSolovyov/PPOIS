#pragma once
#ifndef ORDER_STATUS_H
#define ORDER_STATUS_H

enum class OrderStatus {
    CREATED,
    CONFIRMED,
    PREPARING,
    READY,
    SERVED,
    COMPLETED,
    CANCELLED
};

#endif