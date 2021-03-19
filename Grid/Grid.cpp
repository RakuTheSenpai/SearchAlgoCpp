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
    if(!check_boundary(coords)) throw Grid_Out_Of_Bounds{};
    //Dont change start color to avoid confusion
    if((coords == start && value!=Grid::Status::VISITED)|| coords != start)change_color(coords, value);
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
    window->display();
}

Grid::Status Grid::get_status(Grid::Coord coords){
    return _grid[coords.y][coords.x];
}

Grid::Grid(unsigned s, sf::RenderWindow &w):size{s},_grid(std::vector<std::vector<Grid::Status>>(size, std::vector<Grid::Status>(size, CAN_CROSS))), window(&w), mt(rd()){
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
    mt.seed(::time(NULL));
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
/*Reference: 
http://weblog.jamisbuck.org/2011/1/12/maze-generation-recursive-division-algorithm
https://en.wikipedia.org/wiki/Maze_generation_algorithm#Recursive_division_method
https://stackoverflow.com/questions/59807560/maze-generator-using-recursive-division
*/
void Grid::generate_maze(int x, int y, int width, int height){
    std::vector<std::vector<bool>>visited(size, std::vector<bool>(size, false));
    generate_maze_helper(0, 0, width, height, true, visited);
}

int Grid::random_number(int number){
    std::uniform_int_distribution<int> rnd(0, number);
    return rnd(mt);
}
void Grid::generate_maze_helper(int x, int y, int width, int height, bool horizontal_orientation, std::vector<std::vector<bool>>&visited){
    //Base case: Area is too small to proceed
    if(width < 2 || height < 2){
        return;
    }
    draw();
    //This is basically because most algorithms assume a N*N matrix based on "lines" since this is "chunky" i.e it has cells it's technically 2 * N + 1 thus (x - 1)/2
    int uwidth = (width - 1)/2;
    int uheight = (height - 1)/2;
    //Select random location for wall depending on orientation
    int wX = x + (horizontal_orientation?0:2 * random_number(uwidth) + 1);
    int wY = y + (horizontal_orientation?2 * random_number(uheight) + 1:0);
    //Select random location for hole depending on orientation
    int hX = wX + (horizontal_orientation?2 * random_number(uwidth):0);
    int hY = wY + (horizontal_orientation?0:2 * random_number(uheight));
    //Movement on either the X or Y axis
    int dX = horizontal_orientation?1:0;
    int dY = horizontal_orientation?0:1;

    int goal = horizontal_orientation?width:height;

    //Draw walls except on goal, start, hole or on a visited space (so we don't redraw over previous holes)
    for(int i = 0; i < goal; ++i){
        if(!visited[wX][wY] && (wX != hX || wY != hY) && (get_status(Grid::Coord{wX, wY})!= Grid::Status::START && get_status(Grid::Coord{wX, wY}) != Grid::Status::GOAL)) {
            set_status(Grid::Coord{wX, wY}, Grid::Status::BLOCKED);
        }
        visited[wX][wY] = true;
        wX += dX;
        wY += dY;
    }
    draw();
    //Keep dividing in current area
    int nx = x, ny = y;
    int w = horizontal_orientation?width:wX - x;
    int h = horizontal_orientation?wY - y:height;
    generate_maze_helper(nx, ny, w, h, !horizontal_orientation, visited);
    //Divide the remaining area
    nx = horizontal_orientation?x:wX + 1;
    ny = horizontal_orientation?wY + 1: y;
    w = horizontal_orientation?width:x + width - wX - 1;
    h = horizontal_orientation?y + height - wY - 1:height;
    generate_maze_helper(nx, ny, w, h, !horizontal_orientation, visited);
}