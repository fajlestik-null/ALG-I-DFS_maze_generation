#pragma once

#include <iostream>

using namespace std;

/**
 * @class Input
 * @brief Handles command-line input parsing and validation for a program.
 *
 * This class extracts and validates the number of rows and columns (optionally a seed value)
 * from command-line arguments provided at runtime. If the input is invalid, it exits with an error message (-1).
 */
class Input
{
private:
    int mRows, ///< Number of rows specified by the user.
        mCols; ///< Number of collumns specified by the user.

    /**
     * @brief Assigns a value to a given integer variable.
     *
     * @param rVar Reference to the integer variable, which will be the value assigned to.
     * @param VALUE The integer (const) value to assign.
     */
    void assignValue(int &rVar, const int VALUE);

    /**
     * @brief Checks if the provided string is a valid (non-negative integer).
     *
     * @param STRING The string (const) to check.
     * @return true if the string is valid, false, when the first invalid occurence is found.
     */
    bool isInt(const string STRING);

    /**
     * @brief Prints an error message and exits the program.
     *
     * In practice, this function is used as an abbreviation.
     */
    void printExitMessage();

public:
    /**
     * @brief Constructs the Input object and processes command-line arguments.
     *
     * Accepts either 2 or 3 command-line arguments:
     *  - Number of rows defined as an integer
     *  - Number of columns defined as an integer
     *  @warning Mandatory parameters valid values: rows > 1 || collumns > 1
     *  - Random seed (optional) as integer for the purpose of srand() function
     *
     * @param COUNTER Number (const) of command-line arguments.
     * @param INPUT Array (const) of argument strings.
     */
    Input(const int COUNTER, const char *INPUT[]);

    /**
     * @brief Retrieves the number of rows.
     *
     * @return The number of rows as integer.
     */
    int getRows();

    /**
     * @brief Retrieves the number of collumns.
     *
     * @return The number of collumns integer.
     */
    int getCollumns();
};