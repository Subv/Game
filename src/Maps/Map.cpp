#include "Map.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Player.h"
#include "MovingTile.h"
#include "GameObject.h"
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>

Map::Map(Game* _game) : game(_game), Players(_game->Players), Entities(_game->Entities)
{
}

Map::~Map()
{
    for (std::list<Tile*>::iterator itr = Tiles.begin(); itr != Tiles.end(); ++itr)
        delete *itr;
    TileData.clear();
    Tiles.clear();
}

void Map::Load()
{
    srand((unsigned int)(time(NULL)));

    std::string dir = sResourceManager->ResourcesDir;
    std::ifstream file(dir + "Levels/level1.txt");
    std::string line;

    while (std::getline(file, line))
    {
        std::vector<std::string> TileLine;
        std::stringstream ss;
        for (unsigned int i = 0; i < line.length(); i++)
        {
            if (line[i] != ' ')
            {
                ss << line[i];
                TileLine.push_back(ss.str());
                ss.str(std::string());
            }
        }
        
        TileData.push_back(TileLine);
    }

    for (unsigned int i = 0; i < TileData.size(); ++i)
    {
        for (unsigned int j = 0; j < TileData[i].size(); ++j)
        {
            if (TileData[i][j] == "_")
                continue;

            sf::Vector2f mapPosition(j * 70.0f, i * 70.0f);
            Tile* tile = nullptr;

            if (TileData[i][j] == "!")
            {
                PlayerStartPosition = mapPosition;
                continue;
            }

            if (TileData[i][j] == "J")
                tile = new Tile(game, j, i, 0, true, "brickWall.png");
            else if (TileData[i][j] == "K")
                tile = new Tile(game, j, i, 0, true, j == TileData[i].size() - 1 ? "castleHillRight.png" : "grassMid.png");
            else if (TileData[i][j] == "L")
                tile = new Tile(game, j, i, 0, true, "grassCenter.png");
            else if (TileData[i][j] == "M")
                tile = new Tile(game, j, i, 0, true, "bridgeLogs.png");
            else if (TileData[i][j] == "N")
                tile = new Tile(game, j, i, 0, true, "hill_large.png");
            else if (TileData[i][j] == "O")
                tile = new Tile(game, j, i, 0, false, "hill_small.png");
            else if (TileData[i][j] == "P")
                tile = new Tile(game, j, i, 0, false, "fence.png");
            else if (TileData[i][j] == "Q")
                tile = new Tile(game, j, i, 0, false, "fenceBroken.png");
            else if (TileData[i][j] == "T")
                tile = new Tile(game, j, i, 0, false, "bush.png");
            else if (TileData[i][j] == "B")
                tile = new MovingTile(game, j, i, "plank.png");
            else if (TileData[i][j] == "I")
            {
                if (rand() % 21 >= 18)
                    tile = new Tile(game, j, i, -1, false, "cloud" + std::to_string((rand() % 3) + 1) + ".png");
            }
            else if (TileData[i][j] == "A")
            {
                GameObject* coin = new GameObject(game, "coinGold.png");
                coin->SetPosition(sf::Vector2f(mapPosition.x, mapPosition.y - 20.f));
                coin->AddToMap(this);
                game->Entities.push_back(coin);
                continue;
            }

            if (tile)
            {
                tile->AddToMap(this);
                tile->LoadTexture();
                tile->SetPosition(mapPosition);
                Tiles.push_back(tile);
            }
        }
    }

    SortTiles();
}

void Map::Update(sf::Time diff)
{
    // Remove the objects that are due to be removed
    while (!RemoveQueue.empty())
    {
        Entity*& removed = RemoveQueue.front();
        Entities.remove(removed);
        Players.remove(removed->ToPlayer());
        delete removed;
        RemoveQueue.pop();
    }

    for (std::list<Tile*>::iterator itr = Tiles.begin(); itr != Tiles.end(); ++itr)
    {
        (*itr)->Update(diff);
        if (InSight(*itr)) // Only draw the tiles that we can see
            (*itr)->Draw();
    }
}

bool Map::HasCollisionAt(sf::Vector2f pos, Entity* entity, std::list<CollisionInfo>& colliding) const
{
    sf::FloatRect intersection;
    sf::FloatRect check(pos.x, pos.y, entity->GetWidth(), entity->GetHeight());
    for (auto itr = Tiles.begin(); itr != Tiles.end(); ++itr)
    {
        if ((*itr)->Collidable && (*itr)->Intersects(check, intersection))
        {
            if ((*itr)->TextureName == "castleHillRight.png")
                entity->StopVerticalMovement();
            colliding.push_back(CollisionInfo(intersection, *itr));
        }
        else if ((*itr)->Collidable && (*itr)->IsSpecial())
            (*itr)->ToSpecialTile()->LeaveCollision(entity);
    }

    return !colliding.empty();
}

void Map::AddPlayer(Player* player)
{
    player->SetPosition(PlayerStartPosition);
    player->AddToMap(this);
}

void Map::AddEntity(Entity* entity)
{
    entity->AddToMap(this);
}

bool Map::InSight(Tile* tile)
{
    sf::View view = game->GetWindow().getView();
    sf::Vector2f topLeft;
    topLeft.x = view.getCenter().x - view.getSize().x / 2.f;
    topLeft.y = view.getCenter().y - view.getSize().y / 2.f;
    return sf::FloatRect(topLeft, view.getSize()).intersects(sf::FloatRect(tile->GetPositionX(), tile->GetPositionY(), tile->GetWidth(), tile->GetHeight()));
}

void Map::SortTiles()
{
    // This function sorts the tiles based on their draw order (Clouds are drawn first, then static tiles, then special tiles)
    Tiles.sort([](Tile*& left, Tile*& right)
    {
        return left->Z < right->Z;
    });
}

void Map::AddToRemoveQueue(Entity* entity)
{
    // Adds an entity to the remove queue, to be removed on the next Update tick
    RemoveQueue.push(entity);
}
