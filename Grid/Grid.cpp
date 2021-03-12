#include "Grid.h"
bool Grid::checkBoundary(Grid::Coord current){
    if(current.x < 0 || current.x >= _grid[0].size() || current.y < 0 || current.y >= _grid.size()){
        return false;
    }
    return _grid[current.x][current.y] == Grid::Status::CAN_CROSS;
}

void Grid::set_coordinates_to_value(Grid::Coord coordinates, Grid::Status value){
    int x = coordinates.x, y = coordinates.y;
    if(value == Grid::Status::BLOCKED)_box_grid[y][x].setFillColor(sf::Color::Black);
    _grid[x][y] = value;
}

void Grid::draw(){
    for(auto row:_box_grid){
        for(auto box:row){
            window->draw(box);
        }
    }
}

Grid::Grid(unsigned size, sf::RenderWindow &w):_grid(std::vector<std::vector<Grid::Status>>(size, std::vector<Grid::Status>(size, CAN_CROSS))), window(&w){
    int Y = window->getSize().y;
    int X = window->getSize().x;
    int y_size = Y/size;
    int x_size = X/size;
    for(int y = 0; y <= Y; y+=y_size){
        std::vector<sf::RectangleShape>line;
        for(int x = 0; x <= X; x+=x_size){
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(x_size, y_size));
            rectangle.setOutlineColor(sf::Color::Black);
            rectangle.setOutlineThickness(1);
            rectangle.setPosition(x, y);;
            line.push_back(rectangle);
        }
        _box_grid.push_back(line);
    }
}