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
    for (auto& col : collisions)
    {
        if (game->DebugEnabled())
        {
            sf::RectangleShape rect(sf::Vector2f(col.Intersection.width, col.Intersection.height));
            rect.setPosition(col.Intersection.left, col.Intersection.top);
            game->GetWindow().draw(rect);

            sf::RectangleShape rect2(sf::Vector2f(col.Tile.Sprite.getGlobalBounds().width, col.Tile.Sprite.getGlobalBounds().height));
            rect2.setPosition(col.Tile.Sprite.getGlobalBounds().left, col.Tile.Sprite.getGlobalBounds().top);
            rect2.setOutlineColor(sf::Color::Blue);
            rect2.setFillColor(sf::Color::Transparent);
            rect2.setOutlineThickness(3.f);
            game->GetWindow().draw(rect2);
        }

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
        // Detect horizontal collisions
        else if (Utils::CompareFloats(col.Intersection.top, col.Tile.Sprite.getGlobalBounds().top + col.Tile.Sprite.getGlobalBounds().height / 2.f) == Utils::COMPARE_LESS_THAN && // If the player is at least halfway below the tile, don't collide
                ((Utils::CompareFloats(col.Intersection.left + col.Intersection.width, col.Tile.Sprite.getGlobalBounds().left) == Utils::COMPARE_GREATER_THAN &&
                Utils::CompareFloats(col.Intersection.left + col.Intersection.width, col.Tile.Sprite.getGlobalBounds().left + col.Tile.Sprite.getGlobalBounds().width) == Utils::COMPARE_LESS_THAN) ||
                (Utils::CompareFloats(col.Intersection.left, col.Tile.Sprite.getGlobalBounds().left + col.Tile.Sprite.getGlobalBounds().width) == Utils::COMPARE_LESS_THAN &&
                Utils::CompareFloats(col.Intersection.left, col.Tile.Sprite.getGlobalBounds().left) == Utils::COMPARE_GREATER_THAN)))
        {
            if (Utils::CompareFloats(ToUnit()->Velocity.x, 0.f) == Utils::COMPARE_GREATER_THAN &&
                Utils::CompareFloats(col.Intersection.left + col.Intersection.width, col.Tile.Sprite.getGlobalBounds().left, 10.f) == Utils::COMPARE_EQUAL) // If we already trespassed the tile, don't bother with collision handling, for example if the player jumped from below
            {
                // We are colliding horizontally with the left side of a tile
                ToUnit()->Velocity.x = 0.f;
                ToUnit()->Acceleration.x = 0.f;
                NewPosition.x = col.Tile.Sprite.getGlobalBounds().left - sprite.getGlobalBounds().width; // Move back a bit
                std::cout << "Left collision" << std::endl;
            }
            else if (Utils::CompareFloats(ToUnit()->Velocity.x, 0.f) == Utils::COMPARE_LESS_THAN &&
                Utils::CompareFloats(col.Intersection.left, col.Tile.Sprite.getGlobalBounds().left + col.Tile.Sprite.getGlobalBounds().width, 10.f) == Utils::COMPARE_EQUAL)
            {
                // We are colliding horizontally with the right side of a tile
                ToUnit()->Velocity.x = 0.f;
                ToUnit()->Acceleration.x = 0.f;
                NewPosition.x = col.Tile.Sprite.getGlobalBounds().left + col.Tile.Sprite.getGlobalBounds().width; // Move back a bit
                std::cout << "Right collision" << std::endl;
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


