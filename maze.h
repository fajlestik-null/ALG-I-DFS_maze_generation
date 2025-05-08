#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <stack>
#include <random>

#include <ctime>

using namespace std;

/**
 * @class Maze
 * @brief Generates a random maze using randomized depth-first search and saves it as an SVG file.
 *
 * The Maze class creates a grid of cells, eats out passages using a randomized DFS algorithm,
 * and visualizes the result in an SVG file. Entrance and exit are randomly placed on opposite sides,
 * so they can never be place exactly opposite each other.
 */
class Maze
{
private:
    int mX,        ///< X axis/width of the maze (columns)
        mY,        ///< Y axis/height of the maze (rows)
        mEntrance, ///< Position of the entrance
        mExit;     ///< Position of the exit

    bool mSolveOrientation; ///< Orientation of the entrance and the exit: true = vertical (top-bottom), false = horizontal (left-right)

    /**
     * @struct Cell
     * @brief Represents a single cell in the maze grid.
     *
     * A struct has been chosen, because its defaul public settings.
     */
    typedef struct
    {
        array<bool, 4> mWalls{true, true, true, true}; ///< Walls of the cell: {top, right, bottom, left}
        bool mVisited = false;                         ///< Signalization, whether the cell has been visited during generation
    } Cell;

    /**
     * @enum Direction
     * @brief Enumeration for cell's walls identification.
     *
     * Enumeration was created for better code readability.
     */
    enum Direction
    {
        TOP = 0,
        RIGHT = 1,
        BOTTOM = 2,
        LEFT = 3
    };

    vector<Cell> mGrid;                 ///< Flattened 2D grid of maze cells (flattened as a result of optimalizations)
    vector<pair<int, int>> mNeighbours; ///< Temporary storage for neighbouring unvisited cells; placed inside a class for less re-allocations

    /**
     * @brief Accesses a reference to a cell in the grid.
     * @param Y y coordinate/row index (const).
     * @param X x coordinate/column index (const).
     * @return Reference to the Cell.
     * @note Created mainly for readability of work with the flattened array.
     */
    Cell &accessGrid(const int Y, const int X);

    /**
     * @brief Randomly returns one of the unvisited neighbouring cells.
     * @param Y Current cell's y coordinate (const).
     * @param X Current cell's x coordinate (const).
     * @return Pair of (Y, X) for yet unvisited neighbour, or (-1, -1) if there are none left.
     */
    pair<int, int> getRandomNeighbour(const int Y, const int X);

    /**
     * @brief Removes the wall between two neighbouring cells.
     * @param CURRENT_Y Current cell's y coordinate (const).
     * @param CURRENT_X Current cell's x coordinate (const).
     * @param NEXT_Y Neighbouring cell's y coordinate (const).
     * @param NEXT_X Neighbouring cell's x coordinate (const).
     */
    void removeWall(const int CURRENT_Y, const int CURRENT_X, const int NEXT_Y, const int NEXT_X);

    /**
     * @brief Creates entrance or exit if accetable.
     * @param Y Cell's y coordinate.
     * @param X Cell's x coordinate.
     */
    void checkEntranceExit(const int Y, const int X);

    /**
     * @brief Randomly determines entrance and exit positions within the maze's borders.
     *
     * Created mainly for readability and easier repeatability
     */
    void generateEntranceExit();

    /**
     * @brief Generates the maze using a randomised depth-first search (DFS) algorithm.
     *
     * Starting from the top-left cell ((0,0)), this function explores random unvisited neighbours,
     * removing walls to create passages, then marking those cells as visited. If no neighbours are
     * available, it backtracks until all cells have been marked as visited. The result is a fully
     * connected maze with a single path between any two points.
     *
     * @note Since we work with a continuous graph, we can be sure that wherever we start in the maze,
     * we will always get to the exit successfully. This is also the reason why this algorithm does not
     * "re-solve" mazes so that it can place the entrance and exit, it is just sure, that is will work :).
     */
    void executeRandomDFS();

    /**
     * @brief Converts the maze structure from memory to an SVG file.
     */
    void saveMaze();

public:
    /**
     * @brief Constructs and generates a random maze.
     *
     * @param Y Number of rows in the maze.
     * @param X Number of columns in the maze.
     */
    Maze(const int Y, const int X);
};