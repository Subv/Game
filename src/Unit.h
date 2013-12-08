#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"

class Game;

class Unit : public Entity
{
public:
    Unit(Game* _game);
    virtual ~Unit();

    int HealthPoints;
};
#endif