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

    void Update(sf::Time diff);

    int HealthPoints;
    sf::Vector2f Velocity;
    sf::Vector2f Acceleration;
};
#endif