#include "Tape.h"
#include <sstream>
#include <stdexcept>

Tape::Tape() : head(nullptr), firstCell(nullptr), headPosition(0) {
    head = new Cell(false);
    firstCell = head;
    headPosition = 0;
}

Tape::~Tape() {
    clear();
}

void Tape::clear() {
    Cell* current = firstCell;
    while (current != nullptr) {
        Cell* next = current->next;
        delete current;
        current = next;
    }
    firstCell = head = nullptr;
    headPosition = 0;
}

Tape::Tape(const Tape& other) : head(nullptr), firstCell(nullptr), headPosition(other.headPosition) {
    if (other.firstCell == nullptr) return;

    Cell* otherCurrent = other.firstCell;
    Cell* newCurrent = new Cell(otherCurrent->value);
    firstCell = newCurrent;

    Cell* prevCell = newCurrent;
    otherCurrent = otherCurrent->next;

    while (otherCurrent != nullptr) {
        Cell* newCell = new Cell(otherCurrent->value, prevCell);
        prevCell->next = newCell;
        prevCell = newCell;

        if (otherCurrent == other.head) {
            head = newCell;
        }

        otherCurrent = otherCurrent->next;
    }

    if (head == nullptr) {
        head = firstCell;
    }
}

Tape& Tape::operator=(const Tape& other) {
    if (this != &other) {
        clear();
        headPosition = other.headPosition;

        if (other.firstCell != nullptr) {
            Cell* otherCurrent = other.firstCell;
            Cell* newCurrent = new Cell(otherCurrent->value);
            firstCell = newCurrent;

            Cell* prevCell = newCurrent;
            otherCurrent = otherCurrent->next;

            while (otherCurrent != nullptr) {
                Cell* newCell = new Cell(otherCurrent->value, prevCell);
                prevCell->next = newCell;
                prevCell = newCell;

                if (otherCurrent == other.head) {
                    head = newCell;
                }

                otherCurrent = otherCurrent->next;
            }

            if (head == nullptr) {
                head = firstCell;
            }
        }
    }
    return *this;
}

void Tape::loadFromString(const std::string& tapeStr) {
    clear();

    if (tapeStr.empty()) {
        head = new Cell(false);
        firstCell = head;
        headPosition = 0;
        return;
    }

    std::string cleanStr;
    for (char c : tapeStr) {
        if (c != ' ' && c != '\t' && c != '\r' && c != '\n') {
            cleanStr += c;
        }
    }

    if (cleanStr.empty()) {
        head = new Cell(false);
        firstCell = head;
        headPosition = 0;
        return;
    }

    firstCell = new Cell(cleanStr[0] == '1');
    head = firstCell;
    headPosition = 0;

    Cell* current = firstCell;
    for (size_t i = 1; i < cleanStr.length(); i++) {
        char c = cleanStr[i];
        Cell* newCell = new Cell(c == '1', current);
        current->next = newCell;
        current = newCell;
    }
}

std::string Tape::toString() const {
    if (firstCell == nullptr) {
        return "[0]";
    }

    std::stringstream ss;
    Cell* current = firstCell;
    int position = 0;

    while (current != nullptr) {
        if (current == head) {
            ss << "[" << (current->value ? "1" : "0") << "]";
        }
        else {
            ss << (current->value ? "1" : "0");
        }

        if (current->next != nullptr) {
            ss << " ";
        }

        current = current->next;
        position++;
    }

    return ss.str();
}

void Tape::moveLeft() {
    if (head->prev == nullptr) {
        Cell* newCell = new Cell(false, nullptr, firstCell);
        firstCell->prev = newCell;
        firstCell = newCell;
    }
    head = head->prev;
    headPosition--;
}

void Tape::moveRight() {
    if (head->next == nullptr) {
        Cell* newCell = new Cell(false, head);
        head->next = newCell;
    }
    head = head->next;
    headPosition++;
}

void Tape::write(bool value) {
    if (head != nullptr) {
        head->value = value;
    }
}

bool Tape::read() const {
    return head != nullptr ? head->value : false;
}

int Tape::getHeadPosition() const {
    return headPosition;
}

bool Tape::operator==(const Tape& other) const {
    if (headPosition != other.headPosition) return false;

    Cell* current1 = firstCell;
    Cell* current2 = other.firstCell;

    while (current1 != nullptr && current2 != nullptr) {
        if (current1->value != current2->value) return false;
        current1 = current1->next;
        current2 = current2->next;
    }

    while (current1 != nullptr) {
        if (current1->value) return false;
        current1 = current1->next;
    }

    while (current2 != nullptr) {
        if (current2->value) return false;
        current2 = current2->next;
    }

    return true;
}

bool Tape::operator!=(const Tape& other) const {
    return !(*this == other);
}

void Tape::extendLeft() {
    Cell* newCell = new Cell(false, nullptr, firstCell);
    if (firstCell != nullptr) {
        firstCell->prev = newCell;
    }
    firstCell = newCell;
}

void Tape::extendRight() {
    Cell* last = firstCell;
    while (last != nullptr && last->next != nullptr) {
        last = last->next;
    }

    if (last != nullptr) {
        Cell* newCell = new Cell(false, last);
        last->next = newCell;
    }
}

std::ostream& operator<<(std::ostream& os, const Tape& tape) {
    os << tape.toString();
    return os;
}

std::istream& operator>>(std::istream& is, Tape& tape) {
    std::string tapeStr;
    std::getline(is, tapeStr);
    tape.loadFromString(tapeStr);
    return is;
}
void Tape::reset() {
    // Сбрасываем позицию головки в начало
    headPosition = 0;

    // Находим первую ячейку и устанавливаем головку на нее
    head = firstCell;

    // Альтернативная реализация - если нужно полностью пересоздать ленту:
    // std::string currentState = toString();
    // loadFromString(currentState);
}