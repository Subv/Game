#ifndef TILE_H
#define TILE_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"

class Map;
class SpecialTile;

class Tile : public Entity
{
public:
    Tile(Game* _game, int x, int y, int z, bool collides, std::string model);
    virtual ~Tile();

    virtual void Update(sf::Time const diff) { } // Normal tiles don't call Entity::Update
    virtual bool Intersects(sf::FloatRect& check, sf::FloatRect& intersection) const;
    virtual bool IsSpecial() const { return false; }

    virtual bool IntersectTop(Entity* entity, sf::FloatRect check) const;
    virtual bool IntersectSide(Entity* entity, sf::FloatRect check) const;

    // Collision handlers
    virtual void HandleFloor(Entity* entity, bool& floor);
    virtual void OnTopCollision(Entity* collider, sf::FloatRect intersection);
    virtual void OnLeftCollision(Entity* collider);
    virtual void OnRightCollision(Entity* collider);

    SpecialTile* ToSpecialTile();

    bool Collidable;
    int Z;
protected:
    int X;
    int Y;
};
#endif