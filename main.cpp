
#include "input.h"
#include "maze.h"

/**
 * @brief This program reads command-line arguments to alocate the maze dimensions.
 * Firstly, it creates a `Input` object to inspect input data. If they are valid,
 * program then creates a `Maze` object in the specified dimensions, generates the maze
 * in memory and then it saves it to the SVG file.
 */
int main(int argc, char const *argv[])
{
    /**
     * @brief Construct creates an Input object with command-line arguments as its input.
     */
    Input input(argc, argv);

    /**
     * @brief Construct creates a Maze object with dimensions from Input.
     */
    Maze maze(input.getRows(), input.getCollumns());

    return 0;
}