#include "PostProgram.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void PostProgram::addCommand(int number, char type, int next1, int next2) {
    removeCommand(number);

    Command cmd;
    cmd.number = number;
    cmd.type = type;
    cmd.next1 = next1;
    cmd.next2 = next2;
    commands.push_back(cmd);
}

void PostProgram::removeCommand(int number) {
    for (auto it = commands.begin(); it != commands.end(); ++it) {
        if (it->number == number) {
            commands.erase(it);
            break;
        }
    }
}

bool PostProgram::hasCommand(int number) const {
    for (const Command& cmd : commands) {
        if (cmd.number == number) return true;
    }
    return false;
}

void PostProgram::clearCommands() {
    commands.clear();
}

char PostProgram::getCommandType(int number) const {
    for (const Command& cmd : commands) {
        if (cmd.number == number) return cmd.type;
    }
    throw std::runtime_error("Command not found: " + std::to_string(number));
}

int PostProgram::getNextCommand(int number, bool hasMark) const {
    for (const Command& cmd : commands) {
        if (cmd.number == number) {
            if (cmd.type == '?') return hasMark ? cmd.next1 : cmd.next2;
            if (cmd.type == '!') return -1;
            return cmd.next1;
        }
    }
    throw std::runtime_error("Command not found: " + std::to_string(number));
}

std::vector<int> PostProgram::getCommandNumbers() const {
    std::vector<int> numbers;
    for (const Command& cmd : commands) {
        numbers.push_back(cmd.number);
    }
    return numbers;
}

void PostProgram::loadFromStream(std::istream& is) {
    commands.clear();
    std::string line;

    while (std::getline(is, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        int number;
        char colon;
        char type;

        if (iss >> number >> colon >> type && colon == ':') {
            if (type == '?') {
                int nextMark, nextNoMark;
                if (iss >> nextMark >> nextNoMark) {
                    addCommand(number, type, nextMark, nextNoMark);
                }
            }
            else if (type != '!') {
                int next;
                if (iss >> next) {
                    addCommand(number, type, next);
                }
            }
            else {
                addCommand(number, type);
            }
        }
    }
}

void PostProgram::saveToStream(std::ostream& os) const {
    for (const Command& cmd : commands) {
        os << cmd.number << ": " << cmd.type;
        if (cmd.type == '?') {
            os << " " << cmd.next1 << " " << cmd.next2;
        }
        else if (cmd.type != '!') {
            os << " " << cmd.next1;
        }
        os << std::endl;
    }
}

void PostProgram::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    loadFromStream(file);
    file.close();
}

void PostProgram::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot create file: " + filename);
    }
    saveToStream(file);
    file.close();
}

std::ostream& operator<<(std::ostream& os, const PostProgram& program) {
    program.saveToStream(os);
    return os;
}

std::istream& operator>>(std::istream& is, PostProgram& program) {
    program.loadFromStream(is);
    return is;
}