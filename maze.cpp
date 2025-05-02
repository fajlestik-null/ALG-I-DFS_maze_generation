#include "maze.h"

Maze::Cell &Maze::accessGrid(const int Y, const int X)
{
    return mGrid[Y * mX + X];
}

pair<int, int> Maze::getRandomNeighbour(const int Y, const int X)
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

    return {-1, -1};
}

void Maze::removeWall(const int CURRENT_Y, const int CURRENT_X, const int NEXT_Y, const int NEXT_X)
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

void Maze::checkEntranceExit(const int Y, const int X)
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

void Maze::generateEntranceExit()
{
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
}

void Maze::executeRandomDFS()
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

void Maze::saveMaze()
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

Maze::Maze(const int Y, const int X) : mY(Y), mX(X), mGrid(Y * X)
{
    mSolveOrientation = rand() % 2;

    generateEntranceExit();

    /**
     * Ask if this is acceptable
     **/
    for (int i = 0; mEntrance == mExit; i++)
    {
        if (i % 2)
        {
            (mSolveOrientation == 0) ? mSolveOrientation = 1 : mSolveOrientation = 0;
        }

        generateEntranceExit();
    }
    //

    executeRandomDFS();
    saveMaze();
}