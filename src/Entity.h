#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include "SharedDefines.h"

class Game;
class Map;
class Unit;

class Entity
{
public:
    Entity(Game* _game);
    virtual ~Entity();

    virtual void Update(sf::Time const diff);
    virtual void Draw();

    virtual void LoadTexture();

    virtual TypeId GetTypeId() const { return Type; }

    virtual float GetPositionX() const { return Position.x; }
    virtual float GetPositionY() const { return Position.y; }

    virtual bool IsInAir() const { return inAir; };

    virtual void AddToMap(Map* _map) { map = _map; }

    virtual void StopMoving(sf::Vector2f alongAxis) = 0;

    Unit* ToUnit();

    sf::Vector2f NewPosition;
    sf::Vector2f Position;
protected:
    bool inAir;
    Map* map;
    TypeId Type;
    Game* game;
    sf::Texture texture;
    sf::Sprite sprite;
};
#endif