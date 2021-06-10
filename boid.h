#include <SFML/Graphics.hpp>
#include "vector2.h"
class Boid{ 
    public: 

        Boid(double xCoord, double yCoord, float size);

        void updateVelocity(std::vector<Boid> nearbyBoids, bool scatter);
        void updatePosition(float dt);

        void draw(sf::RenderWindow& window);
        void setBoundingBox(Vector2 min, Vector2 max);

        Vector2 getPosition();
        Vector2 getVelocity();
    private: 
        Vector2 attractRule(std::vector<Boid> nearbyBoids);
        Vector2 repelentRule(std::vector<Boid> nearbyBoids);
        Vector2 velocityRule(std::vector<Boid> nearbyBoids);

        void capVelocity();
        Vector2 boundPosition();
        float getForwardAngle();
        void limitVelocity();
        sf::ConvexShape shape;
        Vector2 position;
        Vector2 velocity;

        Vector2 minBounding;
        Vector2 maxBounding;


        
};