#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#ifndef GRID_H
#define GRID_H
class Grid{
    public:
        struct coord{
            int x;
            int y;
            bool operator==(const coord &b){
                return (this->x == b.x) && (this->y == b.y);
            }
        };
        Grid(unsigned s):_grid(std::vector<std::vector<unsigned>>(s, std::vector<unsigned>(s, 0))){}
        Grid():_grid(std::vector<std::vector<unsigned>>(DEFAULT_SIZE, std::vector<unsigned>(DEFAULT_SIZE, 0))){}
        void dfs(coord, coord = {0, 0});
        void bfs(coord, coord = {0, 0});
        friend std::ostream& operator<<(std::ostream& os, const Grid&g)
        {
            for(auto y:g._grid){
                for(auto x:y){
                    os << x << " ";
                }
                os << "\n";
            }
            return os;
        }
        void set_coordinates_to_value(coord, unsigned);
    private:
        std::vector<std::vector<unsigned>>_grid;
        const unsigned DEFAULT_SIZE = 10;
        bool checkBoundary(coord);
        std::vector<coord>offset = {
            {0, 1},
            {0, -1},
            {1, 0},
            {-1, 0},
            {1, 1},
            {-1, -1},
            {1, -1},
            {-1, 1}
        };
};
#endif