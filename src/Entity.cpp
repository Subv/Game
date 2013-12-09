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
}

Entity::~Entity()
{

}

void Entity::LoadTexture()
{

}

bool Entity::IsInAir()
{
    return inAir;
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
    TileInfo tile;
    bool collides = map->HasCollisionAt(NewPosition, sprite.getGlobalBounds(), intersection, tile);
    bool allowMove = true;
    if (collides)
    {
        bool handled = false;
        sf::Vector2f axis(0.f, 0.f);
        if ((NewPosition.x >= tile.Sprite.getGlobalBounds().left && NewPosition.x <= tile.Sprite.getGlobalBounds().left + 70.f) || (NewPosition.x + 70.f > tile.Sprite.getGlobalBounds().left && NewPosition.x + 70.f < tile.Sprite.getGlobalBounds().left + 70.f))
        {
            if (Utils::CompareFloats(ToUnit()->Velocity.y, 0.f) != Utils::COMPARE_EQUAL) // Don't trigger the collision every frame, only when we actually collide
            {
                std::cout << "COLLISION DETECTED ON Y" << std::endl;

                if (ToUnit()->IsJumping() && Position.y < NewPosition.y)
                    ToUnit()->jumping = false;

                axis.y = 1.f;

                if (tile.Sprite.getGlobalBounds().intersects(sf::FloatRect(NewPosition.x, NewPosition.y, 40.f, 40.f))) // We collided on the head
                {
                    ToUnit()->jumping = false; // We are not jumping anymore, we are plumetting to ground
                    inAir = true;
                    allowMove = false;
                }
                else
                    inAir = false;

                std::cout << "In Air: " << inAir << std::endl;

                handled = true;
            }
        }
        else
            inAir = true;

        if (!handled && ((NewPosition.y >= tile.Sprite.getGlobalBounds().top && NewPosition.y <= tile.Sprite.getGlobalBounds().top + 70.f) || (NewPosition.y + 70.f > tile.Sprite.getGlobalBounds().top && NewPosition.y + 70.f < tile.Sprite.getGlobalBounds().top + 70.f)))
        {
            if (Utils::CompareFloats(ToUnit()->Velocity.x, 0.f) != Utils::COMPARE_EQUAL) // Don't trigger the collision every frame, only when we actually collide
            {
                axis.x = 1.f;
                allowMove = false;
                std::cout << "COLLISION DETECTED ON X" << std::endl;
            }
        }

        StopMoving(axis);
    }
    else
        inAir = true;

    if (allowMove)
    {
        Position = NewPosition;
        sprite.setPosition(Position);
    }

    Draw();
}

Unit* Entity::ToUnit()
{
    if (Type == TYPEID_PLAYER || Type == TYPEID_CREATURE)
        return dynamic_cast<Unit*>(this);
    return NULL;
}


