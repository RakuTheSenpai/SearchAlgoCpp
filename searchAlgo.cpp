#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid/Grid.h"
int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Search Algorithm");
    std::vector<std::vector<sf::RectangleShape>>grid;
    for(int y = 0; y <= 600; y+=60){
        std::vector<sf::RectangleShape>line;
        for(int x = 0; x <= 800; x+=80){
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(80, 60));
            rectangle.setOutlineColor(sf::Color::Black);
            rectangle.setOutlineThickness(1);
            rectangle.setPosition(x, y);;
            line.push_back(rectangle);
        }
        grid.push_back(line);
    }
    grid[0][0].setFillColor(sf::Color::Blue);
    grid[9][9].setFillColor(sf::Color::Red);
    Grid _grid(10, window, grid);
    window.clear(sf::Color::White);
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        _grid.draw();
        window.display();
    }
}