#ifndef SPECIAL_TILE_H
#define SPECIAL_TILE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include "Tile.h"

class Map;
class Entity;

class SpecialTile : public Tile
{
public:
    SpecialTile(Map* _map, int x, int y, sf::Sprite* sprite);
    virtual ~SpecialTile();

    // Optional handlers
    virtual void OnTopCollision(Entity* collider) { }
    virtual void OnLeftCollision(Entity* collider) { }
    virtual void OnRightCollision(Entity* collider) { }
    virtual void HandleFloor(Entity* entity) { }
};

#endif