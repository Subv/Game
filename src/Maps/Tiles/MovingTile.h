#ifndef MOVING_TILE_H
#define MOVING_TILE_H

#include "SpecialTile.h"
#include <string>
#include <set>

class Game;

class MovingTile : public SpecialTile
{
public:
    MovingTile(Game* _game, int x, int y, std::string model);
    ~MovingTile();

    void Update(sf::Time const diff) override;
    void OnTopCollision(Entity* collider) override;
    void LeaveCollision(Entity* collider) override;

    void HandleFloor(Entity* entity) override;

    void StopHorizontalMovement() override;
    void StopVerticalMovement() override;

private:
    float Displacement;
    std::set<Entity*> Passengers;
};
#endif