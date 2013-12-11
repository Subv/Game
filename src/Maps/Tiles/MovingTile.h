#ifndef MOVING_TILE_H
#define MOVING_TILE_H

#include "SpecialTile.h"

class Game;

class MovingTile : public SpecialTile
{
public:
    MovingTile(Game* _game, int x, int y);
    ~MovingTile();

    void Update(sf::Time const diff) override;
};
#endif