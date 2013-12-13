#include "Input.h"
#include "Game.h"
#include "SharedDefines.h"
#include "Utils.h"
#include <Thor/Input.hpp>
#include <functional>
#include <fstream>

Input::Input(Game* _game) : game(_game)
{
    KeyBindings.resize(Common::MaxPlayers);

    LoadBindings();
    LoadActions();

    SaveBindings();
}

Input::~Input()
{
    SaveBindings();
}

void Input::LoadBindings()
{
    std::function<void(thor::ActionContext<Actions>)>* _exitHandler = new std::function<void(thor::ActionContext<Actions>)>(std::bind(&Input::OnExit, this, std::placeholders::_1));
    std::function<void(thor::ActionContext<Actions>)>* _pauseHandler = new std::function<void(thor::ActionContext<Actions>)>(std::bind(&Input::TogglePause, this, std::placeholders::_1));

    std::ifstream bnd;
    bnd.open(Common::KeyBindingsFile);
    std::string line;
    bnd >> line;
    while (!bnd.eof())
    {
        auto sides = Utils::Split(line, "=");
        bnd >> line;

        auto lhs = Utils::Split(sides[0], ",");
        auto rhs = Utils::Split(sides[1], ",");

        unsigned int player = std::stoi(lhs[0]);
        unsigned int action = std::stoi(lhs[1]);
        
        unsigned int device = std::stoi(rhs[0]);
        unsigned int type = std::stoi(rhs[1]);
        unsigned int key = std::stoi(rhs[2]);

        if (player >= Common::MaxPlayers)
            continue;

        BindingsMap& bindings = KeyBindings[player];

        InputButton button(ButtonDevice(device), ButtonType(type), key);
        bindings.insert(BindingsMap::value_type(Actions(action), button));
    }
}

void Input::SaveBindings()
{
    std::ofstream file;
    file.open(Common::KeyBindingsFile);
    
    for (unsigned int i = 0; i < Common::MaxPlayers; ++i)
        for (BindingsMap::const_iterator itr = KeyBindings[i].begin(); itr != KeyBindings[i].end(); ++itr)
            file << i << "," << itr->first << "=" << itr->second.Device << "," << itr->second.Type << "," << itr->second.Button.JoystickButton << std::endl; // We only save the integer, because it's an union

    file.close();
}

void Input::LoadActions()
{
    for (unsigned int i = 0; i < Common::MaxPlayers; ++i)
    {
        thor::ActionMap<Actions>::CallbackSystem* callbacks = new thor::ActionMap<Actions>::CallbackSystem();
        thor::ActionMap<Actions>* actions = new thor::ActionMap<Actions>();
        for (BindingsMap::iterator itr = KeyBindings[i].begin(); itr != KeyBindings[i].end(); ++itr)
        {
            auto old = (*actions)[itr->first];
            if (itr->second.Device == DEVICE_KEYBOARD)
                (*actions)[itr->first] = thor::Action(itr->second.Button.KeyboardKey);
            else if (itr->second.Type == BUTTON_TYPE_AXIS)
                (*actions)[itr->first] = thor::Action(thor::joy(i).axis(itr->second.Button.JoystickAxis).above(30.f));
            else if (itr->second.Device == DEVICE_EVENT)
            {
                (*actions)[itr->first] = thor::Action(itr->second.Button.Event);
                if (itr->second.Callback)
                    callbacks->connect(itr->first, *itr->second.Callback);
            }
            else
                (*actions)[itr->first] = thor::Action(thor::joy(i).button(itr->second.Button.JoystickButton));

            if (old.isValid())
                (*actions)[itr->first] = (*actions)[itr->first] || old;
        }

        PlayerCallbacks.push_back(callbacks);
        KeyActions.push_back(actions);
    }
}

void Input::Update(sf::RenderWindow& window)
{
    KeyActions[0]->invokeCallbacks(SystemCallbacks, &window);

    for (unsigned int i = 0; i < Common::MaxPlayers; ++i)
    {
        KeyActions[i]->update(window);
        KeyActions[i]->invokeCallbacks(*PlayerCallbacks[i], &window);
    }
}

void Input::OnExit(thor::ActionContext<Actions> context)
{
    context.window->close();
}

void Input::TogglePause(thor::ActionContext<Actions> context)
{
    if (game->State == GAME_STATE_PAUSED)
    {
        game->State = game->PreviousState;
        game->PreviousState = GAME_STATE_NONE;
    }
    else
    {
        game->PreviousState = game->State;
        game->State = GAME_STATE_PAUSED;
    }
}

bool Input::IsActive(unsigned int player, Actions action) const
{
    if (player >= Common::MaxPlayers)
        return false;
    return KeyActions[player]->isActive(action);
}

bool Input::IsSystemAction(Actions action)
{
    return action == ACTION_ENTER || action == ACTION_ENABLE_DEBUG || action == ACTION_TOGGLE_PAUSE || action == ACTION_EXIT;
}
