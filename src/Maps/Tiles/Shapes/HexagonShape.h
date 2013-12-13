#ifndef HEXAGON_H
#define HEXAGON_H

#include <SFML/Graphics/Shape.hpp>
#include <vector>

class HexagonShape : public sf::Shape
{
public:
    HexagonShape(sf::Vector2f& center, float arista);

    unsigned int getPointCount() const override { return 6; }

    sf::Vector2f getPoint(unsigned int index) const;

private:
    float _arista;
    sf::Vector2f _center;
};
#endif