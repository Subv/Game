#ifndef INPUT_H
#define INPUT_H

#include <Thor/Input.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <unordered_map>
#include <list>
#include <functional>

enum Actions
{
    ACTION_JUMP,
    ACTION_MOVE_RIGHT,
    ACTION_MOVE_LEFT,

    // Key actions
    ACTION_UP,
    ACTION_DOWN,
    ACTION_ENTER,

    // Debug stuff
    ACTION_ENABLE_DEBUG,
    ACTION_TOGGLE_PAUSE,

    // General stuff
    ACTION_EXIT,
};

enum ButtonDevice
{
    DEVICE_NONE,
    DEVICE_JOYSTICK,
    DEVICE_KEYBOARD,
    DEVICE_EVENT
};

enum ButtonType
{
    BUTTON_TYPE_NONE,
    BUTTON_TYPE_KEY,
    BUTTON_TYPE_AXIS
};

class Game;

class Input
{
public:
    class InputButton
    {
    private:
        union ButtonKey
        {
            sf::Keyboard::Key KeyboardKey;
            int JoystickButton;
            sf::Joystick::Axis JoystickAxis;
            sf::Event::EventType Event;
        };
    public:
        template<typename T = sf::Keyboard::Key>
        InputButton(ButtonDevice device, ButtonType type, T k = sf::Keyboard::Space, std::function<void(thor::ActionContext<Actions>)>* callback = nullptr) : Device(device), Type(type), Callback(callback) {}

        template<>
        InputButton(ButtonDevice device, ButtonType type, sf::Keyboard::Key key, std::function<void(thor::ActionContext<Actions>)>* callback) : Device(device), Type(type), Callback(callback) { Button.KeyboardKey = key; }
        
        template<>
        InputButton(ButtonDevice device, ButtonType type, sf::Joystick::Axis axis, std::function<void(thor::ActionContext<Actions>)>* callback) : Device(device), Type(type), Callback(callback) { Button.JoystickAxis = axis; }

        template<>
        InputButton(ButtonDevice device, ButtonType type, int key, std::function<void(thor::ActionContext<Actions>)>* callback) : Device(device), Type(type), Callback(callback) { Button.JoystickButton = key; }

        template<>
        InputButton(ButtonDevice device, ButtonType type, sf::Event::EventType key, std::function<void(thor::ActionContext<Actions>)>* callback) : Device(device), Type(type), Callback(callback) { Button.Event = key; }

        ButtonDevice Device;
        ButtonType Type;
        ButtonKey Button;
        std::function<void(thor::ActionContext<Actions>)>* Callback;
    };

    Input(Game* _game);
    ~Input();

    void LoadBindings();
    void LoadActions();
    void Update(sf::RenderWindow& window);

    bool IsActive(Actions action) const;

    // Define event handlers
    void OnExit(thor::ActionContext<Actions> context);
    void TogglePause(thor::ActionContext<Actions> context);

    thor::ActionMap<Actions> KeyActions;
    thor::ActionMap<Actions>::CallbackSystem Callbacks;
    typedef std::unordered_multimap<Actions, InputButton> BindingsMap;
    BindingsMap KeyBindings;
    Game* game;
};
#endif