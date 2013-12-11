#include "Map.h"
#include "Tile.h"
#include "SpecialTile.h"

SpecialTile::SpecialTile(Game* _game, int x, int y) : Tile(_game, x, y, true, "")
{

}

SpecialTile::~SpecialTile()
{

}

void SpecialTile::Update(sf::Time const diff)
{
    Entity::Update(diff);
}

