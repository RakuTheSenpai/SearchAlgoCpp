#ifndef GRID_WINDOW_H
#define GRID_WINDOW_H

#include <SFML/Graphics.hpp>
#include "../Grid/Grid.h"
#include "../Algo/Algo.h"
class Grid_Window{
    public:
    Grid_Window(unsigned x, unsigned y, std::string title): width{x}, height{y}{
        window = new sf::RenderWindow(sf::VideoMode(width, height), title);
        status = Grid::Status::BLOCKED;
        grid = new Grid(size, *window);
    }
    void display();
    private:
    enum Algo_Status{
        NONE,
        BFS,
        DFS
    };
    Algo_Status active = Algo_Status::NONE;
    unsigned width;
    unsigned height;
    bool is_pressed = false;
    Grid::Status status;
    sf::RenderWindow *window;
    unsigned size = 20;
    Grid *grid;
    void change_status(sf::Event);
    void change_grid_status(Grid::Status);
};
#endif