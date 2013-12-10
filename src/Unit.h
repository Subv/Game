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

    virtual void Update(sf::Time const diff) override;

    virtual void StopMoving(sf::Vector2f alongAxis) override;
    virtual void Brake();
    virtual void Jump();
    virtual bool IsJumping() const { return jumping; }

    int HealthPoints;
    bool jumping;
    sf::Vector2f Velocity;
    sf::Vector2f Acceleration;
};
#endif