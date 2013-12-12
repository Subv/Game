#include <SFML/Graphics/Sprite.hpp>
#include "Entity.h"
#include "Tile.h"
#include "SpecialTile.h"

Tile::Tile(Game* _game, int x, int y, int z, bool collides, std::string model) : Entity(_game, model), X(x), Y(y), Z(z), Collidable(collides)
{
    Type = TYPEID_TILE;
}

Tile::~Tile()
{
}

bool Tile::Intersects(sf::FloatRect& check, sf::FloatRect& intersection) const
{
    return sprite.getGlobalBounds().intersects(check, intersection);
}

SpecialTile* Tile::ToSpecialTile()
{
    if (IsSpecial())
        return reinterpret_cast<SpecialTile*>(this);
    return nullptr;
}

