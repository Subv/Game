#include "Entity.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Unit.h"
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
    if (collides)
    {
        sf::Vector2f axis(0.f, 0.f);
        if ((NewPosition.x >= tile.Sprite.getGlobalBounds().left && NewPosition.x <= tile.Sprite.getGlobalBounds().left + 70.f) || (NewPosition.x + 70.f > tile.Sprite.getGlobalBounds().left && NewPosition.x + 70.f < tile.Sprite.getGlobalBounds().left + 70.f))
        {
            axis.y = 1.f;
            std::cout << "COLLISION DETECTED ON Y" << std::endl;
            inAir = false;
        }
        else
            inAir = true;

        if ((NewPosition.y >= tile.Sprite.getGlobalBounds().top && NewPosition.y <= tile.Sprite.getGlobalBounds().top + 70.f) || (NewPosition.y + 70.f > tile.Sprite.getGlobalBounds().top && NewPosition.y + 70.f < tile.Sprite.getGlobalBounds().top + 70.f))
        {
            axis.x = 1.f;
            std::cout << "COLLISION DETECTED ON X" << std::endl;
        }

        StopMoving(axis);
    }
    else
    {
        std::cout << "FREE FALLING" << std::endl;
        inAir = true;
    }

    Position = NewPosition;
    sprite.setPosition(Position);

    Draw();
}

Unit* Entity::ToUnit()
{
    if (Type == TYPEID_PLAYER || Type == TYPEID_CREATURE)
        return dynamic_cast<Unit*>(this);
    return NULL;
}


