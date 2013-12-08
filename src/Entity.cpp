#include "Entity.h"
#include "Game.h"
#include "ResourceManager.h"
#include "SharedDefines.h"
#include <SFML/Graphics.hpp>

Entity::Entity(Game* _game) : game(_game)
{
    Type = TYPEID_ENTITY;
}

Entity::~Entity()
{

}

void Entity::LoadTexture()
{
    
}

void Entity::Draw()
{
    game->GetWindow().draw(sprite);
}

void Entity::Update(sf::Time diff)
{
    sprite.setPosition(Position);
    Draw();
}



