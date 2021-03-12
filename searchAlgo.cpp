#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid/Grid.h"
#include "Algo/Algo.h"

void change_status(sf::Event, Grid::Status&, const sf::RenderWindow&, Grid&grid);
void change_grid_status(Grid::Status status, const sf::RenderWindow &window, Grid&grid);

int main(){
    int width = 800, height = 600, size = 20;
    bool is_pressed = false;
    sf::RenderWindow window(sf::VideoMode(width, height), "Search Algorithm");
    Grid grid(size, window);
    Grid::Status status = Grid::Status::BLOCKED;
    //Probably can be refactored
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    is_pressed = true;
                    break;
                case sf::Event::MouseButtonReleased:
                    is_pressed = false;
                    break;
                case sf::Event::KeyPressed:
                    change_status(event, status, window, grid);
                    break;
            }
        }
        window.clear(sf::Color::White);
        if(is_pressed){
           change_grid_status(status, window, grid);
        }
        grid.draw();
        window.display();
    }
}
void change_status(sf::Event event, Grid::Status &status, const sf::RenderWindow &window, Grid &grid){
    switch (event.key.code)
    {
    case sf::Keyboard::Q:
        status = Grid::Status::CAN_CROSS;
        break;
    case sf::Keyboard::W:
        status = Grid::Status::BLOCKED;
        break;
    case sf::Keyboard::E:
        change_grid_status(Grid::Status::START, window, grid);
        break;
    case sf::Keyboard::R:
        change_grid_status(Grid::Status::GOAL, window, grid);
        break;
    case sf::Keyboard::Num1:
        Algo::bfs(grid);
        break;
    case sf::Keyboard::Num2:
        Algo::dfs(grid);
        break;
    default:
        break;
    }
}
void change_grid_status(Grid::Status status, const sf::RenderWindow &window, Grid&grid) {
    sf::Vector2i position = sf::Mouse::getPosition(window);
    Grid::Coord pos{position.x, position.y};
    grid.set_coordinates_to_value(pos,status);
}