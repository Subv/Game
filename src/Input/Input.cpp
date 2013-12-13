#include "Input.h"
#include "Game.h"
#include <Thor/Input.hpp>
#include <functional>

Input::Input(Game* _game) : game(_game)
{
    LoadBindings();
    LoadActions();
}

Input::~Input()
{

}

void Input::LoadBindings()
{
    std::function<void(thor::ActionContext<Actions>)>* _exitHandler = new std::function<void(thor::ActionContext<Actions>)>(std::bind(&Input::OnExit, this, std::placeholders::_1));
    std::function<void(thor::ActionContext<Actions>)>* _pauseHandler = new std::function<void(thor::ActionContext<Actions>)>(std::bind(&Input::TogglePause, this, std::placeholders::_1));

    // We load the user defined (or default) key bindings
    KeyBindings.insert(BindingsMap::value_type(ACTION_JUMP, InputButton(DEVICE_KEYBOARD, BUTTON_TYPE_KEY, sf::Keyboard::Space)));
    KeyBindings.insert(BindingsMap::value_type(ACTION_JUMP, InputButton(DEVICE_JOYSTICK, BUTTON_TYPE_KEY, 0)));

    KeyBindings.insert(BindingsMap::value_type(ACTION_UP, InputButton(DEVICE_KEYBOARD, BUTTON_TYPE_KEY, sf::Keyboard::Up)));
    KeyBindings.insert(BindingsMap::value_type(ACTION_UP, InputButton(DEVICE_KEYBOARD, BUTTON_TYPE_KEY, sf::Keyboard::W)));

    KeyBindings.insert(BindingsMap::value_type(ACTION_MOVE_LEFT, InputButton(DEVICE_KEYBOARD, BUTTON_TYPE_KEY, sf::Keyboard::Left)));
    KeyBindings.insert(BindingsMap::value_type(ACTION_MOVE_LEFT, InputButton(DEVICE_KEYBOARD, BUTTON_TYPE_KEY, sf::Keyboard::A)));

    KeyBindings.insert(BindingsMap::value_type(ACTION_MOVE_RIGHT, InputButton(DEVICE_KEYBOARD, BUTTON_TYPE_KEY, sf::Keyboard::Right)));
    KeyBindings.insert(BindingsMap::value_type(ACTION_MOVE_RIGHT, InputButton(DEVICE_KEYBOARD, BUTTON_TYPE_KEY, sf::Keyboard::D)));

    KeyBindings.insert(BindingsMap::value_type(ACTION_ENTER, InputButton(DEVICE_KEYBOARD, BUTTON_TYPE_KEY, sf::Keyboard::Return)));

    KeyBindings.insert(BindingsMap::value_type(ACTION_ENABLE_DEBUG, InputButton(DEVICE_KEYBOARD, BUTTON_TYPE_KEY, sf::Keyboard::T)));

    KeyBindings.insert(BindingsMap::value_type(ACTION_EXIT, InputButton(DEVICE_EVENT, BUTTON_TYPE_KEY, sf::Event::Closed, _exitHandler)));
    KeyBindings.insert(BindingsMap::value_type(ACTION_TOGGLE_PAUSE, InputButton(DEVICE_KEYBOARD, BUTTON_TYPE_KEY, sf::Keyboard::P, _pauseHandler)));
}

void Input::LoadActions()
{
    for (BindingsMap::iterator itr = KeyBindings.begin(); itr != KeyBindings.end(); ++itr)
    {
        auto old = KeyActions[itr->first];
        if (itr->second.Device == DEVICE_KEYBOARD)
            KeyActions[itr->first] = thor::Action(itr->second.Button.KeyboardKey);
        else if (itr->second.Type == BUTTON_TYPE_AXIS)
            KeyActions[itr->first] = thor::Action(thor::joy(0).axis(itr->second.Button.JoystickAxis).above(30.f));
        else if (itr->second.Device == DEVICE_EVENT)
        {
            KeyActions[itr->first] = thor::Action(itr->second.Button.Event);
            Callbacks.connect(itr->first, *itr->second.Callback);
        }
        else
            KeyActions[itr->first] = thor::Action(thor::joy(0).button(itr->second.Button.JoystickButton));

        if (old.isValid())
            KeyActions[itr->first] = KeyActions[itr->first] || old;
    }
}

void Input::Update(sf::RenderWindow& window)
{
    KeyActions.update(window);
    KeyActions.invokeCallbacks(Callbacks, &window);
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

bool Input::IsActive(Actions action) const
{
    return KeyActions.isActive(action);
}
