/**
 * @file PostProgram.h
 * @brief Header file for the PostProgram class - program for Post Machine
 * @author Your Name
 * @version 1.0
 */

#ifndef POSTPROGRAM_H
#define POSTPROGRAM_H

#include <vector>
#include <string>
#include <iostream>

 /**
  * @struct Command
  * @brief Structure representing a command of Post Machine
  *
  * Contains command number, type and transitions for conditional commands
  */
struct Command {
    int number;     ///< Command number
    char type;      ///< Command type: R, L, V, X, ?, !
    int next1;      ///< Next command (for R,L,V,X) or for true condition (for ?)
    int next2;      ///< Next command for false condition (only for ?)
};

/**
 * @class PostProgram
 * @brief Class implementing the program of Post Machine
 *
 * The program is a set of commands executed by the machine.
 * Supports loading from file, adding, removing commands and finding next commands.
 */
class PostProgram {
private:
    std::vector<Command> commands;  ///< Vector of program commands

public:
    /**
     * @brief Add command to program
     * @param number Command number
     * @param type Command type (R, L, V, X, ?, !)
     * @param next1 Next command (for R,L,V,X) or for true condition (for ?)
     * @param next2 Next command for false condition (only for ?)
     */
    void addCommand(int number, char type, int next1 = -1, int next2 = -1);

    /**
     * @brief Remove command by number
     * @param number Command number to remove
     */
    void removeCommand(int number);

    /**
     * @brief Check if command with given number exists
     * @param number Command number
     * @return true if command exists, false otherwise
     */
    bool hasCommand(int number) const;

    /**
     * @brief Clear program (remove all commands)
     */
    void clearCommands();

    /**
     * @brief Get command type by number
     * @param number Command number
     * @return Command type
     * @throw std::runtime_error if command not found
     */
    char getCommandType(int number) const;

    /**
     * @brief Get next command based on condition
     * @param number Current command number
     * @param hasMark Condition value (for '?' command - has mark or not)
     * @return Next command number or -1 for stop
     * @throw std::runtime_error if command not found
     */
    int getNextCommand(int number, bool hasMark) const;

    /**
     * @brief Get list of command numbers
     * @return Vector of command numbers in the program
     */
    std::vector<int> getCommandNumbers() const;

    /**
     * @brief Load program from stream
     * @param is Input stream
     * @details Format: "number: type [next1 [next2]]"
     */
    void loadFromStream(std::istream& is);

    /**
     * @brief Save program to stream
     * @param os Output stream
     */
    void saveToStream(std::ostream& os) const;

    /**
     * @brief Load program from file
     * @param filename File name
     * @throw std::runtime_error If file cannot be opened
     */
    void loadFromFile(const std::string& filename);

    /**
     * @brief Save program to file
     * @param filename File name
     * @throw std::runtime_error If file cannot be created
     */
    void saveToFile(const std::string& filename) const;

    /**
     * @brief Output stream operator
     * @param os Output stream
     * @param program Program to output
     * @return Reference to output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const PostProgram& program);

    /**
     * @brief Input stream operator
     * @param is Input stream
     * @param program Program to load
     * @return Reference to input stream
     */
    friend std::istream& operator>>(std::istream& is, PostProgram& program);
};

#endif