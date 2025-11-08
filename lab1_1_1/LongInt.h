#pragma once
#ifndef LONGINT_H
#define LONGINT_H

#include <iostream>
#include <vector>
#include <string>

/**
 * @class LongInt
 * @brief Arbitrary precision integer implementation
 *
 * @details The LongInt class provides support for integers of arbitrary size,
 * overcoming the limitations of built-in integer types. It supports all basic
 * arithmetic operations, comparison operators, and input/output operations.
 *
 * @note Numbers are stored in base-10 format with digits stored in a vector
 * from most significant to least significant digit.
 *
 * @warning Division by zero throws std::invalid_argument exception
 *
 * @example examples/basic_usage.cpp
 * @example examples/large_numbers.cpp
 */
class LongInt {
private:
    std::vector<int> digits;      ///< Vector of digits (most significant first)
    bool isNegative;              ///< Sign flag (true for negative, false for positive)

    /**
     * @brief Removes leading zeros from the digit vector
     *
     * @details This internal method ensures that the number representation
     * is canonical by removing any leading zeros. The number zero is
     * represented as a single digit 0.
     *
     * @post After calling this method, either digits.size() == 1 and digits[0] == 0,
     * or digits[0] != 0
     */
    void removeLeadingZeros();

    /**
     * @brief Compares absolute values of two numbers
     *
     * @param other Second number for comparison
     * @return int Comparison result:
     *   - -1 if |this| < |other|
     *   - 0 if |this| == |other|
     *   - 1 if |this| > |other|
     *
     * @details Compares numbers without considering sign, used
     * internally for implementing comparison operators and arithmetic operations
     */
    int compareAbsolute(const LongInt& other) const;

    /**
     * @brief Returns absolute value of the number
     *
     * @return LongInt Number with same magnitude but positive sign
     *
     * @note For zero, returns positive zero
     */
    LongInt absoluteValue() const;

    /**
     * @brief Subtracts absolute values of two numbers
     *
     * @param other Subtrahend
     * @return LongInt Result of subtraction |this| - |other|
     *
     * @pre Assumes that |this| >= |other|
     * @details Internal method for implementing arithmetic operations.
     * Uses standard subtraction algorithm with borrowing.
     */
    LongInt subtractAbsolute(const LongInt& other) const;

public:
    // ============================
    // CONSTRUCTORS AND DESTRUCTOR
    // ============================

    /**
     * @brief Default constructor
     *
     * @details Creates the number 0. Initializes digits with vector {0}
     * and sets isNegative to false.
     *
     * @post *this == LongInt(0)
     */
    LongInt();

    /**
     * @brief Constructor from string
     *
     * @param str String representation of the number
     *
     * @details Converts string to long integer.
     * String may contain:
     * - Digits from '0' to '9'
     * - Optional minus sign at the beginning for negative numbers
     * - Leading zeros (automatically removed)
     *
     * @throw std::invalid_argument If string contains invalid characters
     *
     * @note Examples:
     * - "123" creates number 123
     * - "-456" creates number -456
     * - "000123" automatically converts to 123
     * - "12a34" throws std::invalid_argument
     */
    LongInt(const std::string& str);

    /**
     * @brief Constructor from standard integer
     *
     * @param num Integer to convert
     *
     * @details Creates LongInt based on standard int.
     * Supports both positive and negative numbers.
     * Number 0 is created specially as single digit 0.
     *
     * @post *this == LongInt(std::to_string(num))
     */
    LongInt(int num);

    /**
     * @brief Copy constructor
     *
     * @param other Object to copy
     *
     * @details Creates a deep copy of the other object.
     * Necessary for correct work with STL containers
     * and when passing objects by value.
     *
     * @post *this == other
     */
    LongInt(const LongInt& other);

    // ============================
    // CONVERSION METHODS
    // ============================

    /**
     * @brief Converts number to string
     *
     * @return std::string String representation of the number
     *
     * @details Returns number as string with sign consideration.
     * For negative numbers adds minus sign at the beginning.
     *
     * @note For number -123 returns string "-123"
     * @note For number 0 returns "0" (without sign)
     */
    std::string toString() const;

    /**
     * @brief Checks if number is zero
     *
     * @return true If number equals 0
     * @return false If number doesn't equal 0
     *
     * @details Zero is defined as number with single digit 0
     * and positive sign. Both LongInt(0) and LongInt("-0") are considered zero.
     */
    bool isZero() const;

