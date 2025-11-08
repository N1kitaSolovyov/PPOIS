/**
 * @file main.cpp
 * @brief Main file for LongInt interactive calculator
 * @author Your Name
 * @version 1.0
 * @date 2024-01-15
 */

#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include "LongInt.h"

using namespace std;

/**
 * @brief Clears input buffer and error state
 */
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * @brief Displays the main menu options
 */
void displayMenu() {
    cout << "\n=== Long Integer Calculator ===" << endl;
    cout << "1. Input first number (a)" << endl;
    cout << "2. Input second number (b)" << endl;
    cout << "3. Display current numbers" << endl;
    cout << "4. Arithmetic operations" << endl;
    cout << "5. Comparison operations" << endl;
    cout << "6. Compound assignment operations" << endl;
    cout << "7. Increment/Decrement operations" << endl;
    cout << "8. Conversion operations" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose option: ";
}

/**
 * @brief Displays arithmetic operations submenu
 */
void displayArithmeticMenu() {
    cout << "\n=== Arithmetic Operations ===" << endl;
    cout << "1. Addition (a + b)" << endl;
    cout << "2. Subtraction (a - b)" << endl;
    cout << "3. Multiplication (a * b)" << endl;
    cout << "4. Division (a / b)" << endl;
    cout << "5. Addition with int (a + int)" << endl;
    cout << "6. Subtraction with int (a - int)" << endl;
    cout << "7. Multiplication with int (a * int)" << endl;
    cout << "8. Division with int (a / int)" << endl;
    cout << "0. Back to main menu" << endl;
    cout << "Choose option: ";
}

/**
 * @brief Displays comparison operations submenu
 */
void displayComparisonMenu() {
    cout << "\n=== Comparison Operations ===" << endl;
    cout << "1. Equality (a == b)" << endl;
    cout << "2. Inequality (a != b)" << endl;
    cout << "3. Less than (a < b)" << endl;
    cout << "4. Greater than (a > b)" << endl;
    cout << "5. Less than or equal (a <= b)" << endl;
    cout << "6. Greater than or equal (a >= b)" << endl;
    cout << "7. Compare with int (a == int)" << endl;
    cout << "8. Compare with int (a < int)" << endl;
    cout << "9. Compare with int (a > int)" << endl;
    cout << "0. Back to main menu" << endl;
    cout << "Choose option: ";
}

/**
 * @brief Prompts user for a LongInt number
 * @param prompt The prompt message
 * @return LongInt entered by user
 */
LongInt inputNumber(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);

    // Remove any whitespace
    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

    return LongInt(input);
}

/**
 * @brief Prompts user for an integer
 * @param prompt The prompt message
 * @return int entered by user
 */
int inputInt(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input! Please enter an integer: ";
        clearInput();
    }
    clearInput();
    return value;
}

/**
 * @brief Main interactive menu function
 */
