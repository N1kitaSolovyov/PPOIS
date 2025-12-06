#pragma once
#ifndef TABLE_H
#define TABLE_H

enum class TableStatus {
    FREE,
    OCCUPIED,
    RESERVED,
    CLEANING
};

class Table {
private:
    int number;
    int capacity;
    TableStatus status;

public:
    Table(int number, int capacity);

    void setStatus(TableStatus newStatus);
    bool canAccommodate(int guests) const;
    bool isAvailable() const;

    // Getters
    int getNumber() const;
    int getCapacity() const;
    TableStatus getStatus() const;
};

#endif