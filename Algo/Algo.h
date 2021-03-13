#ifndef ALGO_H
#define ALGO_H
#include <iostream>
#include <queue>
#include <stack>
#include "../Grid/Grid.h"
class Algo{
    public:
        static void dfs(Grid&);
        static void bfs(Grid&);
    private:
        static std::vector<Grid::Coord>offset;
};
#endif