#ifndef ALGO_H
#define ALGO_H

#include <queue>
#include <stack>
#include <unordered_map>
#include "../Grid/Grid.h"

class Algo{
    public:
        static void dfs(Grid&);
        static void bfs(Grid&);
        static void a_star(Grid&);
    private:
        static std::vector<Grid::Coord>offset;
        float distance(Grid::Coord);
};
#endif