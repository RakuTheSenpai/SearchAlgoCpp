#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
class Grid{
    public:
        struct Coord{
            int x;
            int y;
            bool operator==(const Coord &b){
                return (this->x == b.x) && (this->y == b.y);
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
        Grid(unsigned, sf::RenderWindow&);
        void set_coordinates_to_status(Grid::Coord, Grid::Status);
        Grid::Status get_status(Grid::Coord);
        void set_status(Grid::Coord, Grid::Status);
        bool check_boundary(Grid::Coord);
        void draw();
        Grid::Coord get_start();
        Grid::Coord get_goal();
        void clear(bool = false);
    private:
        unsigned size;
        std::vector<std::vector<Grid::Status>>_grid;
        sf::RenderWindow *window;
        std::vector<std::vector<sf::RectangleShape>>_box_grid;
        Grid::Coord start;
        Grid::Coord goal;
        void change_color(Grid::Coord, Grid::Status);
};
#endif