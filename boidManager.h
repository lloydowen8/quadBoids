#include <SFML/Graphics.hpp>
#include "vector2.h"
#include "boid.h"
class BoidManager{ 
    public: 

        BoidManager(int numBoids, sf::RenderWindow& windowView);

        void addBoid(double xCoord, double yCoord, int size);
        void draw(sf::RenderWindow& window);
        void updateBoundingBox(Boid& boid);
        void updatePositions();
        void updateWindowSize(sf::RenderWindow windowView);

    private: 
        sf::Clock dt;
        std::vector<Boid> boids;
        sf::RenderWindow& window;
};