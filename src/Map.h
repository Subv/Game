#ifndef MAP_H
#define MAP_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Game;

class Map
{
public:
    Map(Game* _game);
    ~Map();

    void Load();

    void Update(sf::Time diff);
    void Draw();
private:
    std::vector<std::vector<std::string> > TileData;
    std::vector<std::vector<sf::Sprite> > Tiles;
    Game* game;
};
#endif