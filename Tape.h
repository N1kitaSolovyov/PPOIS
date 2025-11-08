/**
 * @file Tape.h
 * @brief Header file for the Tape class - tape of Post Machine
 * @author Your Name
 * @version 1.0
 */

#ifndef TAPE_H
#define TAPE_H

#include <string>
#include <iostream>
#include "Cell.h"

 /**
  * @class Tape
  * @brief Class implementing the tape of Post Machine
  *
  * The tape represents an infinite sequence of cells in both directions.
  * Supports basic operations: read, write, move left/right.
  * The tape automatically expands when reaching boundaries.
  */
class Tape {
private:
    Cell* head;           ///< Current cell under the head
    Cell* firstCell;      ///< First cell of the tape (for debugging and serialization)
    int headPosition;     ///< Current head position

public:
    /**
     * @brief Default constructor
     * @details Creates a tape with one cell with false value
     */
    Tape();

    /**
     * @brief Destructor
     * @details Frees memory occupied by tape cells
     */
    ~Tape();

    /**
     * @brief Copy constructor
     * @param other Tape to copy from
     */
    Tape(const Tape& other);

    /**
     * @brief Assignment operator
     * @param other Tape to copy from
     * @return Reference to current object
     */
    Tape& operator=(const Tape& other);

    // Basic operations

    /**
     * @brief Load tape from string
     * @param tapeStr String like "10101" (1 - mark, 0 - no mark)
     * @details Spaces and tabs are ignored
     */
    void loadFromString(const std::string& tapeStr);

    /**
     * @brief Convert tape to string
     * @return String representation of tape with current cell highlighted in square brackets
     */
    std::string toString() const;

    /**
     * @brief Move head to the left
     * @details Creates new cell on the left if necessary
     */
    void moveLeft();

    /**
     * @brief Move head to the right
     * @details Creates new cell on the right if necessary
     */
    void moveRight();

    /**
     * @brief Write value to current cell
     * @param value Value to write (true - mark, false - no mark)
     */
    void write(bool value);

    /**
     * @brief Read value from current cell
     * @return Value of current cell
     */
    bool read() const;

    /**
     * @brief Get current head position
     * @return Current head position (relative to initial position)
     */
    int getHeadPosition() const;

    /**
     * @brief Equality comparison operator
     * @param other Tape to compare with
     * @return true if tapes are identical, false otherwise
     */
    bool operator==(const Tape& other) const;

    /**
     * @brief Inequality comparison operator
     * @param other Tape to compare with
     * @return true if tapes are different, false otherwise
     */
    bool operator!=(const Tape& other) const;

    /**
     * @brief Output stream operator
     * @param os Output stream
     * @param tape Tape to output
     * @return Reference to output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Tape& tape);

    /**
     * @brief Input stream operator
     * @param is Input stream
     * @param tape Tape to load
     * @return Reference to input stream
     */
    friend std::istream& operator>>(std::istream& is, Tape& tape);
    void reset();////

private:
    /**
     * @brief Clear tape
     * @details Deletes all cells and resets state
     */
    void clear();

    /**
     * @brief Extend tape to the left
     * @details Creates new cell to the left of the first cell
     */
    void extendLeft();

    /**
     * @brief Extend tape to the right
     * @details Creates new cell to the right of the last cell
     */
    void extendRight();
};

#endif