#ifndef ALGO_H
#define ALGO_H
#include <iostream>
#include <queue>
#include <stack>
#include "../Grid/Grid.h"
class Algo{
    public:
        static Grid dfs(const Grid&, Grid::coord, Grid::coord = {0, 0});
        static Grid bfs(const Grid&, Grid::coord, Grid::coord = {0, 0});
    private:
        static std::vector<Grid::coord>offset;
};
#endif