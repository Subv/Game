#include <iostream>
#include "Unit.h"
#include "GameObject.h"
#include "Player.h"
#include "Game.h"
#include "SharedDefines.h"

GameObject::GameObject(Game* _game, std::string model) : Unit(_game, model)
{
    // Only coins for now.
    Type = TYPEID_OBJECT;
}

GameObject::~GameObject()
{

}

void GameObject::Update(sf::Time const diff)
{
    Unit::Update(diff);
}

void GameObject::HandleCollision(Entity* collider)
{
    if (Player* player = collider->ToPlayer())
    {
        player->Coins += 1;
        RemoveFromWorld();
    }
}
