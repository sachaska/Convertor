// AUTHOR: Ai Sun 4194172
// FILE: hw2.cpp
// DATE: Jan 25 2023
// PURPOSE: This program converts decimal numbers to 64bits binary
// representation.
// INPUT:   User commands and decimal numbers provided by the user.
// PROCESS: The program prompts the user to enter a command to start or exit.
//          If the user starts the program, it converts the entered decimal
//          numbers to binary and displays the result. The program continues
//          until the user decides to exit.
// OUTPUT:  Binary representation of decimal numbers and program status messages

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

// Function:    mainProgram
// Purpose:     The main program
// handles the conversion of decimal numbers to 64bits binary.
// Parameters:  None
// Returns:     true if the user chooses to continue,
// false if the user chooses to exit.
bool mainProgram();

// Function:    decimalToBinary
// Purpose:     Converts a decimal number to its binary representation.
// Parameters:  The decimal number, and the number of bits.
// Returns:     Binary representation of the decimal number as a string.
std::string decimalToBinary(long long, int);

// Function:    formatForBits
// Purpose:     Adds padding to the binary vector to achieve the desired
// number of bits.
// Parameters:  The binary vector, the desired number of bits,
//              and a flag indicating whether the number is negative.
// Returns:     None
void formatForBits(std::vector<int>*, int, bool);

const std::string COMMAND_EXIT = "ESC";
const int DIGITS = 64;

int main() {
    const std::string COMMAND_START = "START";
    bool flag;
    bool isValid;

    std::string user;

   // Program Start Point
   std::cout << "\n\t\t\t\t\t---- HOMEWORK 2 ----" << std::endl;
   std::cout
   << "** Welcome to using Decimal Number to 64 bits Binary Converter.  **\n"
      "\n"
      "**                   Input START to start.                       **\n"
      "**               Input ESC to exit the program.                  **\n";

   do {
       // Accept user input Point
       std::cout << "\nEnter command: ";
       std::cin >> user;

       if (user == COMMAND_START) {
           isValid = true;
           std::cout << "\n------------Main program start------------\n";
           do {
               flag = mainProgram();
           } while (flag);

       }

       else if (user == COMMAND_EXIT) {
           isValid = true;
       }

       else {
           std::cout << "Invalid input. Please try again.\n";
           isValid = false;
       }
   } while (!isValid);

    std::cout << "\n------------PROGRAM END------------\n"
    << "**\tThank you for using convert program!\t**";
}

bool mainProgram() {
    const bool FLAG_EXIT = false;
    const bool FLAG_CONTINUE = true;

    std::string user;
    long value;
    bool isNegative;
    bool isValid;

    // Accept user input for unsigned/signed
    do {
        std::cout << "Enter 1 to convert negative number.\n"
        << "Enter 0 to convert positive number and zero: ";

        std::cin >> user;

        if (user == "1") {

            isNegative = true;
            isValid = true;

        }
        else if (user == "0") {
            isValid = true;
            isNegative = false;
        }

        else if (user == COMMAND_EXIT)
            return FLAG_EXIT;

        else {

            std::cout << "Invalid input. Please try again.\n";
            isValid = false;

        }

    } while (!isValid);

    // Accept user input for number
    do {
        std::cout << "Please input the number to convert (Integer) :";
        std::cin >> user;

        // Check if it's ESC
        if (user == COMMAND_EXIT)
            return FLAG_EXIT;

        else {

            // Check if it's valid
            try {

                value = stoll(user);
                isValid = true;

            } catch (std::out_of_range& e) {

                std::cout << "Number is out of range(MAX: 64bits). "
                             "Please try again.\n";
                isValid = false;

            } catch (std::exception& e) {

                std::cout << "Invalid input. Please try again.\n";
                isValid = false;

            }
            // Check again positive/negative
            if ((value >= 0 && isNegative) || (value < 0) &&!isNegative) {
                std::cout <<
                "Number is not same as type you provide. Please try again.\n";
                isValid = false;
            }
            // Check if it's out of range
            if (value < LONG_MIN) {

                std::cout <<
                "Number is out of range(MAX: 64bits). Please try again.\n";
                isValid = false;

            }
        }

    } while (!isValid);

    std::cout << "\n------------Finish Convert------------\n";

    // Execute convert function
    std::cout <<
        value << " convert to decimal in " << DIGITS << " digits is \n";
    std::cout << decimalToBinary(value, DIGITS);

    do {
        std::cout << "\nWould you like to convert another number? (Y/N) :";
        std::cin >> user;

        if (user == "Y" || user == "y") {
            return FLAG_CONTINUE;
        }
        else if (user == "N" || user == "n" || user == COMMAND_EXIT)
            return FLAG_EXIT;

        else {

            std::cout << "Invalid input. Please try again.\n";
            isValid = false;

        }

    } while (!isValid);

}

void formatForBits(std::vector<int>* binaryVector, int bits, bool isNegative) {
    const int NEGATIVE = 1;
    const int POSITIVE = 0;

    while (binaryVector->size() < bits) {

        if (isNegative)
            binaryVector->push_back(NEGATIVE);
        else
            binaryVector->push_back(POSITIVE);

    }

}

std::string decimalToBinary(long long value, int bits) {
    const int DECIMAL = 2;

    long long absValue;

    std::stringstream ss;

    auto * valueHolder = new std::vector<int>();

    bool isNegative = false;

    // Check if it's unsigned (negative)
    if (value < 0) {
        isNegative = true;

        // If so, get absolute value into process
        absValue = - value;

    }

    else
        absValue = value;

    while (absValue > 0) {

        valueHolder->push_back(absValue % DECIMAL);

        absValue /= DECIMAL;
    }

    if (isNegative) {
        int index = 0;

        while (index < valueHolder->size() && valueHolder->at(index) != 1) {
            index++;
        }

        // If first 1 is found
        if (index < valueHolder->size()) {

            for (int i = index + 1; i < valueHolder->size(); ++i) {
                if (valueHolder->at(i) == 0)
                    valueHolder->at(i) = 1;
                else
                    valueHolder->at(i) = 0;
            }

        }

    }

    if (valueHolder->size() < bits)
        formatForBits(valueHolder, bits, isNegative);

    reverse(valueHolder->begin(), valueHolder->end());

    for (int i = 1; i <= valueHolder->size(); ++i) {
        ss << valueHolder->at(i - 1);
        if (i%4 == 0)
            ss << ' ';
    }

    return ss.str();

}