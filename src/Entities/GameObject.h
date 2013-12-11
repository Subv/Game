#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Unit.h"

class Game;

class GameObject : public Unit
{
public:
    GameObject(Game* _game, std::string model);
    ~GameObject();

private:
    Game* game;
};
#endif