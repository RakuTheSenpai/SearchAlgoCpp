#include <iostream>
#include <vector>
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
        enum status{
            CAN_CROSS,
            BLOCKED,
            VISITED,
            IN_QUEUE,
            GOAL,
            NOT_REACHEABLE  
        };
        Grid(unsigned size):_grid(std::vector<std::vector<status>>(size, std::vector<status>(size, CAN_CROSS))){}
        Grid():_grid(std::vector<std::vector<status>>(DEFAULT_SIZE, std::vector<status>(DEFAULT_SIZE, CAN_CROSS))){}
        void set_coordinates_to_value(coord, status);
        bool checkBoundary(coord);
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
    private:
        std::vector<std::vector<status>>_grid;
        const unsigned DEFAULT_SIZE = 10;
};
#endif