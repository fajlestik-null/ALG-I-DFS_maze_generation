/**
 * @file input.cpp
 * @brief Input class implementation.
 */
#include "input.h"

void Input::assignValue(int &rVar, const int VALUE)
{
    rVar = VALUE;
}

bool Input::isInt(const string STRING)
{
    for (auto s : STRING)
    {
        if (!isdigit(s))
        {
            return false;
        }
    }

    return true;
}

void Input::printExitMessage()
{
    cout << "<------------------------------------------------------------------------------>" << endl;
    cout << "Please insert right parameters: (rows(int > 1) || cols(int > 1)) [optional] seed(int)" << endl;
    cout << "                       Example: ./executable_name 10 10 5                       " << endl;
    cout << "<------------------------------------------------------------------------------>" << endl;
    exit(-1);
}

Input::Input(const int COUNTER, const char *INPUT[])
{
    if (COUNTER == 3 || COUNTER == 4)
    {
        (isInt(INPUT[1])) ? assignValue(mRows, atoi(INPUT[1])) : printExitMessage();
        (isInt(INPUT[2])) ? assignValue(mCols, atoi(INPUT[2])) : printExitMessage();

        if (mRows < 2 && mCols < 2)
        {
            printExitMessage();
        }

        if (COUNTER == 4)
        {
            (isInt(INPUT[3])) ? srand(atoi(INPUT[3])) : printExitMessage();
        }
    }
    else
    {
        printExitMessage();
    }
}

int Input::getRows()
{
    return mRows;
}

int Input::getCollumns()
{
    return mCols;
}