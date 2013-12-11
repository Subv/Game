#include "Entity.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Unit.h"
#include <iostream>
#include "Utils.h"
#include "Map.h"
#include "SharedDefines.h"
#include <SFML/Graphics.hpp>

Entity::Entity(Game* _game) : game(_game), inAir(true)
{
    Type = TYPEID_ENTITY;
    NewPosition = Position;
}

Entity::~Entity()
{

}

void Entity::Draw()
{
    game->GetWindow().draw(sprite);
}

void Entity::Update(sf::Time const diff)
{
    if (!map)
        return;

    // Now we do collision detection and determine if we can actually move there
    std::list<CollisionInfo> collisions;
    bool collides = map->HasCollisionAt(NewPosition, sprite.getGlobalBounds(), collisions);

    bool floor = false;
    for (auto col : collisions)
    {
        sf::RectangleShape rect(sf::Vector2f(col.Intersection.width, col.Intersection.height));
        rect.setPosition(col.Intersection.left, col.Intersection.top);
        game->GetWindow().draw(rect);

        // Detect vertical collisions
        if (Utils::CompareFloats(col.Intersection.top + col.Intersection.height, col.Tile.Sprite.getGlobalBounds().top) == Utils::COMPARE_GREATER_THAN && 
            Utils::CompareFloats(col.Intersection.top + col.Intersection.height, col.Tile.Sprite.getGlobalBounds().top + col.Tile.Sprite.getGlobalBounds().height) == Utils::COMPARE_LESS_THAN && 
            Utils::CompareFloats(sprite.getGlobalBounds().top + sprite.getGlobalBounds().height, col.Tile.Sprite.getGlobalBounds().top, 10.f) == Utils::COMPARE_EQUAL)
        {
            floor = true; // There's a floor tile below us
            ToUnit()->jumping = false;
            // Check that we're actually heading towards the tile
            if (ToUnit()->Velocity.y > 0.f)
            {
                // We touched the top part of the tile, stop falling
                ToUnit()->Velocity.y = 0.f;
                ToUnit()->Acceleration.y = 0.f;
                NewPosition.y = col.Intersection.top - sprite.getGlobalBounds().height + 1.f; // Don't go too low, correct the position if that happens
                std::cout << "Top collision" << std::endl;
            }
        }
    }

    Position.x = NewPosition.x;
    Position.y = NewPosition.y;

    inAir = !floor;

    sprite.setPosition(Position);

    Draw();
}

Unit* Entity::ToUnit()
{
    if (Type == TYPEID_PLAYER || Type == TYPEID_CREATURE)
        return dynamic_cast<Unit*>(this);
    return nullptr;
}

void Entity::SetPosition(sf::Vector2f pos)
{
    Position = pos;
    NewPosition = pos;
    sprite.setPosition(Position);
}


