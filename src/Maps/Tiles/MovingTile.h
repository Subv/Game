#ifndef MOVING_TILE_H
#define MOVING_TILE_H

#include "SpecialTile.h"

class Game;

class MovingTile : public SpecialTile
{
public:
    MovingTile(Map* _map, int x, int y, sf::Sprite* sprite);
    ~MovingTile();

    void Update(sf::Time const diff) override;
};
#endif