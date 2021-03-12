#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid/Grid.h"
int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Search Algorithm");
    Grid grid(20, window);
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    grid.set_coordinates_to_value(Grid::Coord{position.x, position.y},Grid::Status::BLOCKED);
                    break; 
            }
        }
        window.clear(sf::Color::White);
        grid.draw();
        window.display();
    }
}