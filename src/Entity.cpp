#include "Entity.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Unit.h"
#include "Map.h"
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

bool Entity::IsInAir()
{
    return true;
}

void Entity::Draw()
{
    game->GetWindow().draw(sprite);
}

void Entity::Update(sf::Time diff)
{
    if (!map)
        return;

    // Now we do collision detection and determine if we can actually move there
    sf::FloatRect intersection;
    bool collides = map->HasCollisionAt(Position, sprite.getGlobalBounds(), intersection);
    if (collides)
    {
        StopMoving();
        std::cout << "COLLISION DETECTED" << std::endl;
    }

    sprite.setPosition(Position);

    Draw();
}

Unit* Entity::ToUnit()
{
    if (Type == TYPEID_PLAYER || Type == TYPEID_CREATURE)
        return dynamic_cast<Unit*>(this);
    return NULL;
}


