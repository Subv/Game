#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>

#include "Input.h"

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
    friend Map;
    friend Input;
    friend Entity;

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
    Map* GetCurrentMap() { return CurrentMap; }

    void PrepareWorld();
    bool DebugEnabled() const { return debugMode; }

    Player* GetPlayer(int index = 0);

    Input InputHandler;
private:
    static Game* _instance; // Used to store the singleton

    sf::RenderWindow window;

    std::list<Entity*> Entities;
    std::list<Player*> Players;
    
    GameState State;
    GameState PreviousState;
    
    Map* CurrentMap;
    Menu* MenuMap;

    // Some debugging features
    bool debugMode;
    int fps;
};

#define sGame Game::Instance()
#endif