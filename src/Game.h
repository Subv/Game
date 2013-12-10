#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>

class Entity;
class Map;
class Menu;
class Player;

enum GameState
{
    GAME_STATE_NONE,
    GAME_STATE_LOADING_LEVEL,
    GAME_STATE_PLAYING,
    GAME_STATE_MENU,
    GAME_STATE_PAUSED
};

class Game
{
public:
    Game();
    ~Game();

    static Game* Instance()
    {
        if (!_instance)
            _instance = new Game();
        return _instance;
    }

    void Start();
    void Update(sf::Time const diff);
    void DrawTexts();

    sf::RenderWindow& GetWindow() { return window; }
    void PrepareWorld();

    Player* GetPlayer(int index = 0);
private:
    static Game* _instance; // Used to store the singleton

    sf::RenderWindow window;

    std::list<Entity*> Entities;
    std::list<Player*> Players;
    
    GameState State;
    
    Map* CurrentMap;
    Menu* MenuMap;

    // Some debugging features
    bool debugMode;
    int fps;
};

#define sGame Game::Instance()
#endif