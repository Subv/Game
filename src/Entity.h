#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include "SharedDefines.h"

class Game;

class Entity
{
public:
    Entity(Game* _game);
    virtual ~Entity();

    virtual void Update(sf::Time diff);
    virtual void Draw();

    virtual void LoadTexture();

    virtual TypeId GetTypeId() { return Type; }

    sf::Vector2f Position;
protected:
    TypeId Type;
    Game* game;
    sf::Texture texture;
    sf::Sprite sprite;
};
#endif