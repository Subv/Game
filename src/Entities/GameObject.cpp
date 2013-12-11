#include <iostream>
#include "Unit.h"
#include "GameObject.h"
#include "Game.h"
#include "SharedDefines.h"

GameObject::GameObject(Game* _game, std::string model) : Unit(_game, model)
{
    Type = TYPEID_OBJECT;
}

GameObject::~GameObject()
{

}
