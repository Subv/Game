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
    Tile(Game* _game, int x, int y, bool collides, std::string model);
    virtual ~Tile();

    virtual void Update(sf::Time const diff) { } // Normal tiles don't call Entity::Update
    virtual bool Intersects(sf::FloatRect& check, sf::FloatRect& intersection) const;
    virtual bool IsSpecial() const { return false; }

    SpecialTile* ToSpecialTile();

    bool Collidable;
protected:
    int X;
    int Y;
};
#endif