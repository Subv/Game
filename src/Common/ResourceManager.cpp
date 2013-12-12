#include "ResourceManager.h"
#include <thread>
#include <mutex>

ResourceManager* ResourceManager::_instance = nullptr;
std::mutex ResourceManager::LoadMutex;

ResourceManager::ResourceManager() : ResourcesDir("Resources/")
{

}

ResourceManager::~ResourceManager()
{
    for (std::unordered_map<std::string, sf::Font*>::iterator itr = Fonts.begin(); itr != Fonts.end(); ++itr)
        delete itr->second;
    Fonts.clear();

    for (std::unordered_map<std::string, sf::Texture*>::iterator itr = Textures.begin(); itr != Textures.end(); ++itr)
        delete itr->second;
    Textures.clear();

    for (std::unordered_map<std::string, sf::Texture*>::iterator itr = Tiles.begin(); itr != Tiles.end(); ++itr)
        delete itr->second;
    Tiles.clear();
}

sf::Font& ResourceManager::GetFont(std::string _name)
{
    std::lock_guard<std::mutex> lock(FontsMutex);

    std::string name;
    std::transform(_name.begin(), _name.end(), std::back_inserter(name), ::toupper);
    auto itr = Fonts.find(name);
    if (itr != Fonts.end())
        return *itr->second;

    sf::Font* font = new sf::Font();
    font->loadFromFile(ResourcesDir + "Fonts/" + name);

    Fonts[name] = font;
    
    return *font;
}

sf::Texture& ResourceManager::GetTexture(std::string name)
{
    std::lock_guard<std::mutex> lock(TexturesMutex);
    auto itr = Textures.find(name);
    if (itr != Textures.end())
        return *itr->second;

    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(ResourcesDir + "Textures/" + name);
    
    Textures[name] = texture;

    return *texture;
}

sf::Texture& ResourceManager::GetTile(std::string name)
{
    std::lock_guard<std::mutex> lock(TilesMutex);
    auto itr = Tiles.find(name);
    if (itr != Tiles.end())
        return *itr->second;

    sf::Texture* texture = new sf::Texture();
    texture->setSmooth(false);
    texture->loadFromFile(ResourcesDir + "Tiles/" + name);

    Tiles[name] = texture;

    return *texture;
}


