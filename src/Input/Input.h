#ifndef INPUT_H
#define INPUT_H

#include <Thor/Input/ActionMap.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <unordered_map>
#include <list>

enum Actions
{
    ACTION_JUMP,
    ACTION_MOVE_RIGHT,
    ACTION_MOVE_LEFT,

    // Debug stuff
    ACTION_ENABLE_DEBUG
};

enum ButtonDevice
{
    DEVICE_NONE,
    DEVICE_JOYSTICK,
    DEVICE_KEYBOARD
};

enum ButtonType
{
    BUTTON_TYPE_NONE,
    BUTTON_TYPE_KEY,
    BUTTON_TYPE_AXIS
};

class Input
{
public:
    struct InputButton
    {
        union ButtonKey
        {
            sf::Keyboard::Key KeyboardKey;
            int JoystickButton;
            sf::Joystick::Axis JoystickAxis;
        };
        
        template<typename T = sf::Keyboard::Key>
        InputButton(ButtonDevice device, ButtonType type, T k = sf::Keyboard::Space) : Device(device), Type(type) { }

        template<>
        InputButton(ButtonDevice device, ButtonType type, sf::Keyboard::Key key) : Device(device), Type(type) { Button.KeyboardKey = key; }
        
        template<>
        InputButton(ButtonDevice device, ButtonType type, sf::Joystick::Axis axis) : Device(device), Type(type) { Button.JoystickAxis = axis; }

        template<>
        InputButton(ButtonDevice device, ButtonType type, int key) : Device(device), Type(type) { Button.JoystickButton = key; }

        ButtonDevice Device;
        ButtonType Type;
        ButtonKey Button;
    };

    Input();
    ~Input();

    void LoadBindings();
    void LoadActions();
    void Update(sf::RenderWindow& window);

    thor::ActionMap<Actions> KeyActions;
    typedef std::unordered_multimap<Actions, InputButton> BindingsMap;
    BindingsMap KeyBindings;
};
#endif