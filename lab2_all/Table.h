#pragma once
#ifndef TABLE_H
#define TABLE_H

enum class TableStatus {
    FREE,
    OCCUPIED,
    RESERVED
};

class Table {
private:
    int number;
    int capacity;
    TableStatus status;

public:
    Table(int number, int capacity);

    // Управление состоянием
    void setStatus(TableStatus newStatus);
    void setCapacity(int newCapacity);

    // Геттеры
    int getNumber() const;
    int getCapacity() const;
    TableStatus getStatus() const;

    // Простая проверка данных
    bool canAccommodate(int guests) const;
};

#endif