    /**
     * @brief Conversion operator to int type
     *
     * @return int Standard integer
     *
     * @details Allows using LongInt where int is expected.
     * May cause overflow if number is too large for int.
     *
     * @warning When converting numbers exceeding INT_MAX or below INT_MIN,
     * the result is undefined behavior (typically overflow)
     */
    operator int() const;

    // ============================
    // ASSIGNMENT OPERATORS
    // ============================

    /**
     * @brief Assignment operator
     *
     * @param other Object to copy
     * @return LongInt& Reference to current object
     *
     * @details Creates a deep copy of the other object.
     * Correctly handles self-assignment.
     *
     * @post *this == other
     */
    LongInt& operator=(const LongInt& other);

    // ============================
    // COMPARISON OPERATORS
    // ============================

    /**
     * @brief Equality operator for LongInt
     *
     * @param other Second number for comparison
     * @return true If numbers are equal
     * @return false If numbers are not equal
     *
     * @details Compares both sign and absolute value of numbers.
     * Considers special case with zero (0 == -0).
     *
     * @note LongInt(5) == LongInt(5) returns true
     * @note LongInt(5) == LongInt(-5) returns false
     * @note LongInt(0) == LongInt("-0") returns true
     */
    bool operator==(const LongInt& other) const;

    /**
     * @brief Inequality operator for LongInt
     *
     * @param other Second number for comparison
     * @return true If numbers are not equal
     * @return false If numbers are equal
     *
     * @see operator==
     */
    bool operator!=(const LongInt& other) const;

    /**
     * @brief Less than operator for LongInt
     *
     * @param other Second number for comparison
     * @return true If this < other
     * @return false If this >= other
     *
     * @details Considers signs of numbers. Negative numbers are considered smaller.
     * Zero is greater than any negative number and smaller than any positive number.
     *
     * @note LongInt(-5) < LongInt(0) returns true
     * @note LongInt(0) < LongInt(5) returns true
     * @note LongInt(3) < LongInt(5) returns true
     */
    bool operator<(const LongInt& other) const;

    /**
     * @brief Greater than operator for LongInt
     *
     * @param other Second number for comparison
     * @return true If this > other
     * @return false If this <= other
     *
     * @see operator<
     */
    bool operator>(const LongInt& other) const;

    /**
     * @brief Less than or equal operator for LongInt
     *
     * @param other Second number for comparison
     * @return true If this <= other
     * @return false If this > other
     *
     * @see operator<
     */
    bool operator<=(const LongInt& other) const;

    /**
     * @brief Greater than or equal operator for LongInt
     *
     * @param other Second number for comparison
     * @return true If this >= other
     * @return false If this < other
     *
     * @see operator<
     */
    bool operator>=(const LongInt& other) const;

    // ----------------------------
    // Comparison operators with int
    // ----------------------------

    /**
     * @brief Equality operator with int
     *
     * @param other Integer for comparison
     * @return true If numbers are equal
     * @return false If numbers are not equal
     *
     * @details Creates temporary LongInt and uses operator==(const LongInt&)
     *
     * @note LongInt(123) == 123 returns true
     */
    bool operator==(int other) const;

    /**
     * @brief Inequality operator with int
     *
     * @param other Integer for comparison
     * @return true If numbers are not equal
     * @return false If numbers are equal
     *
     * @see operator!=(const LongInt&)
     */
    bool operator!=(int other) const;

    /**
     * @brief Less than operator with int
     *
     * @param other Integer for comparison
     * @return true If this < other
     * @return false If this >= other
     *
     * @see operator<(const LongInt&)
     */
    bool operator<(int other) const;

    /**
     * @brief Greater than operator with int
     *
     * @param other Integer for comparison
     * @return true If this > other
     * @return false If this <= other
     *
     * @see operator>(const LongInt&)
     */
    bool operator>(int other) const;

    /**
     * @brief Less than or equal operator with int
     *
     * @param other Integer for comparison
     * @return true If this <= other
     * @return false If this > other
     *
     * @see operator<=(const LongInt&)
     */
    bool operator<=(int other) const;

    /**
     * @brief Greater than or equal operator with int
     *
     * @param other Integer for comparison
     * @return true If this >= other
     * @return false If this < other
     *
     * @see operator>=(const LongInt&)
     */
    bool operator>=(int other) const;

    // ============================
    // ARITHMETIC OPERATORS
    // ============================

