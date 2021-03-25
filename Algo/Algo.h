#ifndef ALGO_H
#define ALGO_H

#include <queue>
#include <stack>
#include <unordered_map>
#include <set>
#include "../Grid/Grid.h"

class Algo{
    public:
        static void dfs(Grid&);
        static void bfs(Grid&);
        static void a_star(Grid&);
    private:
        static std::vector<Grid::Coord>offset;
        static void a_star_construct_path(std::unordered_map<Grid::Coord,Grid::Coord>&, Grid&, Grid::Coord);
        static float d(Grid::Coord, Grid::Coord);
};
#endif