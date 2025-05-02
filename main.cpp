#include "input.h"
#include "maze.h"

int main(int argc, char const *argv[])
{
    Input input(argc, argv);

    Maze maze(input.getRows(), input.getCollumns());

    return 0;
}