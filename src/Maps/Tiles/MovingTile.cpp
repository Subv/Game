#include "MovingTile.h"

MovingTile::MovingTile(Map* _map, int x, int y, sf::Sprite* sprite) : SpecialTile(_map, x, y, sprite)
{

}

MovingTile::~MovingTile()
{

}

void MovingTile::Update(sf::Time const diff)
{
    Sprite->move(-4.f, 0.f);
}

