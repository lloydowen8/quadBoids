#define _USE_MATH_DEFINES

#include "boid.h"
#include <cmath>

Boid::Boid(double x, double y, float size){ 
    shape.setPointCount(3);
    shape.setPoint(0, sf::Vector2f(-5 * size, 15 * size));
    shape.setPoint(1, sf::Vector2f(5 * size, 15 * size));
    shape.setPoint(2, sf::Vector2f(0, 0));
    shape.setOrigin(0, 10 * size);

    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(x, y);
    shape.setRotation(rand() * 360 / RAND_MAX);
    position.setX(x);
    position.setY(y);
    //velocity.setX(rand() * 20 / RAND_MAX);
    velocity.setY(rand() * 20 / RAND_MAX);
    updatePosition(0);
}

void Boid::draw(sf::RenderWindow &window){ 
    window.draw(shape);
}
void Boid::setBoundingBox(Vector2 min, Vector2 max){ 
    if(min.getX() > max.getX() || min.getY() > max.getY()){ 
        printf("Illegal bounding box min > max\n");
        throw "Illegal bounding box";
    }
    minBounding = min;
    maxBounding = max;
}

Vector2 Boid::getPosition(){ 
    return position;
}

Vector2 Boid::getVelocity(){ 
    return velocity;
}

void Boid::updatePosition(float dt){ 
    position += velocity * dt;
    if(dt != 0){ 
        if(position.getX() < minBounding.getX()){ 
            position.setX(maxBounding.getX());
        }
        if(position.getX() > maxBounding.getX()){ 
            position.setX(minBounding.getX());
        }
        if(position.getY() < minBounding.getY()){ 
            position.setY(maxBounding.getY());
        }
        if(position.getY() > maxBounding.getY()){ 
            position.setY(minBounding.getY());
        }
    }

    shape.setPosition(position.getX(), position.getY());
}

void Boid::updateVelocity(std::vector<Boid> neighbourBoids, bool scatter){ 
    Vector2 v1, v2, v3;
    float c[] = {1.0/50, 50, 1.0/100};
    if(scatter){ 
        c[0] = -100;
        c[2] /= 2; 
    }
    if(neighbourBoids.size() > 0){ 
        v1 = attractRule(neighbourBoids) * c[0];
        v2 = repelentRule(neighbourBoids) * c[1];
        v3 = velocityRule(neighbourBoids) * c[2];
        velocity += v1 + v2 + v3;
    }

    shape.setRotation(getForwardAngle() + 90);
    limitVelocity();
}

Vector2 Boid::attractRule(std::vector<Boid> neighbourBoids){
    Vector2 perceivedCenter;

    for(Boid& boid : neighbourBoids){ 
        perceivedCenter += boid.getPosition();
    }

    perceivedCenter /= neighbourBoids.size();

    return (perceivedCenter - position);
}

Vector2 Boid::repelentRule(std::vector<Boid> neighbourBoids){ 
    Vector2 repelentForce;
    for(Boid& boid:neighbourBoids){ 
        auto d = (position - boid.getPosition()).length();
        if (d < 30){
            repelentForce -= position - boid.getPosition();
        }
    }
    if (repelentForce != Vector2(0, 0))
    {
        // unit vector * inverse length
        // (makes the force stronger the closer the boids are to each other)
        repelentForce = repelentForce.normalized() * (1.0 / repelentForce.length());

    }
    return repelentForce ;
}

Vector2 Boid::velocityRule(std::vector<Boid> neighbourBoids){ 
    Vector2 perceivedVel;

    for(Boid& boid:neighbourBoids){ 
        perceivedVel += boid.getVelocity();
    }

    perceivedVel /= neighbourBoids.size();
    
    return perceivedVel;
}

Vector2 Boid::boundPosition(){ 
    Vector2 vel; 
    vel = {0, 0};

    if(position.getX() < minBounding.getX()){ 
        vel.setX(10);
    }
    if(position.getX() > maxBounding.getX()){ 
        vel.setX(-10);
    }
    if(position.getY() < minBounding.getY()){ 
        vel.setY(10);
    }
    if(position.getY() > maxBounding.getY()){ 
        vel.setY(-10);
    }
    return vel;
}

void Boid::limitVelocity()
{
    int limit = 300;
    if (velocity.length() > limit)
        velocity = (velocity / velocity.length()) * limit;
}

float Boid::getForwardAngle(){ 
    Vector2 normVel = velocity.normalized(); 

    float angle = atan2(normVel.getY(), normVel.getX());
    angle *= 180 / M_PI;  // Convert to degrees
      // Flip
    return angle;
}