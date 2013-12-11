#ifndef TILE_H
#define TILE_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
class Map;

class Tile
{
public:
    Tile(Map* _map, int x, int y, sf::Sprite* sprite, bool collides);
    virtual ~Tile();

    virtual void Update(sf::Time const time) { }
    virtual bool Intersects(sf::FloatRect& check, sf::FloatRect& intersection) const;

    virtual void Draw(sf::RenderWindow& window);

    float GetWidth() const { return Sprite->getGlobalBounds().width; }
    float GetHeight() const { return Sprite->getGlobalBounds().height; }
    float GetPositionX() const { return Sprite->getGlobalBounds().left; }
    float GetPositionY() const { return Sprite->getGlobalBounds().top; }

    bool Collidable;
protected:
    Map* map;
    int X;
    int Y;
    sf::Sprite* Sprite;
};
#endif