    /**
     * @brief Addition operator for two LongInt
     *
     * @param other Second addend
     * @return LongInt Result of addition
     *
     * @details Correctly handles addition of numbers with different signs.
     * In this case, subtraction of absolute values is actually performed.
     * Uses standard addition algorithm with carry.
     *
     * @note LongInt(5) + LongInt(3) returns LongInt(8)
     * @note LongInt(5) + LongInt(-3) returns LongInt(2)
     * @note LongInt(-5) + LongInt(3) returns LongInt(-2)
     */
    LongInt operator+(const LongInt& other) const;

    /**
     * @brief Subtraction operator for two LongInt
     *
     * @param other Subtrahend
     * @return LongInt Result of subtraction
     *
     * @details Correctly handles subtraction of numbers with different signs.
     * In this case, addition of absolute values is actually performed.
     *
     * @note LongInt(5) - LongInt(3) returns LongInt(2)
     * @note LongInt(5) - LongInt(-3) returns LongInt(8)
     * @note LongInt(-5) - LongInt(3) returns LongInt(-8)
     */
    LongInt operator-(const LongInt& other) const;

    /**
     * @brief Multiplication operator for two LongInt
     *
     * @param other Second factor
     * @return LongInt Result of multiplication
     *
     * @details Uses the "column multiplication" algorithm.
     * Result sign is determined by the sign rule (positive if signs same,
     * negative if signs different).
     *
     * @note LongInt(5) * LongInt(3) returns LongInt(15)
     * @note LongInt(5) * LongInt(-3) returns LongInt(-15)
     * @note LongInt(0) * LongInt(123) returns LongInt(0)
     */
    LongInt operator*(const LongInt& other) const;

    /**
     * @brief Division operator for two LongInt
     *
     * @param other Divisor
     * @return LongInt Result of division
     *
     * @throw std::invalid_argument If other == 0 (division by zero)
     *
     * @details Uses the "long division" algorithm.
     * Result sign is determined by the sign rule.
     * Fractional part is discarded (integer division).
     *
     * @note LongInt(10) / LongInt(3) returns LongInt(3)
     * @note LongInt(10) / LongInt(-3) returns LongInt(-3)
     * @note LongInt(-10) / LongInt(3) returns LongInt(-3)
     */
    LongInt operator/(const LongInt& other) const;

    // ============================
    // COMPOUND ASSIGNMENT OPERATORS
    // ============================

    /**
     * @brief Addition assignment operator for LongInt
     *
     * @param other Second addend
     * @return LongInt& Reference to modified current object
     *
     * @see operator+
     * @post *this = old_this + other
     */
    LongInt& operator+=(const LongInt& other);

    /**
     * @brief Subtraction assignment operator for LongInt
     *
     * @param other Subtrahend
     * @return LongInt& Reference to modified current object
     *
     * @see operator-
     * @post *this = old_this - other
     */
    LongInt& operator-=(const LongInt& other);

    /**
     * @brief Multiplication assignment operator for LongInt
     *
     * @param other Second factor
     * @return LongInt& Reference to modified current object
     *
     * @see operator*
     * @post *this = old_this * other
     */
    LongInt& operator*=(const LongInt& other);

    /**
     * @brief Division assignment operator for LongInt
     *
     * @param other Divisor
     * @return LongInt& Reference to modified current object
     *
     * @throw std::invalid_argument If other == 0 (division by zero)
     * @see operator/
     * @post *this = old_this / other
     */
    LongInt& operator/=(const LongInt& other);

    // ============================
    // OPERATORS WITH INT
    // ============================

    /**
     * @brief Addition operator with int
     *
     * @param other Integer addend
     * @return LongInt Result of addition
     *
     * @details Creates temporary LongInt and uses operator+(const LongInt&)
     */
    LongInt operator+(int other) const;

    /**
     * @brief Subtraction operator with int
     *
     * @param other Integer subtrahend
     * @return LongInt Result of subtraction
     *
     * @details Creates temporary LongInt and uses operator-(const LongInt&)
     */
    LongInt operator-(int other) const;

    /**
     * @brief Multiplication operator with int
     *
     * @param other Integer factor
     * @return LongInt Result of multiplication
     *
     * @details Creates temporary LongInt and uses operator*(const LongInt&)
     */
    LongInt operator*(int other) const;

    /**
     * @brief Division operator with int
     *
     * @param other Integer divisor
     * @return LongInt Result of division
     *
     * @throw std::invalid_argument If other == 0 (division by zero)
     * @details Creates temporary LongInt and uses operator/(const LongInt&)
     */
    LongInt operator/(int other) const;

