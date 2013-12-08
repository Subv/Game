#include "Game.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include "Menu.h"
#include "ResourceManager.h"

Game* Game::_instance = NULL;

Game::Game() : window(sf::VideoMode(1000, 600), "Game"), CurrentMap(NULL), MenuMap(NULL), fps(0), debugMode(false), State(GAME_STATE_NONE)
{
    //window.setFramerateLimit(120);
}

Game::~Game()
{
    if (window.isOpen())
        window.close();
}

void Game::Start()
{
    sf::Clock timer;
    sf::Clock fpsTimer;
    int frames = 0;

    while (window.isOpen())
    {
        ++frames;
        if (fpsTimer.getElapsedTime().asSeconds() >= 1)
        {
            fps = frames;
            frames = 0;
            fpsTimer.restart();
        }

        if (State == GAME_STATE_NONE)
            State = GAME_STATE_MENU;

        Update(timer.restart());
    }
}

void Game::Update(sf::Time diff)
{
    // Handle the events
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                return;
            case sf::Event::KeyReleased:
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::T:
                        debugMode ^= true; // Toggle debug draws
                        break;
                    case sf::Keyboard::Up:
                        if (State == GAME_STATE_MENU)
                            MenuMap->ChangeOption(true);
                        break;
                    case sf::Keyboard::Down:
                        if (State == GAME_STATE_MENU)
                            MenuMap->ChangeOption(false);
                        break;
                    case sf::Keyboard::BackSpace:
                        if (State == GAME_STATE_MENU)
                            MenuMap->ChangeMenu(true);
                        break;
                    case sf::Keyboard::Space:
                        if (State == GAME_STATE_MENU)
                            MenuMap->ChangeMenu(false);
                        break;
                }
                break;
            }
        }
    }

    window.clear();

    if (State == GAME_STATE_PLAYING)
    {
        if (CurrentMap)
            CurrentMap->Update(diff);

        for (std::list<Entity*>::iterator itr = Entities.begin(); itr != Entities.end(); ++itr)
            (*itr)->Update(diff);

        for (std::list<Player*>::iterator itr = Players.begin(); itr != Players.end(); ++itr)
            (*itr)->Update(diff);
    }
    else if (State == GAME_STATE_MENU)
    {
        if (!MenuMap)
            MenuMap = new Menu(this);
        MenuMap->Update(diff);
    }

    DrawTexts();
    window.display();
}

void Game::DrawTexts()
{
    sf::Font& font = sResourceManager->GetFont("arial.ttf");

    if (State == GAME_STATE_LOADING_LEVEL)
    {
        sf::Text text("Loading Level", font);
        text.setColor(sf::Color::White);
        text.setPosition(400.0f, 300.0f);
        text.setStyle(sf::Text::Style::Bold);
        window.draw(text);
    }

    // Draw debug information
    if (debugMode)
    {
        // Draw the FPS text on the screen
        sf::Text fpsText(std::to_string(fps) + " FPS", font);
        fpsText.setColor(sf::Color::Red);
        fpsText.setStyle(sf::Text::Style::Bold);
        window.draw(fpsText);

        if (!Players.empty())
        {
            Player* plr = Players.front();
            sf::Text posText("X: " + std::to_string(plr->Position.x) + " Y: " + std::to_string(plr->Position.y), font);
            posText.setColor(sf::Color::Red);
            posText.setStyle(sf::Text::Style::Bold);
            posText.setPosition(0, 570.0f);
            window.draw(posText);
        }
    }
}

void Game::PrepareWorld()
{
    State = GAME_STATE_LOADING_LEVEL;
    
    delete CurrentMap;
    CurrentMap = new Map(this);
    CurrentMap->Load();

    Player* player1 = new Player(this);
    player1->LoadTexture();

    Players.push_back(player1);
    State = GAME_STATE_PLAYING;
}

Player* Game::GetPlayer(int index /*= 0*/)
{
    if (Players.empty())
        return NULL;

    auto itr = Players.begin();
    std::advance(itr, index);
    
    if (itr == Players.end())
        return NULL;

    return *itr;
}
