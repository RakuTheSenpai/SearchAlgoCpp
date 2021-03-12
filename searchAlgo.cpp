#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid/Grid.h"
int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Search Algorithm");
    int N = 20;
    Grid grid(N, window);
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
                    int X = window.getSize().x/N;
                    int Y = window.getSize().y/N;
                    Grid::Coord coords{position.x/X, position.y/Y};
                    grid.set_coordinates_to_value(coords,Grid::Status::BLOCKED);
                    break; 
            }
        }
        window.clear(sf::Color::White);
        grid.draw();
        window.display();
    }
}