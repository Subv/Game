#ifndef MAP_H
#define MAP_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <queue>

class Tile;
class Game;
class Player;
class Entity;
class SpecialTile;

struct CollisionInfo
{
    CollisionInfo(sf::FloatRect intersect, Tile* t) : Intersection(intersect), Block(t) { }
    sf::FloatRect Intersection;
    Tile* Block;
};

class Map
{
public:
    Map(Game* _game);
    ~Map();

    void Load();

    void Update(sf::Time diff);

    bool HasCollisionAt(sf::Vector2f pos, Entity* entity, std::list<CollisionInfo>& colliding) const;

    void AddPlayer(Player* player);
    void AddEntity(Entity* entity);
    bool InSight(Tile* itr);

    void AddToRemoveQueue(Entity* entity);

    sf::Vector2f PlayerStartPosition;
private:
    void SortTiles();
    std::vector<std::vector<std::string> > TileData;
    std::list<Tile*> Tiles;
    std::list<Player*>& Players; // We must not delete this inside Map, it is just a reference to Game::Players
    std::list<Entity*>& Entities;
    std::queue<Entity*> RemoveQueue;
    Game* game;
};
#endif