#include "Grid_Window.h"

void Grid_Window::display(){
    while(window->isOpen()){
        sf::Event event;
        while(window->pollEvent(event)){
            switch (event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::MouseButtonPressed:
                    is_pressed = true;
                    break;
                case sf::Event::MouseButtonReleased:
                    is_pressed = false;
                    break;
                case sf::Event::KeyPressed:
                    change_status(event);
                    break;
            }
        }
        window->clear(sf::Color::White);
        if(is_pressed){
           change_grid_status(status);
        }
        grid->draw();
    }
}

void Grid_Window::change_status(sf::Event event){
   switch (event.key.code)
    {
    case sf::Keyboard::Q:
        status = Grid::Status::CAN_CROSS;
        break;
    case sf::Keyboard::W:
        status = Grid::Status::BLOCKED;
        break;
    case sf::Keyboard::E:
        change_grid_status(Grid::Status::START);
        grid->clear();
        if(active == Algo_Status::BFS){
            Algo::bfs(*grid);
        }else if(active == Algo_Status::DFS){
            Algo::dfs(*grid);
        }else if(active == Algo_Status::A_STAR){
            Algo::a_star(*grid);
        }
        break;
    case sf::Keyboard::R:
        change_grid_status(Grid::Status::GOAL);
        grid->clear();
        if(active == Algo_Status::BFS){
            Algo::bfs(*grid);
        }else if(active == Algo_Status::DFS){
            Algo::dfs(*grid);
        }else if(active == Algo_Status::A_STAR){
            Algo::a_star(*grid);
        }
        break;
    case sf::Keyboard::Num1:
        active = Algo_Status::BFS;
        grid->clear();
        Algo::bfs(*grid);
        break;
    case sf::Keyboard::Num2:
        active = Algo_Status::DFS;
        grid->clear();
        Algo::dfs(*grid);
        break;
    case sf::Keyboard::Num3:
        active = Algo_Status::A_STAR;
        grid->clear();
        Algo::a_star(*grid);
        break;
    case sf::Keyboard::C:
        active = Algo_Status::NONE;
        grid->clear();
        break;
    case sf::Keyboard::D:
        active = Algo_Status::NONE;
        grid->clear(true);
        break;
    case sf::Keyboard::T:{
        grid->clear(true);
        grid->generate_maze(1,1,size, size);
    }
    default:
        break;
    } 
}
void Grid_Window::change_grid_status(Grid::Status status) {
    sf::Vector2i position = sf::Mouse::getPosition(*window);
    Grid::Coord pos{position.x, position.y};
    grid->set_coordinates_to_status(pos,status);
}