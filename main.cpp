#include <SFML/Graphics.hpp>
#include <random>
#include "boidManager.h"

int main(){ 
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Boids", sf::Style::Default, settings);
    window.setFramerateLimit(30);

    BoidManager boidManager(100, window);

    while(window.isOpen()){ 
        window.clear(sf::Color(200, 200, 200));
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized){
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            }
        }

        boidManager.updatePositions();
        boidManager.draw(window);

        window.display();
    }
}