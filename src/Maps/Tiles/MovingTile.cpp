#include "MovingTile.h"

MovingTile::MovingTile(Game* _game, int x, int y) : SpecialTile(_game, x, y)
{

}

MovingTile::~MovingTile()
{

}

void MovingTile::Update(sf::Time const diff)
{
    sprite.move(-4.f, 0.f);
}

