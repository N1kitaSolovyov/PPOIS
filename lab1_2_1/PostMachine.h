/**
 * @file PostMachine.h
 * @brief Header file for the PostMachine class - main class of Post Machine
 * @author Your Name
 * @version 1.0
 */

#ifndef POSTMACHINE_H
#define POSTMACHINE_H

#include "Tape.h"
#include "PostProgram.h"
#include <string>
#include <iostream>

 /**
  * @class PostMachine
  * @brief Main class implementing the Post Machine
  *
  * Coordinates the work of tape and program, executes commands,
  * tracks execution state. Supports step-by-step execution
  * and execution until program completion.
  */
class PostMachine {
private:
    Tape tape;              ///< Machine tape
    PostProgram program;    ///< Program to execute
    int currentCommand;     ///< Current executing command
    bool halted;           ///< Machine halt flag
    bool logging;          ///< Execution logging flag
    int stepCounter;       ///< Step counter

public:
    /**
     * @brief Default constructor
     * @details Initializes machine to initial state: command 1, halted
     */
    PostMachine();

    /**
     * @brief Load program from file
     * @param filename File name with program
     * @throw std::runtime_error If file cannot be opened
     */
    void loadProgramFromFile(const std::string& filename);

    /**
     * @brief Load program from stream
     * @param is Input stream with program
     */
    void loadProgramFromStream(std::istream& is);

    /**
     * @brief Load tape from string
     * @param tapeStr String with initial tape state
     */
    void loadTapeFromString(const std::string& tapeStr);

    /**
     * @brief Load tape from stream
     * @param is Input stream with tape state
     */
    void loadTapeFromStream(std::istream& is);

    /**
     * @brief Start program execution
     * @details Executes program until completion or halt
     */
    void run();

    /**
     * @brief Execute one program step
     * @return true if execution continues, false if completed
     */
    bool step();

    /**
     * @brief Reset machine to initial state
     * @note Does not reset tape state, only counters and command pointer
     */
    void reset();

    /**
     * @brief Get string representation of tape
     * @return String with current tape state
     */
    std::string getTapeString() const;

    /**
     * @brief Get machine state information
     * @return Multi-line string with full state information
     */
    std::string getStateInfo() const;

    /**
     * @brief Check if machine is halted
     * @return true if machine is halted, false otherwise
     */
    bool isHalted() const;

    /**
     * @brief Get current command
     * @return Number of current executing command
     */
    int getCurrentCommand() const;

    /**
     * @brief Add command to program
     * @param number Command number
     * @param type Command type (R, L, V, X, ?, !)
     * @param next1 Next command (for R,L,V,X) or for true condition (for ?)
     * @param next2 Next command for false condition (only for ?)
     */
    void addCommand(int number, char type, int next1 = -1, int next2 = -1);

    /**
     * @brief Remove command from program
     * @param number Command number to remove
     */
    void removeCommand(int number);

    /**
     * @brief Check if command exists
     * @param number Command number to check
     * @return true if command exists, false otherwise
     */
    bool hasCommand(int number) const;

    /**
     * @brief Enable/disable logging
     * @param enable true - enable logging, false - disable
     */
    void setLogging(bool enable);

    /**
     * @brief Output stream operator
     * @param os Output stream
     * @param machine Machine to output
     * @return Reference to output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const PostMachine& machine);

    /**
     * @brief Input stream operator
     * @param is Input stream
     * @param machine Machine to load
     * @return Reference to input stream
     */
    friend std::istream& operator>>(std::istream& is, PostMachine& machine);
};


#endif