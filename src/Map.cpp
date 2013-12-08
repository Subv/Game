#include "Map.h"
#include "ResourceManager.h"
#include "Game.h"
#include <fstream>
#include <sstream>

Map::Map(Game* _game) : game(_game)
{

}

Map::~Map()
{

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
}

void Map::Update(sf::Time diff)
{
    Draw();
}

void Map::Draw()
{
    for (int i = 0; i < TileData.size(); ++i)
    {
        for (int j = 0; j < TileData[i].size(); ++j)
        {
            if (TileData[i][j] == "_")
                continue;

            sf::Vector2f mapPosition(j * 70.0f, i * 70.0f);
            
            std::string fileName = "none";

            if (TileData[i][j] == "J")
                fileName = "brickWall.png";
            else if (TileData[i][j] == "K")
                fileName = "grass.png";
            else if (TileData[i][j] == "L")
                fileName = "grassCenter.png";
            else if (TileData[i][j] == "M")
                fileName = "bridgeLogs.png";
            else if (TileData[i][j] == "N")
                fileName = "hill_large.png";
            else if (TileData[i][j] == "O")
                fileName = "hill_small.png";
            else if (TileData[i][j] == "P")
                fileName = "fence.png";
            else if (TileData[i][j] == "Q")
                fileName = "fenceBroken.png";
            else if (TileData[i][j] == "T")
                fileName = "bush.png";

            if (fileName != "none")
            {
                sf::Sprite block(sResourceManager->GetTile(fileName));
                block.setPosition(mapPosition);
                game->GetWindow().draw(block);
            }
        }
    }
}
