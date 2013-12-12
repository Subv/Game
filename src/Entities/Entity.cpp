#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Unit.h"
#include "Utils.h"
#include "Map.h"
#include "Tile.h"
#include "SpecialTile.h"
#include "SharedDefines.h"

Entity::Entity(Game* _game, std::string model) : game(_game), inAir(true), TextureName(model)
{
    Type = TYPEID_ENTITY;
    NewPosition = Position;

    // Reset the movement
    Velocity.x = 0.0f;
    Velocity.y = 0.0f;
    Acceleration.x = 0.0f;
    Acceleration.y = 0.0f;
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
    bool collides = map->HasCollisionAt(NewPosition, this, collisions);

    bool floor = false;
    for (std::list<CollisionInfo>::const_iterator itr = collisions.begin(); itr != collisions.end(); ++itr)
    {
        CollisionInfo const& collision = *itr;

        if (collision.Block == this) // Don't collide with yourself
            continue;

        if (game->DebugEnabled())
        {
            sf::RectangleShape rect2(sf::Vector2f(collision.Block->GetWidth(), collision.Block->GetHeight()));
            rect2.setPosition(collision.Block->GetPositionX(), collision.Block->GetPositionY());
            rect2.setOutlineColor(sf::Color::Blue);
            rect2.setFillColor(sf::Color::Transparent);
            rect2.setOutlineThickness(3.f);
            game->GetWindow().draw(rect2);
        }

        // Detect vertical collisions
        if (Utils::CompareFloats(collision.Intersection.top + collision.Intersection.height, collision.Block->GetPositionY()) == Utils::COMPARE_GREATER_THAN &&
            Utils::CompareFloats(collision.Intersection.top + collision.Intersection.height, collision.Block->GetPositionY() + collision.Block->GetHeight()) == Utils::COMPARE_LESS_THAN &&
            Utils::CompareFloats(sprite.getGlobalBounds().top + sprite.getGlobalBounds().height, collision.Block->GetPositionY(), 10.f) == Utils::COMPARE_EQUAL)
        {
            floor = true; // There's a floor tile below us

            if (Unit* unit = ToUnit()) // Stop jumping if we're an unit
                unit->jumping = false;

            // Check that we're actually heading towards the tile
            if (Velocity.y > 0.f)
            {
                // We touched the top part of the tile, stop falling
                StopVerticalMovement();
                NewPosition.y = collision.Intersection.top - sprite.getGlobalBounds().height + 1.f; // Don't go too low, correct the position if that happens
                
                if (collision.Block->IsSpecial())
                    collision.Block->ToSpecialTile()->OnTopCollision(this);
                if (Type == TYPEID_PLAYER)
                    std::cout << "Top collision" << std::endl;
            }

            if (collision.Block->IsSpecial())
                collision.Block->ToSpecialTile()->HandleFloor(this);
        }
        // Detect horizontal collisions
        else if (Utils::CompareFloats(collision.Intersection.top, collision.Block->GetPositionY() + collision.Block->GetHeight() / 2.f) == Utils::COMPARE_LESS_THAN && // If the player is at least halfway below the tile, don't collide
            ((Utils::CompareFloats(collision.Intersection.left + collision.Intersection.width, collision.Block->GetPositionX()) == Utils::COMPARE_GREATER_THAN &&
            Utils::CompareFloats(collision.Intersection.left + collision.Intersection.width, collision.Block->GetPositionX() + collision.Block->GetWidth()) == Utils::COMPARE_LESS_THAN) ||
            (Utils::CompareFloats(collision.Intersection.left, collision.Block->GetPositionX() + collision.Block->GetWidth()) == Utils::COMPARE_LESS_THAN &&
            Utils::CompareFloats(collision.Intersection.left, collision.Block->GetPositionX()) == Utils::COMPARE_GREATER_THAN)))
        {
            if (Utils::CompareFloats(Velocity.x, 0.f) == Utils::COMPARE_GREATER_THAN &&
                Utils::CompareFloats(collision.Intersection.left + collision.Intersection.width, collision.Block->GetPositionX(), 10.f) == Utils::COMPARE_EQUAL) // If we already trespassed the tile, don't bother with collision handling, for example if the player jumped from below
            {
                // We are colliding horizontally with the left side of a tile
                StopHorizontalMovement();
                NewPosition.x = collision.Block->GetPositionX() - sprite.getGlobalBounds().width; // Move back a bit
                if (Type == TYPEID_PLAYER)
                    std::cout << "Left collision" << std::endl;
            }
            else if (Utils::CompareFloats(Velocity.x, 0.f) == Utils::COMPARE_LESS_THAN &&
                Utils::CompareFloats(collision.Intersection.left, collision.Block->GetPositionX() + collision.Block->GetWidth(), 10.f) == Utils::COMPARE_EQUAL)
            {
                // We are colliding horizontally with the right side of a tile
                StopHorizontalMovement();
                NewPosition.x = collision.Block->GetPositionX() + collision.Block->GetWidth(); // Move back a bit
                if (Type == TYPEID_PLAYER)
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
    if (IsUnit())
        return dynamic_cast<Unit*>(this);
    return nullptr;
}

void Entity::SetPosition(sf::Vector2f pos)
{
    Position = pos;
    NewPosition = pos;
    sprite.setPosition(Position);
}

void Entity::LoadTexture()
{
    if (Type != TYPEID_TILE)
        texture = sResourceManager->GetTexture(TextureName);
    else
        texture = sResourceManager->GetTile(TextureName);

    sprite.setTexture(texture);
    sprite.setPosition(Position);
}

void Entity::StopHorizontalMovement()
{
    Velocity.x = 0.f;
    Acceleration.x = 0.f;
}

void Entity::StopVerticalMovement()
{
    Velocity.y = 0.f;
    Acceleration.y = 0.f;
}