void runInteractiveMenu() {
    LongInt a, b;
    int choice;
    bool running = true;

    cout << "=== Long Integer Interactive Calculator ===" << endl;
    cout << "This program demonstrates arbitrary precision integer operations." << endl;

    while (running) {
        displayMenu();

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number between 0 and 8." << endl;
            clearInput();
            continue;
        }

        clearInput();

        switch (choice) {
        case 1: {
            a = inputNumber("Enter first number (a): ");
            cout << "First number set to: " << a << endl;
            break;
        }

        case 2: {
            b = inputNumber("Enter second number (b): ");
            cout << "Second number set to: " << b << endl;
            break;
        }

        case 3: {
            cout << "\nCurrent numbers:" << endl;
            cout << "a = " << a << endl;
            cout << "b = " << b << endl;
            cout << "a.isZero() = " << (a.isZero() ? "true" : "false") << endl;
            cout << "b.isZero() = " << (b.isZero() ? "true" : "false") << endl;
            break;
        }

        case 4: {
            int arithmeticChoice;
            do {
                displayArithmeticMenu();

                if (!(cin >> arithmeticChoice)) {
                    cout << "Invalid input!" << endl;
                    clearInput();
                    continue;
                }
                clearInput();

                switch (arithmeticChoice) {
                case 1: {
                    LongInt result = a + b;
                    cout << a << " + " << b << " = " << result << endl;
                    break;
                }
                case 2: {
                    LongInt result = a - b;
                    cout << a << " - " << b << " = " << result << endl;
                    break;
                }
                case 3: {
                    LongInt result = a * b;
                    cout << a << " * " << b << " = " << result << endl;
                    break;
                }
                case 4: {
                    try {
                        LongInt result = a / b;
                        cout << a << " / " << b << " = " << result << endl;
                    }
                    catch (const invalid_argument& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                    break;
                }
                case 5: {
                    int num = inputInt("Enter integer to add: ");
                    LongInt result = a + num;
                    cout << a << " + " << num << " = " << result << endl;
                    break;
                }
                case 6: {
                    int num = inputInt("Enter integer to subtract: ");
                    LongInt result = a - num;
                    cout << a << " - " << num << " = " << result << endl;
                    break;
                }
                case 7: {
                    int num = inputInt("Enter integer to multiply: ");
                    LongInt result = a * num;
                    cout << a << " * " << num << " = " << result << endl;
                    break;
                }
                case 8: {
                    int num = inputInt("Enter integer to divide: ");
                    try {
                        LongInt result = a / num;
                        cout << a << " / " << num << " = " << result << endl;
                    }
                    catch (const invalid_argument& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                    break;
                }
                case 0: {
                    break;
                }
                default: {
                    cout << "Invalid option!" << endl;
                    break;
                }
                }
            } while (arithmeticChoice != 0);
            break;
        }

        case 5: {
            int comparisonChoice;
            do {
                displayComparisonMenu();

                if (!(cin >> comparisonChoice)) {
                    cout << "Invalid input!" << endl;
                    clearInput();
                    continue;
                }
                clearInput();

                switch (comparisonChoice) {
                case 1: {
                    cout << a << " == " << b << " : " << (a == b ? "true" : "false") << endl;
                    break;
                }
                case 2: {
                    cout << a << " != " << b << " : " << (a != b ? "true" : "false") << endl;
                    break;
                }
                case 3: {
                    cout << a << " < " << b << " : " << (a < b ? "true" : "false") << endl;
                    break;
                }
                case 4: {
                    cout << a << " > " << b << " : " << (a > b ? "true" : "false") << endl;
                    break;
                }
                case 5: {
                    cout << a << " <= " << b << " : " << (a <= b ? "true" : "false") << endl;
                    break;
                }
                case 6: {
                    cout << a << " >= " << b << " : " << (a >= b ? "true" : "false") << endl;
                    break;
                }
                case 7: {
                    int num = inputInt("Enter integer to compare: ");
                    cout << a << " == " << num << " : " << (a == num ? "true" : "false") << endl;
                    break;
                }
                case 8: {
                    int num = inputInt("Enter integer to compare: ");
                    cout << a << " < " << num << " : " << (a < num ? "true" : "false") << endl;
                    break;
                }
                case 9: {
                    int num = inputInt("Enter integer to compare: ");
                    cout << a << " > " << num << " : " << (a > num ? "true" : "false") << endl;
                    break;
                }
                case 0: {
                    break;
                }
                default: {
                    cout << "Invalid option!" << endl;
                    break;
                }
                }
            } while (comparisonChoice != 0);
            break;
        }

        case 6: {
            cout << "\n=== Compound Assignment Operations ===" << endl;
            LongInt original_a = a;

            cout << "Original a = " << original_a << endl;
            cout << "b = " << b << endl;

            a += b;
            cout << "After a += b: a = " << a << endl;

            a = original_a;
            a -= b;
            cout << "After a -= b: a = " << a << endl;

            a = original_a;
            a *= b;
            cout << "After a *= b: a = " << a << endl;

            a = original_a;
            try {
                a /= b;
                cout << "After a /= b: a = " << a << endl;
            }
            catch (const invalid_argument& e) {
                cout << "Division error: " << e.what() << endl;
            }

            a = original_a;
            break;
        }

        case 7: {
            cout << "\n=== Increment/Decrement Operations ===" << endl;
            LongInt original_a = a;

            cout << "Original a = " << original_a << endl;
            cout << "++a = " << ++a << endl;
            cout << "a after prefix increment = " << a << endl;

            a = original_a;
            cout << "a++ = " << a++ << endl;
            cout << "a after postfix increment = " << a << endl;

            a = original_a;
            cout << "--a = " << --a << endl;
            cout << "a after prefix decrement = " << a << endl;

            a = original_a;
            cout << "a-- = " << a-- << endl;
            cout << "a after postfix decrement = " << a << endl;

            a = original_a; 
            break;
        }

        case 8: {
            cout << "\n=== Conversion Operations ===" << endl;
            cout << "a = " << a << endl;

            try {
                int intValue = static_cast<int>(a);
                cout << "a as int = " << intValue << endl;
            }
            catch (const exception& e) {
                cout << "Conversion error: Number is too large for int type" << endl;
            }

            cout << "String representation: " << a.toString() << endl;
            cout << "Is zero: " << (a.isZero() ? "true" : "false") << endl;
            break;
        }

        case 0: {
            cout << "Thank you for using Long Integer Calculator!" << endl;
            running = false;
            break;
        }

        default: {
            cout << "Invalid option! Please enter a number between 0 and 8." << endl;
            break;
        }
        }
    }
}

/**
 * @brief Main function
 */
int main() {
    runInteractiveMenu();
    return 0;
}