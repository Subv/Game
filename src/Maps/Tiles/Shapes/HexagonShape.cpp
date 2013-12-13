#include "HexagonShape.h"
#include <SFML/Graphics/Shape.hpp>

HexagonShape::HexagonShape(sf::Vector2f& center, float arista) : _arista(arista), _center(center)
{
    update();
}

sf::Vector2f HexagonShape::getPoint(unsigned int index) const
{
    return sf::Vector2f(0, 0);
}

