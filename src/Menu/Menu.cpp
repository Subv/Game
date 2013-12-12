#include "Menu.h"
#include "Game.h"
#include "ResourceManager.h"
#include <iostream>

Menu::Menu(Game* _game) : game(_game), currentOption(0), parentMenu(-1)
{
    Load();
}

Menu::~Menu()
{

}

void Menu::Update(sf::Time /*diff*/)
{
    Draw();
}

void WalkTreeAndDraw(std::list<MenuItem> node, int parent, Game* game, sf::Font font)
{
    int padding = 0;
    for (std::list<MenuItem>::iterator itr = node.begin(); itr != node.end(); ++itr)
    {
        if (itr->Parent == parent)
        {
            // Found the list that we're going to display, let's add some padding between options
            sf::Text item;
            item.setString(itr->Text);
            sf::Vector2f& pos = const_cast<sf::Vector2f&>(item.getPosition());
            pos.y += padding;
            padding += 30;
            item.setFont(font);
            item.setStyle(sf::Text::Style::Bold);
            game->GetWindow().draw(item);
        }
        else if (!itr->Childs.empty())
            WalkTreeAndDraw(itr->Childs, parent, game, font);
    }
}

void Menu::Draw()
{
    sf::Font& font = sResourceManager->GetFont("arial.ttf");

    WalkTreeAndDraw(Items, parentMenu, game, font);
}

void Menu::ChangeOption(bool up)
{
    std::cout << "Going " << (up ? "up" : "down") << std::endl;
}

void Menu::ChangeMenu(bool back)
{
    /*if (back)
    {
        for (std::list<MenuItem>::iterator itr = Items.begin(); itr != Items.end(); ++itr)
        {
            if (itr->Id == parentMenu)
            {
                parentMenu = itr->Parent;
                currentOption = 0;
                break;
            }
        }
    }
    else
    {

        for (std::list<MenuItem>::iterator itr = Items.begin(); itr != Items.end(); ++itr)
        {
            if (itr->Id == currentOption && !itr->Childs.empty())
            {
                parentMenu = itr->Id;
                currentOption = 0;
                Items = itr->Childs;
                break;
            }
        }
    }*/
    std::cout << "Going " << (back ? "back" : "forth") << std::endl;
    game->PrepareWorld();
}

void Menu::Load()
{
    MenuItem main(0, -1, "Start");
    /*{
        MenuItem other(1, 0, "Other");
        {
            other.Childs.push_back(MenuItem(1, 1, "Inside other"));
            other.Childs.push_back(MenuItem(2, 1, "Inside other 2"));
        }
        MenuItem yetAnother(2, 0, "Yet Another");
        {
            yetAnother.Childs.push_back(MenuItem(1, 2, "Inside another"));
            yetAnother.Childs.push_back(MenuItem(1, 2, "Inside another 2"));
        }
        main.Childs.push_back(other);
        main.Childs.push_back(yetAnother);
    }*/
    Items.push_back(main);
}
