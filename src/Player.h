#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Unit.h"

class Game;

class Player : public Unit
{
public:
    Player(Game* _game);
    ~Player();

    void Update(sf::Time diff);
    void LoadTexture();
};
#endif