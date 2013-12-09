#ifndef UNIT_H
#define UNIT_H

#include <SFML/System/Time.hpp>
#include "Entity.h"

class Game;

class Unit : public Entity
{
public:
    Unit(Game* _game);
    virtual ~Unit();

    virtual void Update(sf::Time diff);

    virtual void StopMoving();
    virtual void Brake();

    int HealthPoints;
    sf::Vector2f Velocity;
    sf::Vector2f Acceleration;
};
#endif