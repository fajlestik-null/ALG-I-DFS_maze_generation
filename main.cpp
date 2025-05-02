#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <stack>
#include <limits>
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
    Cell &accessGrid(const int Y, const int X)
    {
        return mGrid[Y * mX + X];
    }

    pair<int, int> getRandomNeighbour(const int Y, const int X)
    {
        mNeighbours.clear();

        if (Y > 0 && !accessGrid(Y - 1, X).mVisited)
        {
            mNeighbours.emplace_back(Y - 1, X);
        }
        if (X < mX - 1 && !accessGrid(Y, X + 1).mVisited)
        {
            mNeighbours.emplace_back(Y, X + 1);
        }
        if (Y < mY - 1 && !accessGrid(Y + 1, X).mVisited)
        {
            mNeighbours.emplace_back(Y + 1, X);
        }
        if (X > 0 && !accessGrid(Y, X - 1).mVisited)
        {
            mNeighbours.emplace_back(Y, X - 1);
        }
        if (!mNeighbours.empty())
        {
            return mNeighbours[rand() % mNeighbours.size()];
        }

        return {-1, -1}; // error/empty message -> cannot happen naturaly
    }

    void removeWall(const int CURRENT_Y, const int CURRENT_X, const int NEXT_Y, const int NEXT_X)
    {
        if (CURRENT_Y == NEXT_Y)
        {
            if (CURRENT_X < NEXT_X)
            {
                accessGrid(CURRENT_Y, CURRENT_X).mWalls[RIGHT] = false;
                accessGrid(NEXT_Y, NEXT_X).mWalls[LEFT] = false;
            }
            else
            {
                accessGrid(CURRENT_Y, CURRENT_X).mWalls[LEFT] = false;
                accessGrid(NEXT_Y, NEXT_X).mWalls[RIGHT] = false;
            }
        }
        else if (CURRENT_X == NEXT_X)
        {
            if (CURRENT_Y < NEXT_Y)
            {
                accessGrid(CURRENT_Y, CURRENT_X).mWalls[BOTTOM] = false;
                accessGrid(NEXT_Y, NEXT_X).mWalls[TOP] = false;
            }
            else
            {
                accessGrid(CURRENT_Y, CURRENT_X).mWalls[TOP] = false;
                accessGrid(NEXT_Y, NEXT_X).mWalls[BOTTOM] = false;
            }
        }
    }

    void checkEntranceExit(const int Y, const int X)
    {
        if (mSolveOrientation == 0)
        {
            if (mEntrance == X && Y == 0)
            {
                accessGrid(Y, X).mWalls[TOP] = false;
            }
            if (mExit == X && Y == mY - 1)
            {
                accessGrid(Y, X).mWalls[BOTTOM] = false;
            }
        }
        else
        {
            if (mEntrance == Y && X == 0)
            {
                accessGrid(Y, X).mWalls[LEFT] = false;
            }
            if (mExit == Y && X == mX - 1)
            {
                accessGrid(Y, X).mWalls[RIGHT] = false;
            }
        }
    }

    void executeRandomDFS()
    {
        stack<pair<int, int>> backTrack;
        backTrack.push({0, 0});
        accessGrid(0, 0).mVisited = true;

        checkEntranceExit(0, 0);

        while (!backTrack.empty())
        {
            bool currentSwitched = false;

            int currentY = backTrack.top().first;
            int currentX = backTrack.top().second;

            pair<int, int> nextCell = getRandomNeighbour(currentY, currentX);

            int nextY = nextCell.first;
            int nextX = nextCell.second;

            if (nextY != -1 && nextX != -1)
            {
                removeWall(currentY, currentX, nextY, nextX);

                checkEntranceExit(nextY, nextX);

                accessGrid(nextY, nextX).mVisited = true;
                backTrack.push({nextY, nextX});
                currentSwitched = true;
            }

            if (!currentSwitched)
            {
                backTrack.pop();
            }
        }
    }

    void saveMaze()
    {
        int indent = 20;

        ofstream file("maze.svg");
        file << "<svg xmlns = 'http://www.w3.org/2000/svg' width = '" << mX * 20 + 2 * indent << "' height = '" << mY * 20 + 2 * indent << "'>\n";
        file << "<rect width='100%' height='100%' fill='white'/>\n";
        file << "<g stroke='black' stroke-width='2'>\n";

        for (int y = 0; y < mY; y++)
        {
            for (int x = 0; x < mX; x++)
            {
                int coordinateY = y * 20 + indent;
                int coordinateX = x * 20 + indent;

                if (accessGrid(y, x).mWalls[TOP])
                {
                    file << "<line x1='" << coordinateX << "' y1='" << coordinateY << "' x2='" << coordinateX + 20 << "' y2='" << coordinateY << "' />\n";
                }
                if (accessGrid(y, x).mWalls[RIGHT])
                {
                    file << "<line x1='" << coordinateX + 20 << "' y1='" << coordinateY << "' x2='" << coordinateX + 20 << "' y2='" << coordinateY + 20 << "' />\n";
                }
                if (accessGrid(y, x).mWalls[BOTTOM])
                {
                    file << "<line x1='" << coordinateX << "' y1='" << coordinateY + 20 << "' x2='" << coordinateX + 20 << "' y2='" << coordinateY + 20 << "' />\n";
                }
                if (accessGrid(y, x).mWalls[LEFT])
                {
                    file << "<line x1='" << coordinateX << "' y1='" << coordinateY << "' x2='" << coordinateX << "' y2='" << coordinateY + 20 << "' />\n";
                }
            }
        }

        file << "</g>\n</svg>\n";
        file.close();
    }

public:
    Maze(const int Y, const int X) : mY(Y), mX(X), mGrid(Y * X)
    {
        mSolveOrientation = rand() % 2;

        if (mSolveOrientation == 0)
        {
            mEntrance = rand() % mX;
            mExit = rand() % mX;
        }
        else
        {
            mEntrance = rand() % mY;
            mExit = rand() % mY;
        }

        while (mEntrance == mExit)
        {
            if (mSolveOrientation == 0)
            {
                mExit = rand() % mX;
            }
            else
            {
                mExit = rand() % mY;
            }
        }

        executeRandomDFS();
        saveMaze();
    }
};

class Input
{
private:
    int mRows,
        mCols;

private:
    void assignValue(int &rVar, const int VALUE)
    {
        rVar = VALUE;
    }

    bool isInt(const string STRING)
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

    void printExitMessage()
    {
        cout << "<---------------------------------------------------------------------->" << endl;
        cout << "Please insert right parameters: rows(int) cols(int) [optional] seed(int)" << endl;
        cout << "Example: ./executable_name 10 10 5" << endl;
        cout << "<---------------------------------------------------------------------->" << endl;
        exit(-1);
    }

public:
    Input(const int COUNTER, const char *INPUT[])
    {
        if (COUNTER == 3 || COUNTER == 4)
        {
            (isInt(INPUT[1])) ? assignValue(mRows, atoi(INPUT[1])) : printExitMessage();
            (isInt(INPUT[2])) ? assignValue(mCols, atoi(INPUT[2])) : printExitMessage();

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

    int getRows()
    {
        return mRows;
    }

    int getCollumns()
    {
        return mCols;
    }
};

int main(int argc, char const *argv[])
{

    Input input(argc, argv);

    Maze maze(input.getRows(), input.getCollumns());

    return 0;
}