#include "Map.h"
#include "Tile.h"
#include "SpecialTile.h"

SpecialTile::SpecialTile(Map* _map, int x, int y, sf::Sprite* sprite) : Tile(_map, x, y, sprite, true)
{

}

SpecialTile::~SpecialTile()
{

}

