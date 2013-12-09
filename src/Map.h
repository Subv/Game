#ifndef MAP_H
#define MAP_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

class Game;
class Player;

struct TileInfo
{
    TileInfo() {}
    TileInfo(int x, int y, sf::Sprite sprite, bool collidable) : X(x), Y(y), Sprite(sprite), Collidable(collidable) { }

    int X, Y;
    bool Collidable;
    sf::Sprite Sprite;
};

class Map
{
public:
    Map(Game* _game);
    ~Map();

    void Load();

    void Update(sf::Time diff);
    void Draw();

    bool HasCollisionAt(sf::Vector2f pos, sf::FloatRect& player, sf::FloatRect& intersection, TileInfo& tile);

    void AddPlayer(Player* player);
private:
    std::vector<std::vector<std::string> > TileData;
    std::vector<TileInfo> Tiles;
    std::list<Player*> Players;
    Game* game;
};
#endif