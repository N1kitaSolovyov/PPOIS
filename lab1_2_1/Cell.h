/**
 * @file Cell.h
 * @brief Header file for the Cell class - tape cell of Post Machine
 * @author Your Name
 * @version 1.0
 */

#ifndef CELL_H
#define CELL_H

 /**
  * @class Cell
  * @brief Class representing a cell of Post Machine tape
  *
  * Each cell contains a value (mark) and pointers to previous and next cells.
  * Cells are organized in a doubly-linked list to implement infinite tape.
  */
class Cell {
public:
    bool value;    ///< Cell value (true - mark, false - no mark)
    Cell* prev;    ///< Pointer to previous cell
    Cell* next;    ///< Pointer to next cell

    /**
     * @brief Cell constructor
     * @param val Cell value (default false)
     * @param p Pointer to previous cell (default nullptr)
     * @param n Pointer to next cell (default nullptr)
     */
    Cell(bool val = false, Cell* p = nullptr, Cell* n = nullptr);
};

#endif