#ifndef SPECIAL_TILE_H
#define SPECIAL_TILE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include "Tile.h"

class Game;
class Entity;

class SpecialTile : public Tile
{
public:
    SpecialTile(Game* _game, int x, int y, std::string model);
    virtual ~SpecialTile();

    // Optional handlers
    virtual void OnTopCollision(Entity* collider) { }
    virtual void OnLeftCollision(Entity* collider) { }
    virtual void OnRightCollision(Entity* collider) { }
    virtual void HandleFloor(Entity* entity) { }
    virtual void LeaveCollision(Entity* collider) { }
    virtual bool IsSpecial() const { return true; }

    virtual void Update(sf::Time const diff);
};

#endif