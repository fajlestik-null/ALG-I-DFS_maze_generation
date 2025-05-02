#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <stack>
#include <random>

using namespace std;

class Maze
{
private:
    int mX,
        mY,
        mSolveOrientation,
        mEntrance,
        mExit;

    typedef struct
    {
        array<bool, 4> mWalls{true, true, true, true};
        bool mVisited = false;
    } Cell;

    enum Direction
    {
        TOP = 0,
        RIGHT = 1,
        BOTTOM = 2,
        LEFT = 3
    };

    vector<Cell> mGrid;
    vector<pair<int, int>> mNeighbours;

private:
    Cell &accessGrid(const int Y, const int X);

    pair<int, int> getRandomNeighbour(const int Y, const int X);

    void removeWall(const int CURRENT_Y, const int CURRENT_X, const int NEXT_Y, const int NEXT_X);

    void checkEntranceExit(const int Y, const int X);

    void generaeEntranceExit();

    void executeRandomDFS();

    void saveMaze();

public:
    Maze(const int Y, const int X);
};