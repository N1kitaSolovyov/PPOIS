#include "Table.h"

Table::Table(int number, int capacity)
    : number(number), capacity(capacity), status(TableStatus::FREE) {
}

void Table::setStatus(TableStatus newStatus) {
    status = newStatus;
}

void Table::setCapacity(int newCapacity) {
    capacity = newCapacity;
}

int Table::getNumber() const {
    return number;
}

int Table::getCapacity() const {
    return capacity;
}

TableStatus Table::getStatus() const {
    return status;
}

bool Table::canAccommodate(int guests) const {
    return guests <= capacity;
}