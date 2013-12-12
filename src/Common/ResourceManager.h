#ifndef RESOURCES_H
#define RESOURCES_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <thread>
#include <mutex>


class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    static ResourceManager* Instance()
    {
        if (!_instance)
        {
            std::lock_guard<std::mutex> lock(LoadMutex);
            if (!_instance)
                _instance = new ResourceManager();
        }
        return _instance;
    }

    sf::Texture& GetTexture(std::string name);
    sf::Font& GetFont(std::string name);
    sf::Texture& GetTile(std::string name);

    std::string ResourcesDir;

    static std::mutex LoadMutex;
private:
    static ResourceManager* _instance;
    std::unordered_map<std::string, sf::Texture*> Textures;
    std::mutex TexturesMutex;
    std::unordered_map<std::string, sf::Font*> Fonts;
    std::mutex FontsMutex;
    std::unordered_map<std::string, sf::Texture*> Tiles;
    std::mutex TilesMutex;
};

#define sResourceManager ResourceManager::Instance()
#endif