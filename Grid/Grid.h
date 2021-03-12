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
            CAN_CROSS,
            BLOCKED,
            VISITED,
            IN_QUEUE,
            GOAL,
            NOT_REACHEABLE  
        };
        Grid(unsigned size, sf::RenderWindow &w);
        void set_coordinates_to_value(Grid::Coord, Grid::Status);
        bool checkBoundary(Grid::Coord);
        void draw();
    private:
        std::vector<std::vector<Grid::Status>>_grid;
        sf::RenderWindow *window;
        std::vector<std::vector<sf::RectangleShape>>_box_grid;
};
#endif