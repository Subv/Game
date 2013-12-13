#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Unit.h"

class Game;

class GameObject : public Unit
{
public:
    GameObject(Game* _game, std::string model);
    ~GameObject();

    virtual bool ShouldFall() const override { return false; }
    virtual void Update(sf::Time const diff) override;

    virtual void HandleCollision(Entity* collider) override;
private:
    Game* game;
};
#endif