    /**
     * @brief Addition assignment operator with int
     *
     * @param other Integer addend
     * @return LongInt& Reference to modified current object
     *
     * @see operator+=(const LongInt&)
     */
    LongInt& operator+=(int other);

    /**
     * @brief Subtraction assignment operator with int
     *
     * @param other Integer subtrahend
     * @return LongInt& Reference to modified current object
     *
     * @see operator-=(const LongInt&)
     */
    LongInt& operator-=(int other);

    /**
     * @brief Multiplication assignment operator with int
     *
     * @param other Integer factor
     * @return LongInt& Reference to modified current object
     *
     * @see operator*=(const LongInt&)
     */
    LongInt& operator*=(int other);

    /**
     * @brief Division assignment operator with int
     *
     * @param other Integer divisor
     * @return LongInt& Reference to modified current object
     *
     * @throw std::invalid_argument If other == 0 (division by zero)
     * @see operator/=(const LongInt&)
     */
    LongInt& operator/=(int other);

    // ============================
    // INCREMENT AND DECREMENT
    // ============================

    /**
     * @brief Prefix increment
     *
     * @return LongInt& Reference to modified object
     *
     * @details Increases number by 1. Returns reference to modified object.
     *
     * @note Example: ++a (modifies a and returns modified value)
     * @post *this = old_this + 1
     */
    LongInt& operator++();

    /**
     * @brief Postfix increment
     *
     * @param int Dummy parameter to distinguish prefix and postfix versions
     * @return LongInt Copy of object before increment
     *
     * @details Increases number by 1. Returns copy of object before increment.
     *
     * @note Example: a++ (returns old value, then increments a)
     * @post *this = old_this + 1
     */
    LongInt operator++(int);

    /**
     * @brief Prefix decrement
     *
     * @return LongInt& Reference to modified object
     *
     * @details Decreases number by 1. Returns reference to modified object.
     *
     * @note Example: --a (modifies a and returns modified value)
     * @post *this = old_this - 1
     */
    LongInt& operator--();

    /**
     * @brief Postfix decrement
     *
     * @param int Dummy parameter to distinguish prefix and postfix versions
     * @return LongInt Copy of object before decrement
     *
     * @details Decreases number by 1. Returns copy of object before decrement.
     *
     * @note Example: a-- (returns old value, then decrements a)
     * @post *this = old_this - 1
     */
    LongInt operator--(int);

    // ============================
    // FRIEND OPERATORS
    // ============================

    /**
     * @brief Output stream operator
     *
     * @param os Output stream
     * @param num Number to output
     * @return std::ostream& Reference to stream
     *
     * @details Outputs number to stream in string representation.
     * Uses toString() method for conversion.
     *
     * @note Format is same as toString(): "-123" for negative, "123" for positive
     */
    friend std::ostream& operator<<(std::ostream& os, const LongInt& num);

    /**
     * @brief Input stream operator
     *
     * @param is Input stream
     * @param num Number to input
     * @return std::istream& Reference to stream
     *
     * @details Reads string from stream and converts it to LongInt.
     * Expects numeric format (digits and optional minus sign).
     * Skips leading whitespace, reads until first non-digit character.
     *
     * @throw std::invalid_argument If input format is invalid
     */
    friend std::istream& operator>>(std::istream& is, LongInt& num);
};

// ============================
// NON-MEMBER OPERATORS
// ============================

/**
 * @brief Addition operator (int + LongInt)
 * @param lhs Left integer operand
 * @param rhs Right LongInt operand
 * @return LongInt Result of addition
 */
LongInt operator+(int lhs, const LongInt& rhs);

/**
 * @brief Subtraction operator (int - LongInt)
 * @param lhs Left integer operand
 * @param rhs Right LongInt operand
 * @return LongInt Result of subtraction
 */
LongInt operator-(int lhs, const LongInt& rhs);

/**
 * @brief Multiplication operator (int * LongInt)
 * @param lhs Left integer operand
 * @param rhs Right LongInt operand
 * @return LongInt Result of multiplication
 */
LongInt operator*(int lhs, const LongInt& rhs);

/**
 * @brief Division operator (int / LongInt)
 * @param lhs Left integer operand
 * @param rhs Right LongInt operand
 * @return LongInt Result of division
 *
 * @throw std::invalid_argument If rhs == 0 (division by zero)
 */
LongInt operator/(int lhs, const LongInt& rhs);

#endif // LONGINT_H