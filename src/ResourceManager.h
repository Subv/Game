#ifndef RESOURCES_H
#define RESOURCES_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    static ResourceManager* Instance()
    {
        if (!_instance)
            _instance = new ResourceManager();
        return _instance;
    }

    sf::Texture& GetTexture(std::string name);
    sf::Font& GetFont(std::string name);
    sf::Texture& GetTile(std::string name);

    std::string ResourcesDir;

private:
    static ResourceManager* _instance;
    std::unordered_map<std::string, sf::Texture*> Textures;
    std::unordered_map<std::string, sf::Font*> Fonts;
    std::unordered_map<std::string, sf::Texture*> Tiles;
};

#define sResourceManager ResourceManager::Instance()
#endif