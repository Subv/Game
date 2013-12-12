#include "Map.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Player.h"
#include "MovingTile.h"
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>

Map::Map(Game* _game) : game(_game), Players(_game->Players), Entities(_game->Entities)
{
}

Map::~Map()
{
    for (std::vector<Tile*>::iterator itr = Tiles.begin(); itr != Tiles.end(); ++itr)
        delete *itr;
    TileData.clear();
    Tiles.clear();
}

void Map::Load()
{
    std::string dir = sResourceManager->ResourcesDir;
    std::ifstream file(dir + "Levels/level1.txt");
    std::string line;

    while (std::getline(file, line))
    {
        std::vector<std::string> TileLine;
        std::stringstream ss;
        for (int i = 0; i < line.length(); i++)
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

    for (int i = 0; i < TileData.size(); ++i)
    {
        for (int j = 0; j < TileData[i].size(); ++j)
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
                tile = new Tile(game, j, i, true, "brickWall.png");
            else if (TileData[i][j] == "K")
                tile = new Tile(game, j, i, true, "grass.png");
            else if (TileData[i][j] == "L")
                tile = new Tile(game, j, i, true, "grassCenter.png");
            else if (TileData[i][j] == "M")
                tile = new Tile(game, j, i, true, "bridgeLogs.png");
            else if (TileData[i][j] == "N")
                tile = new MovingTile(game, j, i, "hill_large.png");
            else if (TileData[i][j] == "O")
                tile = new Tile(game, j, i, false, "hill_small.png");
            else if (TileData[i][j] == "P")
                tile = new Tile(game, j, i, false, "fence.png");
            else if (TileData[i][j] == "Q")
                tile = new Tile(game, j, i, false, "fenceBroken.png");
            else if (TileData[i][j] == "T")
                tile = new Tile(game, j, i, false, "bush.png");

            if (tile)
            {
                tile->AddToMap(this);
                tile->LoadTexture();
                tile->SetPosition(mapPosition);
                Tiles.push_back(tile);
            }
        }
    }
}

void Map::Update(sf::Time diff)
{
    //sf::Clock cl;
    for (std::vector<Tile*>::iterator itr = Tiles.begin(); itr != Tiles.end(); ++itr)
        (*itr)->Update(diff);
    //std::cout << "Finished updating in " << cl.getElapsedTime().asSeconds() << " seconds" << std::endl;
    Draw();
}

void Map::Draw()
{
    for (std::vector<Tile*>::iterator itr = Tiles.begin(); itr != Tiles.end(); ++itr)
        (*itr)->Draw();
}

bool Map::HasCollisionAt(sf::Vector2f pos, Entity* entity, std::list<CollisionInfo>& colliding) const
{
    sf::FloatRect intersection;
    sf::FloatRect check(pos.x, pos.y, entity->GetWidth(), entity->GetHeight());
    for (auto itr = Tiles.begin(); itr != Tiles.end(); ++itr)
    {
        if ((*itr)->Collidable && (*itr)->Intersects(check, intersection))
            colliding.push_back(CollisionInfo(intersection, *itr));
        else if ((*itr)->Collidable && (*itr)->IsSpecial())
            reinterpret_cast<SpecialTile*>(*itr)->LeaveCollision(entity);
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