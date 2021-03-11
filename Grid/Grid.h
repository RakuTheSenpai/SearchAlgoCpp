#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
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
        enum Status{
            CAN_CROSS,
            BLOCKED,
            VISITED,
            IN_QUEUE,
            GOAL,
            NOT_REACHEABLE  
        };
        Grid(unsigned size, sf::RenderWindow &w, std::vector<std::vector<sf::RectangleShape>>&grid):_grid(std::vector<std::vector<Status>>(size, std::vector<Status>(size, CAN_CROSS))), window(&w), _box_grid(&grid){}
        void set_coordinates_to_value(coord, Status);
        bool checkBoundary(coord);
        void draw();
    private:
        std::vector<std::vector<Status>>_grid;
        sf::RenderWindow *window;
        std::vector<std::vector<sf::RectangleShape>> *_box_grid;
};
#endif