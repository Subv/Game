#include "Input.h"
#include <Thor/Input.hpp>

Input::Input()
{
    LoadBindings();
    LoadActions();
}

Input::~Input()
{

}

void Input::LoadBindings()
{
    // We load the user defined (or default) key bindings
    KeyBindings.insert(BindingsMap::value_type(ACTION_JUMP, InputButton(DEVICE_KEYBOARD, BUTTON_TYPE_KEY, sf::Keyboard::Space)));
    KeyBindings.insert(BindingsMap::value_type(ACTION_JUMP, InputButton(DEVICE_JOYSTICK, BUTTON_TYPE_KEY, 0)));
}

void Input::LoadActions()
{
    for (BindingsMap::iterator itr = KeyBindings.begin(); itr != KeyBindings.end(); ++itr)
    {
        auto bindings = KeyBindings.equal_range(itr->first);
        for (auto key = bindings.first; key != bindings.second; ++key)
        {
            auto old = KeyActions[key->first];
            if (key->second.Device == DEVICE_KEYBOARD)
                KeyActions[key->first] = thor::Action(key->second.Button.KeyboardKey);
            else if (key->second.Type == BUTTON_TYPE_AXIS)
                KeyActions[key->first] = thor::Action(thor::joy(0).axis(key->second.Button.JoystickAxis).above(30.f));
            else
                KeyActions[key->first] = thor::Action(thor::joy(0).button(key->second.Button.JoystickButton), thor::Action::PressOnce);
            
            if (old.isValid())
                KeyActions[key->first] = KeyActions[key->first] || old;
        }
    }
}

void Input::Update(sf::RenderWindow& window)
{
    KeyActions.update(window);
}
