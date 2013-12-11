#include <SFML/Graphics/Sprite.hpp>
#include "Tile.h"

Tile::Tile(Map* _map, int x, int y, sf::Sprite* sprite, bool collides) : map(_map), X(x), Y(y), Sprite(sprite), Collidable(collides)
{

}

Tile::~Tile()
{
}

bool Tile::Intersects(sf::FloatRect& check, sf::FloatRect& intersection) const
{
    return Sprite->getGlobalBounds().intersects(check, intersection);
}

void Tile::Draw(sf::RenderWindow& window)
{
    window.draw(*Sprite);
}

