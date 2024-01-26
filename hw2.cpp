#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

std::string decimalToBinary(long long, int);

void formatForBits(std::vector<int>*, int, bool);

bool mainProgram();

const std::string COMMAND_EXIT = "ESC";

int main() {
    const std::string COMMAND_START = "START";
    bool flag;
    bool isValid;

    std::string user;

   // Program Start Point
   std::cout << "\n---- HOMEWORK 2 ----" << std::endl;
   std::cout
   << "** Welcome to using Decimal Number to Binary Converter.         **\n"
      "** This program converts numbers into:\n"
      "** 16, 32, 64 bits.\n"
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
    int bits;
    bool isValid;

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

            // Check if it's out of range
            if (value < LONG_MIN) {

                std::cout <<
                "Number is out of range(MAX: 64bits). Please try again.\n";
                isValid = false;

            }
        }

    } while (!isValid);

    // Accept user input for unsigned/signed
    do {
        std::cout << "Do you want to do unsigned number?(Y/N): ";

        std::cin >> user;

        if (user == "Y" || user == "y") {
            // Check number
            if (value < 0) {
                std::cout << "Number you input " << value << " is negative.\n";
                isValid = false;
            }
            else
                isValid = true;

        }
        else if (user == "N" || user == "n") {
            isValid = true;
        }

        else if (user == COMMAND_EXIT)
            return FLAG_EXIT;

        else {

            std::cout << "Invalid input. Please try again.\n";
            isValid = false;

        }

    } while (!isValid);

    // Accept user input for digits
    do {
        std::cout << "Number size: 64, 32, 16 bits? (Input:64, 32, 16): ";

        std::cin >> user;

        // Check if it's exit
        if (user == COMMAND_EXIT)
            return FLAG_EXIT;

        // Check if it's valid
        try {

            bits = stoi(user);

        } catch (std::exception& e) {

            std::cout << "Invalid input. Please try again.\n";

        }

        if (bits != 32 && bits != 64 && bits != 16) {
            std::cout << "Invalid input. Please try again.\n";
            isValid = false;
        }

        else
            isValid = true;

    } while (!isValid);

    std::cout << "\n------------Finish Convert------------\n";

    try {
        // Execute convert function
        std::cout <<
        value << " convert to decimal in " << bits << " digits is \n";
        std::cout << decimalToBinary(value, bits);
    } catch (std::exception& e) {
        std::cout << "\n------------Out of digits------------\n";
    }

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

    else if (valueHolder->size() > bits)
            throw std::exception();

    reverse(valueHolder->begin(), valueHolder->end());

    for (int i = 1; i <= valueHolder->size(); ++i) {
        ss << valueHolder->at(i - 1);
        if (i%4 == 0)
            ss << ' ';
    }

    return ss.str();

}