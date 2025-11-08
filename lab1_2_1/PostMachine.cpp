#include "PostMachine.h"

PostMachine::PostMachine()
    : currentCommand(1), halted(false), logging(false), stepCounter(0) {
}

void PostMachine::loadProgramFromFile(const std::string& filename) {
    program.loadFromFile(filename);
    reset();
}

void PostMachine::loadProgramFromStream(std::istream& is) {
    program.loadFromStream(is);
    reset();
}

void PostMachine::loadTapeFromString(const std::string& tapeStr) {
    tape.loadFromString(tapeStr);
}

void PostMachine::loadTapeFromStream(std::istream& is) {
    is >> tape;
}

void PostMachine::run() {
    halted = false;
    while (step()) {
    }
}

bool PostMachine::step() {
    if (halted) return false;

    if (!program.hasCommand(currentCommand)) {
        halted = true;
        return false;
    }

    char type = program.getCommandType(currentCommand);
    int nextCmd = currentCommand;

    switch (type) {
    case 'R':
        tape.moveRight();
        nextCmd = program.getNextCommand(currentCommand, false);
        break;
    case 'L':
        tape.moveLeft();
        nextCmd = program.getNextCommand(currentCommand, false);
        break;
    case 'V':
        tape.write(true);
        nextCmd = program.getNextCommand(currentCommand, false);
        break;
    case 'X':
        tape.write(false);
        nextCmd = program.getNextCommand(currentCommand, false);
        break;
    case '?':
        nextCmd = program.getNextCommand(currentCommand, tape.read());
        break;
    case '!':
        halted = true;
        nextCmd = -1;
        break;
    }

    if (logging) {
        std::cout << "Step " << (stepCounter + 1) << ": ";
        std::cout << "Command " << currentCommand << " (" << type << ")";
        std::cout << " -> " << nextCmd;
        std::cout << " | Tape: " << tape.toString();
        std::cout << " | Head: " << tape.getHeadPosition() << std::endl;
    }

    if (!halted) {
        if (nextCmd > 0 && program.hasCommand(nextCmd)) {
            currentCommand = nextCmd;
        }
        else {
            halted = true;
        }
    }

    stepCounter++;
    return !halted;
}

void PostMachine::reset() {
    currentCommand = 1;
    halted = false;
    stepCounter = 0;
    tape.reset(); 
}

std::string PostMachine::getTapeString() const {
    return tape.toString();
}

std::string PostMachine::getStateInfo() const {
    std::string info;
    info += "Current command: " + std::to_string(currentCommand) + "\n";
    info += "Halted: " + std::string(halted ? "Yes" : "No") + "\n";
    info += "Steps executed: " + std::to_string(stepCounter) + "\n";
    info += "Tape: " + tape.toString() + "\n";
    info += "Head position: " + std::to_string(tape.getHeadPosition()) + "\n";
    return info;
}

bool PostMachine::isHalted() const {
    return halted;
}

int PostMachine::getCurrentCommand() const {
    return currentCommand;
}

void PostMachine::addCommand(int number, char type, int next1, int next2) {
    program.addCommand(number, type, next1, next2);
    reset();
}

void PostMachine::removeCommand(int number) {
    program.removeCommand(number);
    reset();
}

bool PostMachine::hasCommand(int number) const {
    return program.hasCommand(number);
}

void PostMachine::setLogging(bool enable) {
    logging = enable;
}

std::ostream& operator<<(std::ostream& os, const PostMachine& machine) {
    os << machine.program;
    return os;
}

std::istream& operator>>(std::istream& is, PostMachine& machine) {
    machine.program.clearCommands();
    is >> machine.program;
    machine.reset();
    return is;
}