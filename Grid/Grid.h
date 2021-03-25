#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
class Grid{
    public:
        struct Coord{
            int x;
            int y;
            bool operator==(const Coord &b) const{
                return (this->x == b.x) && (this->y == b.y);
            }
            bool operator!=(const Coord &b) const{
                return !(*this == b);
            }
            bool operator<(const Coord&b) const{
                return this->x < b.x || this->y < b.y;
            }
        };
        enum Status{
            START,
            CAN_CROSS,
            BLOCKED,
            VISITED,
            IN_QUEUE,
            GOAL,
            NOT_REACHEABLE,
            PATH 
        };
        class Grid_Out_Of_Bounds{};
        Grid(unsigned, sf::RenderWindow&);
        void set_coordinates_to_status(Grid::Coord, Grid::Status);
        Grid::Status get_status(Grid::Coord);
        void set_status(Grid::Coord, Grid::Status);
        bool check_boundary(Grid::Coord);
        void draw();
        Grid::Coord get_start();
        Grid::Coord get_goal();
        void clear(bool = false);
        void generate_maze(int, int, int, int);
        bool choose_orientation(int, int);
    private:
        unsigned size;
        std::vector<std::vector<Grid::Status>>_grid;
        sf::RenderWindow *window;
        std::vector<std::vector<sf::RectangleShape>>_box_grid;
        Grid::Coord start;
        Grid::Coord goal;
        std::random_device rd;
        std::mt19937 mt;
        void change_color(Grid::Coord, Grid::Status);
        void generate_maze_helper(int, int, int, int, bool, std::vector<std::vector<bool>>&);
        int random_number(int);
};
//For hashing keys on hash tables
namespace std{
    template<>
    struct hash<Grid::Coord>{
        std::size_t operator()(const Grid::Coord &coord) const{
            using std::size_t;
            return (hash<int>()(coord.x) ^ (hash<int>()(coord.y << 1)) >> 1);
        }
    };
}
#endif