#ifndef MENU_H
#define MENU_H

#include <SFML/System/Time.hpp>
#include <list>
#include <string>

class Game;

class MenuItem
{
public:
    MenuItem() {}
    MenuItem(int id, int parent, std::string text) : Id(id), Parent(parent), Text(text) {}
    int Id;
    int Parent;
    std::string Text;
    std::list<MenuItem> Childs;
};

class Menu
{
public:
    Menu(Game* _game);
    ~Menu();

    void Update(sf::Time diff);
    void Draw();
    void ChangeOption(bool up);
    void ChangeMenu(bool back);

    void Load();
private:
    std::list<MenuItem> Items;
    int currentOption;
    int parentMenu;
    Game* game;
};
#endif