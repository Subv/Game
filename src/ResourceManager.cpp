#include "ResourceManager.h"

ResourceManager* ResourceManager::_instance = nullptr;

ResourceManager::ResourceManager() : ResourcesDir("C:/Users/Sebastian/Documents/Game/Code/Resources/")
{

}

ResourceManager::~ResourceManager()
{

}

sf::Font& ResourceManager::GetFont(std::string name)
{
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
    auto itr = Textures.find(name);
    if (itr != Textures.end())
        return *itr->second;

    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(ResourcesDir + "Textures/" + name);
    texture->setSmooth(true);
    Textures[name] = texture;

    return *texture;
}

sf::Texture& ResourceManager::GetTile(std::string name)
{
    auto itr = Tiles.find(name);
    if (itr != Tiles.end())
        return *itr->second;

    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(ResourcesDir + "Tiles/" + name);

    Tiles[name] = texture;

    return *texture;
}


