#include "Grid.h"
bool Grid::check_boundary(Grid::Coord current){
    if(current.x < 0 || current.x >= _grid[0].size() || current.y < 0 || current.y >= _grid.size()){
        return false;
    }
    return true;
}
void Grid::change_color(Grid::Coord coords, Grid::Status value){
    switch(value){
        case Grid::Status::START:
            _box_grid[start.y][start.x].setFillColor(sf::Color::White);
            _box_grid[coords.y][coords.x].setFillColor(sf::Color::Yellow);
            break;
        case Grid::Status::BLOCKED:
            _box_grid[coords.y][coords.x].setFillColor(sf::Color::Black);
            break;
        case Grid::Status::CAN_CROSS:
            _box_grid[coords.y][coords.x].setFillColor(sf::Color::White);
            break;
        case Grid::Status::IN_QUEUE:
            _box_grid[coords.y][coords.x].setFillColor(sf::Color::Magenta);
            break;
        case Grid::Status::VISITED:
            _box_grid[coords.y][coords.x].setFillColor(sf::Color::Blue);
            break;
        case Grid::Status::GOAL:
            _box_grid[goal.y][goal.x].setFillColor(sf::Color::White);
            _box_grid[coords.y][coords.x].setFillColor(sf::Color::Green);
            break;
        case Grid::Status::NOT_REACHEABLE:
            _box_grid[coords.y][coords.x].setFillColor(sf::Color::Red);
            break;
        case Grid::Status::PATH:
            _box_grid[coords.y][coords.x].setFillColor(sf::Color::Green);
            break;
    }
}
void Grid::set_status(Grid::Coord coords, Grid::Status value){
    change_color(coords, value);
    if(value == Grid::Status::START){
        start = coords;
    }else if(value == Grid::Status::GOAL){
        goal = coords;
    }
    _grid[coords.y][coords.x] = value;
}
void Grid::set_coordinates_to_status(Grid::Coord coordinates, Grid::Status value){
    int x = coordinates.x, y = coordinates.y;
    int X = window->getSize().x/size;
    int Y = window->getSize().y/size;
    Grid::Coord coords{x/X, y/Y};
    if(!check_boundary(coords) || coords == start || coords == goal) return;
    set_status(coords, value);
}
void Grid::draw(){
    for(auto row:_box_grid){
        for(auto box:row){
            window->draw(box);
        }
    }
}

Grid::Status Grid::get_status(Grid::Coord coords){
    return _grid[coords.y][coords.x];
}

Grid::Grid(unsigned s, sf::RenderWindow &w):size{s},_grid(std::vector<std::vector<Grid::Status>>(size, std::vector<Grid::Status>(size, CAN_CROSS))), window(&w){
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
    int n_size = size;
    start = Grid::Coord{0,0};
    goal = Grid::Coord{n_size - 1, n_size - 1};
    set_status(start, Grid::Status::START);
    set_status(goal, Grid::Status::GOAL);
}

Grid::Coord Grid::get_start(){
    return start;
}

Grid::Coord Grid::get_goal(){
    return goal;
}

void Grid::clear(bool walls){
    for(int row = 0; row < size; ++row){
        for(int col = 0; col < size; ++col){
            Grid::Coord coords{col, row};
            if(walls || get_status(coords)!= Grid::Status::BLOCKED){
                set_status(coords, Grid::Status::CAN_CROSS);
            }
        }
    }
    set_status(get_start(), Grid::Status::START);
    set_status(get_goal(), Grid::Status::GOAL);
}