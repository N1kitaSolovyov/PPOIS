#include "Cell.h"

Cell::Cell(bool val, Cell* p, Cell* n)
    : value(val), prev(p), next(n) {
}