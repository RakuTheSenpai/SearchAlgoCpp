#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#ifndef GRID_H
#define GRID_H
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
            NOT_REACHEABLE  
        };
        Grid(unsigned, sf::RenderWindow&);
        void set_coordinates_to_value(Grid::Coord, Grid::Status);
        Grid::Status get_grid_value(Grid::Coord);
        bool checkBoundary(Grid::Coord);
        void draw();
        void set_value(Grid::Coord, Grid::Status);
        Grid::Coord get_start();
        Grid::Coord get_goal();
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