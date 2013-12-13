#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Unit.h"

#include <Thor/Particles.hpp>
#include <Thor/Animation.hpp>
#include <Thor/Vectors/PolarVector.hpp>
#include <Thor/Math/Distributions.hpp>
class Game;

class Player : public Unit
{
public:
    Player(Game* _game, int index, std::string texture);
    ~Player();

    void Update(sf::Time const diff) override;
    void LoadMoveTexture(int type);

    int PlayerNumber;
    unsigned int Coins;
};
#endif