#pragma once

#include <iostream>

using namespace std;

class Input
{
private:
    int mRows,
        mCols;

private:
    void assignValue(int &rVar, const int VALUE);

    bool isInt(const string STRING);

    void printExitMessage();

public:
    Input(const int COUNTER, const char *INPUT[]);

    int getRows();

    int getCollumns();
};