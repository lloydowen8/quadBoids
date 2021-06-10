#include "boidManager.h"
#include <cmath>

BoidManager::BoidManager(int numBoids, sf::RenderWindow& windowView) : window(windowView){
    for(int i = 0; i < numBoids; i++){ 
        double xRand = rand() * window.getSize().x / RAND_MAX;
        double yRand = rand() * window.getSize().y / RAND_MAX;
        addBoid(xRand, yRand, 1);
    }
    dt.restart();
}

void BoidManager::draw(sf::RenderWindow& window){ 
    for(Boid boid : boids){ 
        boid.draw(window);
    }
}

void BoidManager::updatePositions(){ 
    int visionRadius = 100;
    std::vector<Boid> nearbyBoids;
    auto itEnd = boids.end();
    for (auto it = boids.begin(); it != itEnd; ++it) 
    {
        updateBoundingBox(*it);
        bool scatter = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        nearbyBoids.clear();
        for (Boid& compBoid : boids)
            if (((*it).getPosition() - compBoid.getPosition()).length() < visionRadius
                    && compBoid.getPosition() != (*it).getPosition())
                nearbyBoids.push_back(compBoid);

        (*it).updateVelocity(nearbyBoids, scatter);
        float delta = dt.restart().asSeconds();
        for (Boid& boid : boids)
            boid.updatePosition(delta);
    }

}


void BoidManager::addBoid(double xCoord, double yCoord, int size){
    Boid boid(xCoord, yCoord, size);
    updateBoundingBox(boid);
    boids.push_back(boid);
}

void BoidManager::updateBoundingBox(Boid& boid){
    sf::Vector2u windowSize = window.getSize();
    boid.setBoundingBox(Vector2(10, 10), Vector2(windowSize.x - 10, windowSize.y - 10));
}

void BoidManager::updateWindowSize(sf::RenderWindow windowView){ 
    window.setSize(windowView.getSize());
}