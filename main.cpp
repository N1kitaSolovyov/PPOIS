/**
 * @file main.cpp
 * @brief Main file of the Post Machine program with interactive menu and file execution
 * @author Your Name
 * @version 1.0
 */

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "PostMachine.h"

using namespace std;

/**
 * @brief Displays the interactive menu options
 */
void displayMenu() {
    cout << "\n=== Post Machine Interactive Menu ===" << endl;
    cout << "1. Load program from file" << endl;
    cout << "2. Load tape from string" << endl;
    cout << "3. Execute step by step" << endl;
    cout << "4. Run full program" << endl;
    cout << "5. Show current state" << endl;
    cout << "6. Add command manually" << endl;
    cout << "7. Remove command" << endl;
    cout << "8. Reset machine" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose option: ";
}

/**
 * @brief Clears the input buffer and error state
 */
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * @brief Runs the interactive menu mode
 */
void runInteractiveMenu() {
    PostMachine machine;
    bool logging = true;
    machine.setLogging(logging);

    int choice;

    do {
        displayMenu();

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number between 0 and 9." << endl;
            clearInput();
            continue;
        }

        clearInput();

        switch (choice) {
        case 1: {
            string filename;
            cout << "Enter program file name: ";
            getline(cin, filename);

            try {
                ifstream file(filename);
                if (!file.is_open()) {
                    throw runtime_error("Cannot open file: " + filename);
                }

                string tapeStr;
                if (!getline(file, tapeStr)) {
                    throw runtime_error("File is empty");
                }

                machine.loadTapeFromString(tapeStr);
                machine.loadProgramFromStream(file);
                file.close();

                machine.reset();

                cout << "Program and tape loaded successfully!" << endl;
                cout << "Initial tape: " << machine.getTapeString() << endl;
                cout << "Machine state: " << (machine.isHalted() ? "Halted" : "Ready") << endl;
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            break;
        }
        case 2: {
            string tapeStr;
            cout << "Enter tape string (e.g., '101'): ";
            getline(cin, tapeStr);
            machine.loadTapeFromString(tapeStr);
            cout << "Tape loaded: " << machine.getTapeString() << endl;
            break;
        }

        case 3: {
            if (machine.isHalted()) {
                cout << "Machine is halted. Reset first or load new program." << endl;
                break;
            }

            cout << "Step-by-step execution (press Enter for next step, 'q' to quit):" << endl;

            while (!machine.isHalted()) {
                cout << "\n" << machine.getStateInfo() << endl;

                cout << "Press Enter to continue (or 'q' to quit)...";
                string input;
                getline(cin, input);

                if (input == "q" || input == "Q") {
                    break;
                }

                if (!machine.step()) {
                    cout << "Execution completed or halted!" << endl;
                    break;
                }
            }
            break;
        }

        case 4: {
            if (machine.isHalted()) {
                cout << "Machine is halted. Reset first or load new program." << endl;
                break;
            }

            cout << "Running full program..." << endl;
            machine.run();
            cout << "Execution completed!" << endl;
            cout << machine.getStateInfo() << endl;
            break;
        }

        case 5: {
            cout << machine.getStateInfo() << endl;
            break;
        }

        case 6: {
            int number, next1, next2;
            char type;

            cout << "Enter command number: ";
            while (!(cin >> number)) {
                cout << "Invalid input! Enter a number: ";
                clearInput();
            }

            cout << "Enter command type (R, L, V, X, ?, !): ";
            while (!(cin >> type) ||
                (type != 'R' && type != 'L' && type != 'V' &&
                    type != 'X' && type != '?' && type != '!')) {
                cout << "Invalid command type! Enter R, L, V, X, ?, or !: ";
                clearInput();
            }

            if (type == '?') {
                cout << "Enter next command if true: ";
                while (!(cin >> next1)) {
                    cout << "Invalid input! Enter a number: ";
                    clearInput();
                }
                cout << "Enter next command if false: ";
                while (!(cin >> next2)) {
                    cout << "Invalid input! Enter a number: ";
                    clearInput();
                }
                machine.addCommand(number, type, next1, next2);
            }
            else if (type != '!') {
                cout << "Enter next command: ";
                while (!(cin >> next1)) {
                    cout << "Invalid input! Enter a number: ";
                    clearInput();
                }
                machine.addCommand(number, type, next1);
            }
            else {
                machine.addCommand(number, type);
            }

            clearInput(); 
            cout << "Command added successfully!" << endl;
            break;
        }

        case 7: {
            int number;
            cout << "Enter command number to remove: ";
            while (!(cin >> number)) {
                cout << "Invalid input! Enter a number: ";
                clearInput();
            }

            if (machine.hasCommand(number)) {
                machine.removeCommand(number);
                cout << "Command removed successfully!" << endl;
            }
            else {
                cout << "Command not found!" << endl;
            }
            clearInput();
            break;
        }

        case 8: {
            machine.reset();
            cout << "Machine reset to initial state!" << endl;
            break;
        }

        case 9: {
            logging = !logging;
            machine.setLogging(logging);
            cout << "Logging " << (logging ? "enabled" : "disabled") << endl;
            break;
        }

        case 0: {
            cout << "Goodbye!" << endl;
            break;
        }

        default: {
            cout << "Invalid option! Please enter a number between 0 and 9." << endl;
            break;
        }
        }

    } while (choice != 0);
}

/**
 * @brief Executes a Post Machine program from a file
 */
void runFromFile(const string& filename, bool logging) {
    try {
        PostMachine machine;
        machine.setLogging(logging);

        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Cannot open file: " + filename);
        }

        string tapeStr;
        if (!getline(file, tapeStr)) {
            throw runtime_error("File is empty");
        }

        machine.loadTapeFromString(tapeStr);
        machine.loadProgramFromStream(file);
        file.close();

        cout << "=== Starting Post Machine ===" << endl;
        cout << "Program file: " << filename << endl;
        cout << "Initial tape: " << machine.getTapeString() << endl;
        cout << "Logging: " << (logging ? "enabled" : "disabled") << endl;

        if (logging) {
            cout << "\nExecution steps:" << endl;
        }

        machine.run();

        cout << "\n=== Final Result ===" << endl;
        cout << machine.getStateInfo() << endl;

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

/**
 * @brief Main function of the Post Machine program
 */
int main(int argc, char* argv[]) {
    if (argc > 1) {
        string filename;
        bool logging = false;

        for (int i = 1; i < argc; i++) {
            string arg = argv[i];
            if (arg == "-log" || arg == "--log") {
                logging = true;
            }
            else {
                filename = arg;
            }
        }

        if (!filename.empty()) {
            runFromFile(filename, logging);
        }
        else {
            cout << "Usage: " << argv[0] << " [program_file] [-log]" << endl;
            cout << "Or run without arguments for interactive mode" << endl;
        }
    }
    else {
        cout << "=== Post Machine ===" << endl;
        cout << "Running in interactive mode..." << endl;
        runInteractiveMenu();
    }

    return 0;
}